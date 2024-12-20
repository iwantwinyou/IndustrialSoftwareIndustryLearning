#include "lpAutoChangeModel.h"
#include <QSharedPointer>
#include "lpqtConfig/include/lpServerSheetCfg.h"
#include "include/modelCtrl.h"
#include "../lpDataMgr/lpDataMgr.h"
#pragma execution_character_set("utf-8")
#define LPDEF_LPAUTOCHANGEMODEL_VER	"v1.0.2.0"
lpAutoChangeModel::lpAutoChangeModel()
{
	qDebug() << LPDEF_LPAUTOCHANGEMODEL_VER << __FUNCTION__;
	loadCreateJobInfo();
	QVariantMap extend_vmp = lpServerSheetCfg::instance()->getCfg()->t_srv_cfg_.extend_funtion_.toMap();
	QVariantMap change_model_vmp = extend_vmp.value("auto_change_model").toMap();
	m_interval_time = change_model_vmp.value("time_interval_sec", 10).toInt();
	m_undetected_time = change_model_vmp.value("time_undetected_min", 5).toInt();
	qDebug() << __FUNCTION__ << "time(sec) " << m_interval_time << "undetectedTime(min)" << m_undetected_time;
	m_timer = new QTimer(this);
	m_timer->setInterval(m_interval_time * 1000);
	m_undetected_timer = new QTimer(this);
	m_undetected_timer->setInterval(m_undetected_time*1000*60);
	m_otherApp = QSharedPointer<lpqtconnnOtherApp>(new lpqtconnnOtherApp);
	initConnect();
}

lpAutoChangeModel::~lpAutoChangeModel()
{
	if (m_timer)
	{
		m_timer->stop();
		delete m_timer;
	}
	if (m_undetected_timer)
	{
		m_undetected_timer->stop();
		delete m_undetected_timer;
	}
}

QSharedPointer<lpAutoChangeModelMgr>lpCreateAutoModelChange()
{
	return QSharedPointer<lpAutoChangeModelMgr>(new lpAutoChangeModel());
}

void lpAutoChangeModel::initConnect()
{
	connect(this, &lpAutoChangeModel::sgChangeModel, this, &lpAutoChangeModel::onAutoChangeModel);
	connect(m_timer, &QTimer::timeout, this, &lpAutoChangeModel::onReqModel);
	connect(m_undetected_timer, &QTimer::timeout, this, &lpAutoChangeModel::onUndetectedTimeout);
	connect(m_otherApp.data(), &lpqtconnnOtherApp::sgChangeJobName, this, &lpAutoChangeModel::onAutoChangeModel);
	connect(this, &lpAutoChangeModel::sgChangeResult, m_otherApp.data(), &lpqtconnnOtherApp::on_send_data);//切换成功或失败给扫码软件发送的反馈
	connect(this, &lpAutoChangeModel::sgSendCurJobInfo, this, &lpAutoChangeModel::onRecvCurJob);
}

bool lpAutoChangeModel::plcModelMatch2AOI(const QString& plcModel)
{
	//更新模板列表
	this->updateModelList();
	//检查plc模板 是否存在更新后的 软件模板列表中
	if (m_map_model_detectparam_.contains(plcModel))
		return true;
	return false;
}

bool lpAutoChangeModel::OtherAppModelMatch2AOI(const QString& partNum)
{
	this->updateModelList();
	for (const QString& fullModelName : m_map_model_detectparam_.keys()) {
		if (fullModelName.contains(partNum)) {//完整模板名中匹配料号（第三方app发送过来的是料号 不是完整的模板名）
			m_fullMatchModelName = fullModelName;
			return true;
		}
	}
	return false;
}

void lpAutoChangeModel::updateModelList()
{
	m_map_model_detectparam_.clear();
	m_map_model_detectparam_ = modelCtrl::getModelList().value<QMap<QString, QString>>();
}

