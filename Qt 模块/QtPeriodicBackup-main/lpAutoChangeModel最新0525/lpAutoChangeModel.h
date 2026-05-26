/*
file:lpAutoChangeModel.h
date:2024/8/16
brief:rtp 自动切工单 功能
author:wuchaoxi
copyright:杭州利珀科技有限公司
*/
#pragma once
#include "lpautochangemodel_global.h"
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
	//检查plc模板是否与软件模板一致
	bool plcModelMatch2AOI(const QString& plcModel);
	bool OtherAppModelMatch2AOI(const QString& partNum);
	//更新模板列表
	void updateModelList();
	QString getCurrentModelName()const;
	QString getCurrentJobName()const;
	QMap<QString, QString>getModelDetectparam()const;
signals:
	void sgChangeModel(const QString &model,const QString&jobName);
	void sgChangeResult(bool isSuccess);//发出切换成功或失败的反馈
public slots:
	//自动切工单
	virtual void onAutoChangeModel(const QString &modelName, const QString &jobName)=0;
	void onRecvCurJob(QSharedPointer<QJsonObject>curJob)override;
private:
	QMap<QString, QString>		m_map_model_detectparam_;
	QString m_cur_model_name; //当前模板名
	QString m_cur_job_name; //当前工单名
	QString m_fullMatchModelName;//完整配方名，第三方app切换发送过来的可能不是完整的配方名
};

//PLC切换类
class PLCChangeProcess :public lpAutoChangeModel
{
	Q_OBJECT
public:
	PLCChangeProcess();
	~PLCChangeProcess();
public slots:
	void onStart(bool isStart)override;
	void onRecvResult()override;
	void onRecvModelName(QString cmd, QVariantMap vm)override;
	void onAutoChangeModel(const QString &modelName, const QString &jobName)override;
	void onRecvUi2Master(const QString& key, QSharedPointer<QJsonObject> json_sptr)override;
	void onRecvUIConnStatus(bool is_connected)override;
private slots:
	void onReqModel(); //定时器超时  向plc请求型号
	void onUndetectedTimeout();
private:
	void initConnect();
private:
	bool		m_isStoped{ true }; //标志位，用于跟踪检测是否已停止
	int			m_interval_time{ -1 };
	int			m_undetected_time{ -1 };
	QTimer*		m_timer{ nullptr };
	QTimer*		m_undetected_timer{ nullptr };
	bool		m_connected{false};//判断UI是否连接,ui打开才发送换工单的信号
};

//第三方app切换
class OtherAppChangeProcess :public lpAutoChangeModel
{
	Q_OBJECT
public:
	OtherAppChangeProcess();
	~OtherAppChangeProcess();

public slots:
	void onStart(bool isStart)override;
	void onRecvResult()override;
	void onRecvModelName(QString cmd, QVariantMap vm)override;
	void onAutoChangeModel(const QString &modelName, const QString &jobName)override;
	void onRecvUi2Master(const QString& key, QSharedPointer<QJsonObject> json_sptr)override;
	void onRecvUIConnStatus(bool is_connected)override;
private:
	void loadCreateJobInfo();
	void initConnect();
private:
	QSharedPointer<lpqtconnnOtherApp> m_otherApp;
	QVariantMap m_createJobMap;
	bool m_connected{false};//判断UI是否连接,ui打开才发送换工单的信号
};
