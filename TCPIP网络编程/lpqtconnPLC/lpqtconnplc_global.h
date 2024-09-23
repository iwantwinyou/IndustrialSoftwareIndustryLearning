#pragma once

#include <QtCore/qglobal.h>
#include <QtCore>
#include <qobject.h>

#ifndef BUILD_STATIC
# if defined(LPQTCONNPLC_LIB)
#  define LPQTCONNPLC_EXPORT Q_DECL_EXPORT
# else
#  define LPQTCONNPLC_EXPORT Q_DECL_IMPORT
# endif
#else
# define LPQTCONNPLC_EXPORT
#endif

// 注意: PLC的qna3e协议中,存在的最大难点是软件收到的应答无cmd标识(即无法识别是对什么命令的应答)
//     方法1,send型-通用处理 request型-按返回数据长度识别
//     方法2,使用一应一答,软件标记自己的请求（本模块使用此方法）
class LPQTCONNPLC_EXPORT lpconnBasePLC : public QObject
{
	Q_OBJECT
public:
	lpconnBasePLC(const QString& cfg_file=nullptr,QObject* parent = nullptr) :QObject(parent) {};
	virtual ~lpconnBasePLC() {};

	// tools : 各种格式数据转为 PLC数据包 （1字示例: "0001")
	virtual QString fun_getCurTime()=0;// 时间  年/月/日/时/分/秒/毫秒(7字)
	virtual QString fun_ints2HexStr(const QList<int>& vals, int len=4)=0; // len-每个int的长度 常用 4，8
	virtual QString fun_str2HexStr(const QString& src, int num)=0;// num-字符数，src不足时尾部补"00" 1字可包含2字符,因此num一般为偶数

signals:
	// 数据发送  AOI -> PLC
		// 定制
	void sgAOIStart(bool b_start);// 发送AOI检测状态 true-检测中
	void sgAskStatus();    // 请求 缓存中的PLC状态信息
		// 通用
	void sgSendData(const QString& cmd, const QList<int>& vals, bool bAppend = true);// send_xx
	void sgSendDataEx(const QString& cmd, const QString& data, bool bAppend = true); // send_xx
	void sgReadData(const QString& cmd, bool bAppend = true); // read_xx
	void sgAskConnStatus();// 请求 AOI和PLC的连接状态

	// 数据读取  PLC -> AOI
		// 定制
	void sgResultStatis(QVariantMap vm); // <key, int>
	void sgResultStatus(QVariantMap vm); // <key, status_txt>
		// 通用
	void sgResultRead(QString cmd, QVariantMap vm);// 通用 <key,val>
	void sgConnectStatus(bool is_connect);// PLC连接状态
	void sgWarnHeartbeatOut(int t_out);// 心跳已长时间未收到回复

	// 功能接口
	void sgUpdateConfig(const QVariantMap& vmp);// 更新参数,如 b_print
};

LPQTCONNPLC_EXPORT QSharedPointer<lpconnBasePLC> lpCreateConnPLC(const QString& cfg_file = nullptr);
