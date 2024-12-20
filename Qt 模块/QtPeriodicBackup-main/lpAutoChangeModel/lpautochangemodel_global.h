#pragma once

#include <QtCore/qglobal.h>
#include <qobject.h>
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
	void sgPartDbReady();//发出数据库准备就绪的信号
public slots:
	virtual void onRecvCurJob(QSharedPointer<QJsonObject>curJob) = 0;
	virtual void onRecvModelName(QString cmd, QVariantMap vm) = 0;
	virtual void onStart(bool isStart) = 0;
	virtual void onRecvResult() = 0; //收到结果

};
typedef QSharedPointer<lpAutoChangeModelMgr>LPAUTOCHANGEMODEL_SPTR;
LPAUTOCHANGEMODEL_EXPORT QSharedPointer<lpAutoChangeModelMgr>lpCreateAutoModelChange();