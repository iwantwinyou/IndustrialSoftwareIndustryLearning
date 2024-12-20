/*
file:lpAutoChangeModel.h
date:2024/8/16
brief:rtp 自动切工单 功能
author:wuchaoxi
copyright:杭州利珀科技有限公司
*/
#pragma once
#include "lpautochangemodel_global.h"
#include "lpqtconnOtherAppDefine.h"
#include "lpqtconnnOtherApp.h"
#include <QMap>
#include<QTimer>
#include <QTime>
class LPAUTOCHANGEMODEL_EXPORT lpAutoChangeModel :public lpAutoChangeModelMgr
{
	Q_OBJECT
public:
	lpAutoChangeModel();
	~lpAutoChangeModel();

public:
	void initConnect();
	//检查plc模板是否与软件模板一致
	bool plcModelMatch2AOI(const QString& plcModel);
	bool OtherAppModelMatch2AOI(const QString& partNum);
	//更新模板列表
	void updateModelList();
signals:
	void sgChangeModel(const QString &model,const QString&jobName);
	void sgChangeResult(bool isSuccess);//发出切换成功或失败的反馈
	void sgSendCurJobInfo(QSharedPointer<QJsonObject>curJobInfo);//把当前工单的数据发出去
public slots:
	//自动切工单
	void onAutoChangeModel(const QString &modelName,const QString &jobName);
	void onRecvCurJob(QSharedPointer<QJsonObject>curJob)override;
	void onRecvModelName(QString cmd, QVariantMap vm)override;
	void onStart(bool isStart)override;
	void onRecvResult()override;
	void onReqModel(); //定时器超时  向plc请求型号
	void onUndetectedTimeout();
private:
	void loadDetectParam(QSharedPointer<QJsonObject> &obj_sptr, const QString &detect_path);
	void loadCreateJobInfo();
private:
	int			m_interval_time{ -1 };
	int			m_undetected_time{ -1 };
	QTimer*		m_timer{ nullptr };
	QTimer*		m_undetected_timer{ nullptr };
	bool		m_isStoped{ true }; //标志位，用于跟踪检测是否已停止
	bool		m_isDetected{ false }; //标志位，标记是否检测到新片

	QMap<QString, QString>		m_map_model_detectparam_;
	QVariantMap  m_model_info_vmp; 
	QString m_cur_model_name; //当前模板名
	QString m_cur_job_name; //当前工单名
	QString m_edgeGrindingHeight;//磨边宽
	QString m_edgeGrindingWidth;//磨边长
	QString m_isEdgeGrinding;//是否磨边
	QString m_customName; //客户名称
	QString m_packNum; //包装数量
	QString m_barCode;
	QSharedPointer<lpqtconnnOtherApp> m_otherApp;
	QVariantMap m_createJobMap;
	QString m_fullMatchModelName;
};