void lpAutoChangeModel::onAutoChangeModel(const QString &modelName, const QString &jobName)
{	
	emit sgPartDbReady();
	bool is_plcChange = jobName.isEmpty();
	QSharedPointer<QJsonObject> obj_sptr = QSharedPointer<QJsonObject>(new QJsonObject());
	QDateTime createTime = QDateTime::currentDateTime();//获取一下此时的时间
	QString create_time = createTime.toString("yyyy-MM-dd hh:mm:ss");
	obj_sptr->insert("create_time", create_time); //创建时间

	QString detectParam;
	double modelHeightMm = 0, modelWidthMm = 0;
	//如果是plc切换
	if (is_plcChange)
	{
		if (m_cur_model_name.isEmpty() || m_isStoped)
			return;

		if (!plcModelMatch2AOI(modelName))	//判断一下plc模型是否和当前匹配
		{
			qDebug() << "ModelList not contains newModelName,ChangeModel failed!" << __FUNCTION__;
			emit sgStart(false);//停止检测（RTP中需要停止）
			QVariantMap vmp;
			vmp["des"] = "模板不匹配";//报警类型
			emit sgSendWarning("未能找到型号为" + modelName + "的模板！！", 3, vmp);
			m_isStoped = true;
			return;
		}
		if (m_cur_model_name == modelName)//如果当前型号跟plc发送的型号一致  不进行处理 待下一次
		{
			qDebug() << "curModel and newModelName is the same!Wait the next ChangeModel!" << modelName << __FUNCTION__;
			emit sgChangeResult(false);
			return;
		}
		m_cur_model_name = modelName; //更新当前模板名为新的模板名
		obj_sptr->insert("model_name", modelName); //构建模板名 此模板名是plc发过来的新模板
		if (!m_cur_job_name.isEmpty())
			obj_sptr->insert("job_name", m_cur_job_name);//构建工单名
		if (!m_edgeGrindingHeight.isEmpty())
			obj_sptr->insert("edgeGrindingHeight", m_edgeGrindingHeight);//磨边长
		if (!m_edgeGrindingWidth.isEmpty())
			obj_sptr->insert("edgeGrindingWidth", m_edgeGrindingWidth);//磨边宽
		if (!m_isEdgeGrinding.isEmpty())
			obj_sptr->insert("isEdgeGrinding", m_isEdgeGrinding);//是否磨边
		if (!m_customName.isEmpty())
			obj_sptr->insert("customName", m_customName);
		if (!m_packNum.isEmpty())
			obj_sptr->insert("packNum", m_packNum);
		if (!m_barCode.isEmpty())
			obj_sptr->insert("bar_code", m_barCode);
		detectParam = m_map_model_detectparam_.value(modelName);// 从模型列表中获取新的检测参数
		obj_sptr->insert("detect_file_name", detectParam); //检测参数

		QString modelSize = modelCtrl::getModelSize(modelName, &modelWidthMm, &modelHeightMm);
		obj_sptr->insert("model_h_mm", modelHeightMm);
		obj_sptr->insert("model_w_mm", modelWidthMm);
		QString model_size = QString::number(modelWidthMm) + ":" + QString::number(modelHeightMm);
		obj_sptr->insert("model_size", model_size);
	}
	else //如果是第三方app
	{
		if (!OtherAppModelMatch2AOI(modelName))	//判断一下模型是否和当前匹配
		{
			qDebug() << "ModelList not contains newModelName,ChangeModel failed!" << __FUNCTION__;
			emit sgChangeResult(false);
			QVariantMap vmp;
			vmp["des"] = "模板不匹配";//报警类型
			emit sgSendWarning("未能找到型号为" + modelName + "的模板！！", 3, vmp);
			return;
		}
		obj_sptr->insert("model_name", m_fullMatchModelName); //构建模板名 此模板名是plc发过来的新模板
		if (!jobName.isEmpty())
			obj_sptr->insert("job_name", jobName);//构建工单名
		if (!m_createJobMap.value("edgeGrindingHeight").toString().isEmpty())
			obj_sptr->insert("edgeGrindingHeight", m_createJobMap.value("edgeGrindingHeight").toString());//磨边长
		if (!m_createJobMap.value("edgeGrindingWidth").toString().isEmpty())
			obj_sptr->insert("edgeGrindingWidth", m_createJobMap.value("edgeGrindingWidth").toString());//磨边宽
		if (!m_createJobMap.value("isEdgeGrinding").toString().isEmpty())
			obj_sptr->insert("isEdgeGrinding", m_createJobMap.value("isEdgeGrinding").toString());//是否磨边
		if (!m_createJobMap.value("customName").toString().isEmpty())
			obj_sptr->insert("customName", m_createJobMap.value("customName").toString());
		if (!m_createJobMap.value("packNum").toString().isEmpty())
			obj_sptr->insert("packNum", m_createJobMap.value("packNum").toString());
		if (!m_createJobMap.value("bar_code").toString().isEmpty())
			obj_sptr->insert("bar_code", m_createJobMap.value("bar_code").toString());
		for (const auto&fullModelName : m_map_model_detectparam_.keys()) {
			if (fullModelName.contains(modelName)) {
				detectParam = m_map_model_detectparam_.value(fullModelName);// 从模型列表中获取新的检测参数
				obj_sptr->insert("detect_file_name", detectParam); //检测参数
			}
		}

		QString modelSize = modelCtrl::getModelSize(m_fullMatchModelName, &modelWidthMm, &modelHeightMm);
		obj_sptr->insert("model_h_mm", modelHeightMm);
		obj_sptr->insert("model_w_mm", modelWidthMm);
		QString model_size = QString::number(modelWidthMm) + ":" + QString::number(modelHeightMm);
		obj_sptr->insert("model_size", model_size);
	}
	qDebug() << "ModelList contains newModelName" << modelName << __FUNCTION__;

	{
		qDebug() << "Begin ChangeModel" << modelName << __FUNCTION__;
		emit sgStart(false);//停止检测

		QString detect_path = QString("%1/lpIPUConfig/detectParam/%2.json").arg(modelCtrl::f_getSharePath()).arg(detectParam);
		detect_path = QDir::cleanPath(detect_path);
		obj_sptr->insert("detect_path", detect_path);
		loadDetectParam(obj_sptr, detect_path);
		//alg_param
		lpDataMgr::instance()->loadDetectParam(detect_path);
		QJsonObject job_detect_param_obj = lpDataMgr::instance()->getDetectParamJson();
		QVariantMap vJob, vAlg;
		vJob["detect_param"] = QJsonDocument(job_detect_param_obj).toJson(QJsonDocument::Compact);
		vAlg["flaw_statis"] = lpDataMgr::instance()->getFlawStatisMap();
		if (is_plcChange) {
			vAlg["model_info"] = lpDataMgr::instance()->getModelInfo(modelName, vJob);
		}
		else {
			vAlg["model_info"] = lpDataMgr::instance()->getModelInfo(m_fullMatchModelName, vJob);
		}
		vAlg["detect_param"] = lpDataMgr::instance()->getParamValueMap();
		vAlg["flaw_class"] = lpDataMgr::instance()->getFlawExpVm().toMap().value("flaw_class");
		QJsonObject algParamObj = QJsonObject::fromVariantMap(vAlg);
		obj_sptr->insert("alg_param", algParamObj);

		QJsonObject jobDetailObject = *obj_sptr;
		jobDetailObject.remove("alg_param");
		jobDetailObject.remove("detect_param");
		jobDetailObject.remove("model_h_mm");
		jobDetailObject.remove("model_w_mm");
		QString strObj = QJsonDocument(jobDetailObject).toJson(QJsonDocument::Indented);
		obj_sptr->insert("job_detail", strObj);

		emit sgNewJob(obj_sptr);
		emit sgSendCurJobInfo(obj_sptr);
		emit sgAskCurJob();
		emit sgStart(true);
		if (is_plcChange) {
			emit sgSendWarning("切换模板成功！！切换成型号为：" + modelName + " 的模板！！", 1, QVariantMap());
		}
		else {
			emit sgSendWarning("切换模板成功！！切换成型号为：" + m_fullMatchModelName + " 的模板！！", 1, QVariantMap());
		}
		emit sgChangeResult(true);
		qDebug() << "changeModel sucessfully!" << __FUNCTION__;
	}
}

