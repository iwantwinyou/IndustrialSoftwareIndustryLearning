#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(LPQTCONNOTHERAPP_LIB)
#  define LPQTCONNOTHERAPP_EXPORT Q_DECL_EXPORT
# else
#  define LPQTCONNOTHERAPP_EXPORT Q_DECL_IMPORT
# endif
#else
# define LPQTCONNOTHERAPP_EXPORT
#endif

#include <QtCore/qglobal.h>
#include <QtCore>
#include <QObject>
class LPQTCONNOTHERAPP_EXPORT lpconnOtherAppBase :public QObject
{
	Q_OBJECT
public:
	lpconnOtherAppBase(const QString& cfg_file = nullptr, QObject* parent = nullptr) :QObject(parent) {};
	virtual ~lpconnOtherAppBase() {};

signals:
	//数据发送  AOI -> OtherApp
	//通用
	void sgAskConnStatus();// 请求 AOI和OtherApp的连接状态
	//数据读取  OtherApp -> AOI
	//通用
	void sgConnectStatus(bool is_connect);// OtherApp连接状态
	void sgChangeJobName(const QString &modelName,const QString &jobName);

};

typedef QSharedPointer<lpconnOtherAppBase>LPCONNOTHERAPPBASE_SPTR;
LPQTCONNOTHERAPP_EXPORT QSharedPointer<lpconnOtherAppBase> lpCreateConnOtherApp(const QString& cfg_file = nullptr);