#include "lpAutoChangeModel.h"
#include <QSharedPointer>
#include "lpqtConfig/include/lpServerSheetCfg.h"
#include "include/modelCtrl.h"
#include "../lpDataMgr/lpDataMgr.h"
#include "include/lperror.h"
#pragma execution_character_set("utf-8")
lpAutoChangeModel::lpAutoChangeModel()
{
	qDebug() <<"LP_VERSION_DLL " "V1.0.7.0 " __FUNCTION__;
}

lpAutoChangeModel::~lpAutoChangeModel()
{

}

QSharedPointer<lpAutoChangeModelMgr>lpCreateAutoModelChange()
{
	int create_mode{ e_plc };
	QVariantMap extend_vmp = lpServerSheetCfg::instance()->getCfg()->t_srv_cfg_.extend_funtion_.toMap();
	QVariantMap change_model_vmp = extend_vmp.value("auto_change_model").toMap();
	create_mode = change_model_vmp.value("create_mode", 0).toInt();
	switch (create_mode) {
	case e_otherApp:
		return QSharedPointer<lpAutoChangeModelMgr>(new OtherAppChangeProcess());
	case e_plc:
	default:
		return QSharedPointer<lpAutoChangeModelMgr>(new PLCChangeProcess());
	}
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

QString lpAutoChangeModel::getCurrentModelName() const
{
	return m_cur_model_name;
}

QString lpAutoChangeModel::getCurrentJobName() const
{
	return m_cur_job_name;
}

QMap<QString, QString> lpAutoChangeModel::getModelDetectparam() const
{
	return m_map_model_detectparam_;
}

void lpAutoChangeModel::onRecvCurJob(QSharedPointer<QJsonObject>curJob)
{
	m_cur_model_name = curJob->value("model_name").toString();
	m_cur_job_name = curJob->value("job_name").toString();
}

PLCChangeProcess::PLCChangeProcess()
{
	QVariantMap extend_vmp = lpServerSheetCfg::instance()->getCfg()->t_srv_cfg_.extend_funtion_.toMap();
	QVariantMap change_model_vmp = extend_vmp.value("auto_change_model").toMap();
	m_interval_time = change_model_vmp.value("time_interval_sec", 10).toInt();
	m_undetected_time = change_model_vmp.value("time_undetected_min", 5).toInt();
	qDebug() << __FUNCTION__ << "time(sec) " << m_interval_time << "undetectedTime(min)" << m_undetected_time;
	m_timer = new QTimer(this);
	m_timer->setInterval(m_interval_time * 1000);//秒
	m_undetected_timer = new QTimer(this);
	m_undetected_timer->setInterval(m_undetected_time * 1000*60);//分钟
	initConnect();
}

PLCChangeProcess::~PLCChangeProcess()
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

void PLCChangeProcess::onStart(bool isStart)
{
	qDebug()<< __FUNCTION__;
	if (isStart) //如果在检测中  开启定时器
	{
		m_isStoped = false;//检测未停止
		m_undetected_timer->start();
	}
	else   //停止检测  关闭定时器
	{
		m_isStoped = true; //表示检测已停止
		m_timer->stop();
		m_undetected_timer->stop();
	}
}

void PLCChangeProcess::onRecvResult()
{
	m_undetected_timer->start();
}

void PLCChangeProcess::onRecvModelName(QString cmd, QVariantMap vm)
{
	if (cmd != "read_rtp_model")
		return;
	QString model = vm.value("model").toString();
	if (model.isEmpty())
		return;
	qDebug() << __FUNCTION__ << "recv model:" << model;
	emit sgChangeModel(model, QString());
}

void PLCChangeProcess::onAutoChangeModel(const QString &modelName, const QString &jobName)
{
	if (getCurrentModelName().isEmpty() || m_isStoped || !m_connected) {
		qWarning() << "not auto change model" << __FUNCTION__ << "currentModelName:" << getCurrentModelName() << "isStoped:" << m_isStoped << "connect:" << m_connected;
		return;
	}
	if (!plcModelMatch2AOI(modelName)) {//判断下plc模型是否与当匹配
		qWarning() << "ModelList not contains newModelName,do not change model!" << __FUNCTION__ << "newModelName:" << modelName;
		QVariantMap vmp;
		vmp["des"] = tr("模板不匹配");
		vmp["code"] = LPERR_SHEET_MODEL_COMP;
		emit sgSendWarning("No Model found : " + modelName + ", 自动切型失败报警",3,vmp);
		emit sgStart(false);//PLC切换用于RTP项目，需要停止
		m_isStoped = true;
		return;
	}
	if (getCurrentModelName() == modelName) {
		qWarning() << "This time is not change model!" << "currentModelName:" << getCurrentModelName() << "newModelName:" << modelName << __FUNCTION__;
		return ;
	}
	QJsonObject obj;
	obj["model_name"] = modelName;
	QString cmd = "auto_new_job";
	qDebug() << __FUNCTION__ << "try auto change model!! Model:" << modelName;
	emit sgSendMaster2Ui(cmd, obj);
}

void PLCChangeProcess::onRecvUi2Master(const QString& key, QSharedPointer<QJsonObject> json_sptr)
{

}

void PLCChangeProcess::onRecvUIConnStatus(bool is_connected)
{
	m_connected = is_connected;
}

void PLCChangeProcess::onReqModel()
{
	if (!m_isStoped) //点击开始后请求 plc
	{
		QString cmd = "read_rtp_model";
		emit sgReadData(cmd);
		qDebug() << "reqModel " << __FUNCTION__;
	}
}

void PLCChangeProcess::onUndetectedTimeout()
{
	m_timer->start();
}

void PLCChangeProcess::initConnect()
{
	connect(m_timer, &QTimer::timeout, this, &PLCChangeProcess::onReqModel);
	connect(m_undetected_timer, &QTimer::timeout, this, &PLCChangeProcess::onUndetectedTimeout);
	connect(this, &PLCChangeProcess::sgChangeModel, this, &PLCChangeProcess::onAutoChangeModel);
}

OtherAppChangeProcess::OtherAppChangeProcess()
{
	loadCreateJobInfo();
	m_otherApp = QSharedPointer<lpqtconnnOtherApp>(new lpqtconnnOtherApp);
	initConnect();
}

OtherAppChangeProcess::~OtherAppChangeProcess()
{


}

void OtherAppChangeProcess::onStart(bool isStart)
{

}

void OtherAppChangeProcess::onRecvResult()
{

}

void OtherAppChangeProcess::onRecvModelName(QString cmd, QVariantMap vm)
{

}

void OtherAppChangeProcess::onAutoChangeModel(const QString &modelName, const QString &jobName)
{
	if (!m_connected) {
		qWarning() << __FUNCTION__ << "UI is not connect!" << "connect:" << m_connected;
		return;
	}
	if (!OtherAppModelMatch2AOI(modelName)) {
		qWarning() << "ModelList not contains newModelName,do not change model! " << __FUNCTION__;
		emit sgChangeResult(false);
		QVariantMap vmp;
		vmp["des"] = "模板不匹配";
		vmp["code"] = LPERR_SHEET_MODEL_COMP;
		emit sgSendWarning("No Model found:" + modelName + "的模板！！", 3, vmp);
		return;
	}
	//如果当前工单跟工单名不为空则使用上一份工单的部分数据，否则则全部重新构建新的数据
	QMap<QString, QString>modelDetectMap = getModelDetectparam();
	QString lastFullModelName;
	if (!getCurrentModelName().isEmpty() || !getCurrentJobName().isEmpty()) {
		for (const auto& fullModelName : getModelDetectparam().keys()) {
			if (fullModelName.contains(modelName)) {
				lastFullModelName = fullModelName;
			}
		}
		QJsonObject obj;
		obj["model_name"] = lastFullModelName;
		obj["job_name"] = jobName;
		QString cmd = "auto_new_job";

		qDebug() << __FUNCTION__ << "try auto change model!! Model:" << lastFullModelName << "job_name:" << jobName;
		emit sgSendMaster2Ui(cmd, obj);
	}
	else {
		for (const auto& fullModelName : getModelDetectparam().keys()) {
			if (fullModelName.contains(modelName)) {
				lastFullModelName = fullModelName;
			}
		}
		QJsonObject obj;
		QJsonObject extend_obj;////重新构建，需要createJob里面的数据
		auto getIfNotEmpty = [&](const QString& key) {
			QString val = m_createJobMap.value(key).toString();
			if (!val.isEmpty()) extend_obj.insert(key, val);
		};
		getIfNotEmpty("edgeGrindingHeight");
		getIfNotEmpty("edgeGrindingWidth");
		getIfNotEmpty("isEdgeGrinding");
		getIfNotEmpty("customName");
		getIfNotEmpty("packNum");
		getIfNotEmpty("bar_code");
		obj["model_name"] = lastFullModelName;
		obj["job_name"] = jobName;
		obj["job_info"] = extend_obj;
		QString cmd = "auto_new_job";
		qDebug() << __FUNCTION__ << "try auto change model!! Model:" << lastFullModelName << "job_name:" << jobName;
		emit sgSendMaster2Ui(cmd, obj);
	}
}

void OtherAppChangeProcess::onRecvUi2Master(const QString& key, QSharedPointer<QJsonObject> json_sptr)
{
	if (key == "auto_new_job") {
		bool isSuccess = json_sptr->value("is_success").toBool();
		emit sgChangeResult(isSuccess);
	}
}

void OtherAppChangeProcess::onRecvUIConnStatus(bool is_connected)
{
	qDebug() << "is_connected:" << is_connected;
	m_connected = is_connected;
}

void OtherAppChangeProcess::loadCreateJobInfo()
{
	QString pathstr = QString("%1/ui/createJob.json").arg(qApp->applicationDirPath());
	QFile createJobFile(pathstr);
	if (!createJobFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qWarning() << "Failed to open Json file!!!" << pathstr;
		return;
	}
	QVariantMap pd = QJsonDocument::fromJson(createJobFile.readAll()).object().toVariantMap();
	createJobFile.close();
	if (pd.contains("additional")) {
		QVariantMap addMap = pd.value("additional").toMap();
		for (auto it = addMap.begin(); it != addMap.end(); ++it) {
			QVariantMap fieldMap = it.value().toMap();
			if (fieldMap.contains("template"))
			{
				m_createJobMap.insert(it.key(), fieldMap.value("template"));
			}
		}
	}
}

void OtherAppChangeProcess::initConnect()
{
	connect(m_otherApp.data(), &lpqtconnnOtherApp::sgChangeJobName, this, &OtherAppChangeProcess::onAutoChangeModel);
	connect(this, &lpAutoChangeModel::sgChangeResult, m_otherApp.data(), &lpqtconnnOtherApp::on_send_data);//切换成功或失败给扫码软件发送的反馈
}
