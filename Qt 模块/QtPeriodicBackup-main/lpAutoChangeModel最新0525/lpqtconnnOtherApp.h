/*
file:lpqtconnOtherApp.h
date:2024/11/22
brief:实现和第三方软件之间的数据发送、接收等操作，与第三方软件进行通信模块
author:wuchaoxi
copyright:杭州利珀科技有限公司
*/
#pragma once
#include <qobject.h>
#include <QtCore>
#include <QTcpSocket>
#include <QTcpServer>
#include "lpqtconnOtherAppDefine.h"
class lpqtconnnOtherApp :public QObject
{
	Q_OBJECT
public:
	lpqtconnnOtherApp(QObject *parent=nullptr);
	~lpqtconnnOtherApp();

signals:
	void sgChangeJobName(const QString &modelName, const QString &jobName);
protected:
	void loadConfig();
public slots:
	void onNewConnection();
	void on_data_received();
	void on_socketError(QAbstractSocket::SocketError err);
	void on_send_data(bool isSucess);//发送反馈数据
	void on_close();//程序退出时进行清理
private:
	void initServer();
	void closeServer();
	bool parseReceivedData();



private:
	QString m_host_ip;
	quint16 m_port{ 6000 };
	bool m_bPrint{ false };// 是否打印第三方软件数据包日志
	QString m_recv_package;// OtherApp收到的数据缓存(用于处理OtherApp零碎发送数据)
	QTcpServer *m_tcpServer;//server用于监听端口，获取新的tcp连接的描述符
	QTcpSocket *m_tcpSocket;

};