void lpAutoChangeModel::onRecvCurJob(QSharedPointer<QJsonObject>curJob)
{//拿到需要的工单信息
	m_cur_model_name = curJob->value("model_name").toString();
	m_cur_job_name = curJob->value("job_name").toString();
	m_edgeGrindingWidth = curJob->value("edgeGrindingWidth").toString();
	m_edgeGrindingHeight = curJob->value("edgeGrindingHeight").toString();
	m_isEdgeGrinding = curJob->value("isEdgeGrinding").toString();
	m_customName = curJob->value("customName").toString();
	m_packNum = curJob->value("packNum").toString();
	m_barCode = curJob->value("bar_code").toString();
}

void lpAutoChangeModel::onRecvModelName(QString cmd, QVariantMap vm)
{
	if (cmd != "read_rtp_model")
		return;
	int modelStr = vm.value("model").toInt();
	if (modelStr <= 0 || modelStr >= 1000)
		return;
	QString model = QString::number(modelStr);
	if (model.isEmpty())
		return;
	qDebug() << __FUNCTION__ << "recv model:" << model;
	emit sgChangeModel(model,QString());
}

void lpAutoChangeModel::onStart(bool isStart)
{
	qDebug()<< __FUNCTION__;
	if (isStart) //如果在检测中  开启定时器
	{
		m_isStoped = false;//检测未停止
		m_undetected_timer->stop();
		m_undetected_timer->start();
	}
	else   //停止检测  关闭定时器
	{
		m_isStoped = true; //表示检测已停止
		m_timer->stop();
		m_undetected_timer->stop();
	}
}

