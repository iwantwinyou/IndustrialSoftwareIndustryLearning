#pragma once

#include "lpqtconnplc_global.h"
#include <QtNetwork>
#include "lpqtDefine.h"

class lpqtconnPLC : public lpconnBasePLC
{
	Q_OBJECT
public:
	lpqtconnPLC(const QString& cfg_file = nullptr, QObject *parent = nullptr);
	virtual ~lpqtconnPLC();

	// tools : 各种格式数据转为 PLC数据包 （1字示例: "0001")
	QString fun_getCurTime();// 时间  年/月/日/时/分/秒/毫秒(7字)
	QString fun_ints2HexStr(const QList<int>& vals, int len = 4); // len-每个int的长度 常用 4，8
	QString fun_str2HexStr(const QString& src, int num);// num-字符数，src不足时尾部补"00" 1字可包含2字符,因此num一般为偶数


public slots:
	void on_send_data(const QString& cmd,const QList<int>& vals, bool bAppend=true);
	void on_send_data_ex(const QString& cmd, const QString& data, bool bAppend = true);// 直接发送组好的数据包
	void on_read_data(const QString& cmd,bool bAppend=true);
	void on_aoi_start(bool b_start);
	void on_connStatus();// 获取连接状态
	void on_read_cache_status();// 从本地缓存中读取运行状态
	void on_update_config(const QVariantMap& vmp);

protected:
	void pf_init(const QString& cfg_file = nullptr);
	void pf_readConfig(const QString& cfg_file = nullptr);// ./x64/lpIPUConfig/lpPLCConfig.json
	void pf_connectPLC(const QString& ip, quint16 port);// 连接到PLC
	
	void send_binary_dataEx();// 从缓存中取数据发送
	void send_binary_dataEx(const QByteArray& data, const QString&cmd, bool bAppend=true);// 添加一条发送数据

	void pf_analyze(const QString& cmd, const QString& data);

protected slots:
	void on_connected();
	void on_disconnected();
	void on_socket_error(QAbstractSocket::SocketError err);
	void on_data_received();

	void on_auto_connect();
	void on_send_heartbeat();
	void on_ask_statis();
	void on_ask_status();
	void on_guard_plc();//plc守护

private:
	void send_binary_data(const QByteArray& data, const QString& cmd);// 执行具体的发送数据
	QString makeAddr(const QString& srcAddr);
	QString int_to_hex_str(int val, int len=4);
	void pf_VList2StrList(QVariantList& v_in, QStringList& out);
	void pf_praseReg(QJsonObject& jreg, TPLCReadCell& rc);
	void pf_praseDiy(QJsonObject& jdiy, TPLCReadCell& rc);
	QString get_recv_package();//从PLC数据缓存中提取数据处理
	bool praseString(QString &val_total, QVariant& out_val, int w_num, int type=0, bool b_auto_del=false);

	void thrdStart();
	void thrdStop();

	Q_SLOT void on_close();// 程序退出时进行清理

signals:
	void sgClose();

private:
	QString m_host_ip;
	quint16 m_port{ 1025 };
	QTcpSocket* m_sock_ptr{ nullptr };

	int m_sp_statis_{ 1 };// 单位: s  默认:1s
	int m_sp_status_{ 1 };// 单位: s  默认:1s
	int m_sp_guard_{ 1 }; // 单位: 分钟 默认: 1分钟
	QTimer* m_tm_auto_connect{ nullptr };  // 自动重连       单位: ms 默认:3000ms
	QTimer* m_tm_heart_beat_{ nullptr }; // 心跳包发送       单位: ms 默认:1000ms
	QTimer* m_tm_statis_{ nullptr };// 定时请求 数据统计     单位: s  默认:1s
	QTimer* m_tm_status_{ nullptr };// 定时请求 运行状态     单位: s  默认:1s
	QTimer* m_tm_guard_{ nullptr };// 守护时钟               单位: 分钟 默认: 1分钟
	bool m_b_can_statis{ true };// true-可以发送新的 false-需等待上一次完成
	bool m_b_can_status{ true };
	bool m_b_guard_{ true };// 守护监测 true-表示安全(有收到数据) false-监测标记(若下次进入还是false，说明出现了数据接收异常)
	bool m_bCanSend{ true };// 是否可以发送请求：用于一应一答中，判断是否可以进行下一次发送 true-可以 false-不可以
	QList<QPair<QString, QByteArray>> m_ls_send;// 发送缓存
	QPair<QString,QByteArray> m_cur_send;// 当前发送的命令,配合守护使用
	int m_heartbeat_count_{ 0 };// 心跳计数
	int m_heartbeat_out_{ 0 };// 心跳断开时间计数
	int m_heartbeat_out_sp{ 0 };// >1 时,表示开启心跳断开报警

	QString m_recv_package;// PLC收到的数据缓存(用于处理PLC零碎发送数据)
	
	bool m_bPrint{ false };// 是否打印PLC数据包日志
	int m_nWorkStatus{ 2 };// 1-正在检测 2-停止检测
	QMap<int, int>	m_mp_plc_status_;// <pos, status>
	QVariantMap m_mp_plc_status_s;//<addr, txt>

	QMap<QString, QString> m_mpSendAddr;// <cmd, addr>
	QMap<QString, TPLCReadCell> m_mpReadAddr;//<cmd, cell>

	QThread *this_thrd_ptr_{ nullptr };//线程管理
};
