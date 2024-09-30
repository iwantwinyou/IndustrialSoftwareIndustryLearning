/*
file:lpqtconnOtherApp.h
date:2024/9/23
brief:实现和第三方软件之间的数据发送、接收等操作，与第三方软件进行通信模块
author:wuchaoxi
copyright:杭州利珀科技有限公司
*/
#pragma once

#include "lpqtconnotherapp_global.h"
#include "lp_singleton_base.h"
#include "lpqtDefine.h"
#include <QTcpSocket>

class  lpqtconnOtherApp:public lpconnOtherAppBase
{
public:
	lpqtconnOtherApp(const QString& cfg_file = nullptr, QObject *parent = nullptr);
	virtual ~lpqtconnOtherApp();


protected slots:
	void on_connected();
	void on_auto_connect();
	void on_data_received();
	void on_connStatus();
	void on_socketError(QAbstractSocket::SocketError err);
protected:
	void pf_init(const QString& cfg_file = nullptr);
	void pf_readConfig(const QString& cfg_file = nullptr);// ./x64/lpIPUConfig/lpOtherAppConfig.json
	void pf_connectOtherApp(const QString& ip, quint16 port);// 连接到第三方软件的ip地址跟端口号
private:
	bool parseReceivedData();
	void send_data(bool isSucess);//发送反馈数据
	void thrdStart();
	void thrdStop();
private:
	QString m_host_ip;
	quint16 m_port{ 6000 };
	QTimer* m_tm_auto_connect{ nullptr };  // 自动重连       单位: ms 默认:3000ms
	QTcpSocket* m_socket_ptr{nullptr};
	bool m_bPrint{ false };// 是否打印PLC数据包日志
	QString m_recv_package;// OtherApp收到的数据缓存(用于处理OtherApp零碎发送数据)


	QThread *this_thrd_ptr_{ nullptr };//线程管理
};