void lpAutoChangeModel::onRecvResult()
{
	qDebug() << __FUNCTION__ << "this is autoChangeModel recvResult!";
	if (!m_undetected_timer->isActive())
	{// 开始计时
		m_undetected_timer->start();
	}
	else
	{
		m_undetected_timer->stop();
		m_undetected_timer->start();
	}
}

void lpAutoChangeModel::onReqModel()
{
	qDebug() << __FUNCTION__;
	if (!m_isStoped) //点击开始后请求 plc
	{
		QString cmd = "read_rtp_model";
		emit sgReadData(cmd);
	}

}

void lpAutoChangeModel::onUndetectedTimeout()
{
	qDebug() << __FUNCTION__;
	m_timer->start();
}

void lpAutoChangeModel::loadDetectParam(QSharedPointer<QJsonObject> &obj_sptr, const QString &detect_path)
{
	QFile detectFile(detect_path);
	if (!detectFile.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qWarning() << "Failed to open Json file!!!" << detect_path;
	}
	QJsonDocument jsonDoc = QJsonDocument::fromJson(detectFile.readAll());
	detectFile.close();
	if (jsonDoc.isNull())
	{
		qWarning() << "Failed to parse Json document!!!";
	}
	QString jsonStr = jsonDoc.toJson(QJsonDocument::Indented);
	obj_sptr->insert("detect_param", jsonStr);
}

void lpAutoChangeModel::loadCreateJobInfo()
{
	QString pathstr = QString("%1/ui/createJob.json").arg(qApp->applicationDirPath());
	QFile createJobFile(pathstr);
	if (!createJobFile.open(QIODevice::ReadOnly | QIODevice::Text)){
		qWarning() << "Failed to open Json file!!!" << pathstr;
		return;
	}
	QVariantMap pd = QJsonDocument::fromJson(createJobFile.readAll()).object().toVariantMap();
	createJobFile.close();
	if (pd.contains("additional")){
		QVariantMap addMap = pd.value("additional").toMap();
		for (auto it = addMap.begin(); it != addMap.end(); ++it){
			QVariantMap fieldMap = it.value().toMap();
			if (fieldMap.contains("template"))
			{
				m_createJobMap.insert(it.key(), fieldMap.value("template"));
			}
		}
	}
}
