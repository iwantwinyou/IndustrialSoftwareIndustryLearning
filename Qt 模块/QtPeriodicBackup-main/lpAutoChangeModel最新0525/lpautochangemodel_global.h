#pragma once

#include <QtCore/qglobal.h>
#include <qobject.h>
#include <QJsonObject>
#ifndef BUILD_STATIC
# if defined(LPAUTOCHANGEMODEL_LIB)
#  define LPAUTOCHANGEMODEL_EXPORT Q_DECL_EXPORT
# else
#  define LPAUTOCHANGEMODEL_EXPORT Q_DECL_IMPORT
# endif
#else
# define LPAUTOCHANGEMODEL_EXPORT
#endif
#include <QVariant>
class LPAUTOCHANGEMODEL_EXPORT lpAutoChangeModelMgr :public QObject
{
	Q_OBJECT

public:

	lpAutoChangeModelMgr(QObject *parent = nullptr) :QObject(parent) {}
	virtual ~lpAutoChangeModelMgr() {}

signals:
	void sgStart(bool isStart);
	void sgNewJob(QSharedPointer<QJsonObject>newJob);
	void sgAskCurJob();
	void sgReadData(const QString &cmd, bool bAppend = true); //给plc发送要读的命令
	void sgAlarmPLCEx(const QString& cmd, const QString& data, bool bAppend = true); // 给plc发送的报警
	void sgSendWarning(QString info, int type, QVariant vparam);// 发出报警信息: to UI,log,DB等
	void sgSendMaster2Ui(const QString& key, QJsonObject obj); //封装master_to_ui的数据(cmd固定，key自定义)
public slots:
	virtual void onRecvCurJob(QSharedPointer<QJsonObject>curJob) = 0;
	virtual void onRecvModelName(QString cmd, QVariantMap vm) = 0;
	virtual void onStart(bool isStart) = 0;
	virtual void onRecvResult() = 0; //收到结果
	virtual void onRecvUi2Master(const QString& key, QSharedPointer<QJsonObject> json_sptr) = 0;//从UI收到的信息，此处用来从ui接收到模板或工单切换成功或失败的反馈
	virtual void onRecvUIConnStatus(bool is_connected) = 0;// AOI_UI是否连接到Master

};
typedef QSharedPointer<lpAutoChangeModelMgr>LPAUTOCHANGEMODEL_SPTR;
LPAUTOCHANGEMODEL_EXPORT QSharedPointer<lpAutoChangeModelMgr>lpCreateAutoModelChange();