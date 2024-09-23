#include "lpqtconnPLC.h"

#pragma execution_character_set("utf-8")
//////////////////////////////////////////////////////////////////////////
QSharedPointer<lpconnBasePLC> lpCreateConnPLC(const QString& cfg_file)
{
	return QSharedPointer<lpconnBasePLC>(new lpqtconnPLC(cfg_file));
}

//////////////////////////////////////////////////////////////////////////
lpqtconnPLC::lpqtconnPLC(const QString& cfg_file/* = nullptr*/, QObject *parent /*= nullptr*/)
	:lpconnBasePLC(cfg_file, parent)
{
	qDebug() << "connPLC_V1.0.5.0" << __FUNCTION__;

	qRegisterMetaType<QList<int>>("QList<int>");

	pf_init(cfg_file);
}

lpqtconnPLC::~lpqtconnPLC()
{
	qDebug() << __FUNCTION__;
	emit sgClose();
	thrdStop();
}

void lpqtconnPLC::on_send_data(const QString& cmd, const QList<int>& vals, bool bAppend/* = true*/)
{// PLC组包: head + Len1 + head_send + addr + Len2 + data
	if (cmd.isEmpty() || vals.count() < 1) return;
	if (!m_mpSendAddr.contains(cmd)) {
		qWarning() << cmd << "addr is null!" << __FUNCTION__;
		return;
	}
	if (cmd == PLCDATA::C_START)
		m_nWorkStatus = vals.first();
	QString data_str;
	auto& addr = m_mpSendAddr.value(cmd);
	int len1 = (6 + vals.count()) * 4;
	int len2 = vals.count();
	// 组包
	data_str = PLCDATA::head + int_to_hex_str(len1) + PLCDATA::head_send
		+ addr + int_to_hex_str(len2);
	for (auto val : vals)
		data_str += int_to_hex_str(val);
	// 发送
	send_binary_dataEx(data_str.toUtf8(), cmd, bAppend);
}

void lpqtconnPLC::on_send_data_ex(const QString& cmd, const QString& data, bool bAppend /*= true*/)
{
	if (cmd.isEmpty() || data.count() < 4) return;
	if (!m_mpSendAddr.contains(cmd)) {
		qWarning() << cmd << "addr is null!" << __FUNCTION__;
		return;
	}
	QString data_str;
	auto& addr = m_mpSendAddr.value(cmd);
	int num_data = data.count() / 4;
	int len1 = (6 + num_data) * 4;
	int len2 = num_data;
	// 组包
	data_str = PLCDATA::head + int_to_hex_str(len1) + PLCDATA::head_send
		+ addr + int_to_hex_str(len2);
	data_str += data.left(num_data * 4);
	// 发送
	send_binary_dataEx(data_str.toUtf8(), cmd, bAppend);
}

void lpqtconnPLC::on_read_data(const QString& cmd, bool bAppend/* = true*/)
{// PLC组包: head + "0018" + head_read + addr + Len2 
	if (cmd.isEmpty()) return;
	if (!m_mpReadAddr.contains(cmd)) {
		qWarning() << cmd << "addr is null!" << __FUNCTION__;
		return;
	}
	QString data_str;
	auto& rc = m_mpReadAddr.value(cmd);
	// 组包
	data_str = PLCDATA::head + PLCDATA::len1_read + PLCDATA::head_read
		+ rc.addr + int_to_hex_str(rc.cnt);

	// 发送
	send_binary_dataEx(data_str.toUtf8(), cmd, bAppend);
}

void lpqtconnPLC::on_aoi_start(bool b_start)
{
	m_nWorkStatus = (b_start ? 1 : 2);
	on_send_data(PLCDATA::C_START, QList<int>()<<m_nWorkStatus);
}

void lpqtconnPLC::on_connStatus()
{
	bool b_conn = false;
	if (m_sock_ptr) {
		b_conn = (m_sock_ptr->state() == QAbstractSocket::SocketState::ConnectedState);
	}
	emit sgConnectStatus(b_conn);
}

void lpqtconnPLC::on_read_cache_status()
{
	if(m_mp_plc_status_s.count()>0)
		emit sgResultStatus(m_mp_plc_status_s);
}

void lpqtconnPLC::on_update_config(const QVariantMap& vmp)
{
	if(vmp.contains("b_print"))
		m_bPrint = vmp.value("b_print").toBool();
	if (vmp.contains("tcp_server_ip") || vmp.contains("tcp_server_port")) {
		QString host_ip = vmp.value("tcp_server_ip", m_host_ip).toString();
		quint16 port = vmp.value("tcp_server_port", m_port).toInt();
		if(host_ip!=m_host_ip || port!=m_port)
			pf_connectPLC(m_host_ip=host_ip, m_port=port);
	}
}

void lpqtconnPLC::pf_init(const QString& cfg_file/* = nullptr*/)
{
	pf_readConfig(cfg_file);

	// socket初始化
	m_sock_ptr = new QTcpSocket(this);
	m_sock_ptr->setSocketOption(QAbstractSocket::SendBufferSizeSocketOption, 1024);
	m_sock_ptr->setSocketOption(QAbstractSocket::KeepAliveOption, true);
	connect(m_sock_ptr, &QTcpSocket::connected,	this, &lpqtconnPLC::on_connected);
	connect(m_sock_ptr, &QTcpSocket::disconnected,this, &lpqtconnPLC::on_disconnected);
	connect(m_sock_ptr, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(on_socket_error(QAbstractSocket::SocketError)));
	connect(m_sock_ptr, &QTcpSocket::readyRead,	this, &lpqtconnPLC::on_data_received);

	// 心跳包
	m_tm_heart_beat_ = new QTimer(this);
	connect(m_tm_heart_beat_, &QTimer::timeout,	this, &lpqtconnPLC::on_send_heartbeat);
	if (m_sp_statis_ > 0) {// 统计数据
		m_tm_statis_ = new QTimer(this);
		connect(m_tm_statis_, &QTimer::timeout, this, &lpqtconnPLC::on_ask_statis);
	}
	if (m_sp_status_ > 0) {// PLC状态
		m_tm_status_ = new QTimer(this);
		connect(m_tm_status_, &QTimer::timeout, this, &lpqtconnPLC::on_ask_status);
	}

	// 断线重连时钟
	m_tm_auto_connect = new QTimer(this);
	connect(m_tm_auto_connect, &QTimer::timeout, this, &lpqtconnPLC::on_auto_connect);

	// 添加守护 : 自动重发上次未发送成功的命令
	if (m_sp_guard_ > 0) {
		m_tm_guard_ = new QTimer(this);
		connect(m_tm_guard_, &QTimer::timeout, this, &lpqtconnPLC::on_guard_plc);
	}

	// 内部消息传递，主要用于进入线程
	connect(this, &lpqtconnPLC::sgAOIStart, this, &lpqtconnPLC::on_aoi_start);
	connect(this, &lpqtconnPLC::sgSendData, this, &lpqtconnPLC::on_send_data);
	connect(this, &lpqtconnPLC::sgSendDataEx, this, &lpqtconnPLC::on_send_data_ex);
	connect(this, &lpqtconnPLC::sgReadData, this, &lpqtconnPLC::on_read_data);
	connect(this, &lpqtconnPLC::sgAskConnStatus, this, &lpqtconnPLC::on_connStatus);
	connect(this, &lpqtconnPLC::sgAskStatus, this, &lpqtconnPLC::on_read_cache_status);
	connect(this, &lpqtconnPLC::sgClose, this, &lpqtconnPLC::on_close, Qt::BlockingQueuedConnection);
	connect(this, &lpqtconnPLC::sgUpdateConfig, this, &lpqtconnPLC::on_update_config);

	// 连接PLC
	pf_connectPLC(m_host_ip, m_port);

	this_thrd_ptr_ = new QThread;
	this->moveToThread(this_thrd_ptr_);
	thrdStart();// 自动启动线程
}

void lpqtconnPLC::pf_readConfig(const QString& cfg_file/* = nullptr*/)
{
	QString cfg_path = PLCDATA::CFG_PATH;
	if (!cfg_file.isEmpty())
		cfg_path = cfg_file;
	QFile file(cfg_path);
	if (!file.open(QFile::ReadOnly | QIODevice::Text)) {
		qWarning() << "read failed!" << cfg_path << __FUNCTION__;
		return;
	}
	QJsonObject obj = QJsonDocument::fromJson(file.readAll()).object();
	file.close();
	// 配置
	QJsonObject j1 = obj.value("config").toObject();
	m_host_ip = j1.value("tcp_server_ip").toString();
	m_port = j1.value("tcp_server_port").toInt(1025);
	m_bPrint = j1.value("b_print").toBool();
	m_sp_statis_ = j1.value("t_statis_s").toInt();
	m_sp_status_ = j1.value("t_status_s").toInt();
	m_heartbeat_out_sp = j1.value("t_heartbeat_out_warn").toInt(0);
	// 协议
	j1 = obj.value("protocol").toObject();
	foreach(auto cmd, j1.keys()) {
		if (cmd.startsWith("send_")) {
			QString addr = j1.value(cmd).toString();
			if (addr.isEmpty()) 
				continue;
			m_mpSendAddr[cmd] = makeAddr(addr);
		}
		else if (cmd.startsWith("read_")) {
			QJsonObject j2 = j1.value(cmd).toObject();
			TPLCReadCell rc;
			rc.addr = j2.value("addr").toString();
			rc.cnt = j2.value("cnt").toInt();
			pf_VList2StrList(j2.value("keys").toVariant().toList(), rc.keys);
			if (rc.addr.isEmpty() || rc.cnt<1)
				continue;
			rc.addr = makeAddr(rc.addr);
			rc.decode_type = (int)emDecodeType::D_NULL;
			if (rc.keys.count() > 0)
				rc.decode_type = (int)emDecodeType::D_KEY;
			else if(j2.contains("reg"))
				pf_praseReg(j2.value("reg").toObject(), rc);
			else if(j2.contains("diy"))
				pf_praseDiy(j2.value("diy").toObject(), rc);
			m_mpReadAddr[cmd] = rc;
		}
	}

	qDebug() << "load end." << cfg_path << __FUNCTION__;
}

void lpqtconnPLC::pf_praseReg(QJsonObject& jreg, TPLCReadCell& rc)
{
	foreach(auto pos_, jreg.keys()) {
		QJsonObject obj = jreg.value(pos_).toObject();
		TPLCRegCell reg;
		reg.addr = pos_;
		reg.ok_val = obj.value("true_value").toInt(0);
		reg.ok_txt = obj.value("true_alias").toString();
		reg.ng_val = obj.value("false_value").toInt(1);
		reg.ng_txt = obj.value("false_alias").toString();
		rc.mpRegs[pos_] = reg;
	}
	if(rc.mpRegs.count()>0)
		rc.decode_type = (int)emDecodeType::D_REG;
}
void lpqtconnPLC::pf_praseDiy(QJsonObject& jdiy, TPLCReadCell& rc)
{
	// 加载diy配置
	foreach(auto pos_, jdiy.keys()) {
		QJsonObject obj = jdiy.value(pos_).toObject();
		TPLCDecodeCell diy;
		diy.addr_pos = pos_;
		diy.key_ = obj.value("key").toString(pos_);
		diy.cnt = obj.value("cnt").toInt();
		diy.data_type = obj.value("type").toInt((int)emDataType::PLC_SOURCE);
		if (diy.cnt < 1) continue;
		rc.mpDecodes[pos_] = diy;
	}
	// 类型
	if (rc.mpDecodes.count() > 0)
		rc.decode_type = (int)emDecodeType::D_DIY;
}

void lpqtconnPLC::pf_connectPLC(const QString& ip, quint16 port)
{
	qDebug() << ip << port<< __FUNCTION__;
	// 连接状态下，先断开原连接
	if (m_sock_ptr->state() == QAbstractSocket::SocketState::ConnectedState) {
		m_sock_ptr->abort();
		m_sock_ptr->close();
	}
	if (m_tm_auto_connect->isActive())
		m_tm_auto_connect->stop();
	if (ip.isEmpty()) {
		qWarning() << "tcp_server_ip is empty!" << __FUNCTION__;
		return;
	}
	// 进行连接
	m_sock_ptr->connectToHost(ip, port);
	if (!m_sock_ptr->waitForConnected(100)) {// 连接失败，触发重连机制
		qWarning() << "connect to PLC failed!" << ip << port << __FUNCTION__;
		m_tm_auto_connect->start(3000);
		return;
	}
	//qDebug() << "connect to PLC successful." << ip << port << __FUNCTION__;
}

void lpqtconnPLC::send_binary_data(const QByteArray& data, const QString& cmd)
{
	m_cur_send = qMakePair(cmd, data);
	m_bCanSend = false;
	if (m_sock_ptr->state() != QAbstractSocket::SocketState::ConnectedState)
		return;
	
	m_sock_ptr->write(data.constData(), data.size());
	m_sock_ptr->flush();
	if (m_bPrint)
		qDebug() << "send. cmd=" << cmd << data << __FUNCTION__;
}

QString lpqtconnPLC::makeAddr(const QString& srcAddr)
{
	if (srcAddr.size() > 6)
		return srcAddr.right(6);
	QString addr_ = srcAddr;
	for (int n = srcAddr.size(); n < 6; n++)
		addr_ = "0" + addr_;
	return addr_;
}

QString lpqtconnPLC::int_to_hex_str(int val, int len/*=4*/)
{
	QString hexstr = QString::number(val, 16);//表示转换成16进制存入字符串
	while (hexstr.length() < len) {
		hexstr.push_front("0");
	}
	if (hexstr.length() > len  && len > 0)// val长度超出预期时，只保留低位值信息
		hexstr = hexstr.right(len);
	return hexstr.toUpper();
}

void lpqtconnPLC::pf_VList2StrList(QVariantList& v_in, QStringList& out)
{
	for (auto it : v_in)
		out << it.toString();
}

void lpqtconnPLC::send_binary_dataEx()
{
	if (!m_bCanSend) return;
	if (m_ls_send.size() < 1) return;
	auto data = m_ls_send.takeFirst();// 防止断线时值堆积，因此先取数，再判断是否连接
	send_binary_data(data.second, data.first);
}

// 添加一条发送数据
// bAppend=true-从尾部新增一条 false-从头部插队(主要用于心跳)
// 优化: 新cmd到时,检索发送list中是否有对应的cmd,有则内容进行替换;无则原逻辑进行fi
void lpqtconnPLC::send_binary_dataEx(const QByteArray& data, const QString&cmd, bool bAppend/* = true*/)
{
	bool bFind = false;
	// 先进行检索队列中cmd, 有则替换data
	for (int i = 0; i < m_ls_send.size(); i++) {
		auto& pv = m_ls_send[i];
		if (pv.first == cmd) {
			bFind = true;
			pv.second = data;
		}
	}
	// 未检索到的cmd按规则添加到队列中
	if (!bFind) {// 
		auto p = qMakePair(cmd, data);
		if (bAppend)
			m_ls_send << p;
		else
			m_ls_send.prepend(p);
	}
	send_binary_dataEx();
}

void lpqtconnPLC::on_connected()
{// 连接成功
	qDebug() << "connect to PLC successful." << m_host_ip << m_port << __FUNCTION__;
	// 操作处理
	m_tm_auto_connect->stop();
	m_heartbeat_count_ = 0;
	m_heartbeat_out_ = 0;
	m_tm_heart_beat_->start(1000);
	if (m_tm_guard_)
		m_tm_guard_->start(std::chrono::minutes(m_sp_guard_));
	if (m_tm_statis_)
		m_tm_statis_->start(std::chrono::seconds(m_sp_statis_));
	if (m_tm_status_)
		m_tm_status_->start(std::chrono::seconds(m_sp_status_));

	m_bCanSend = true;
	m_b_guard_ = true;
	sgConnectStatus(true);
}

void lpqtconnPLC::on_disconnected()
{
	qWarning() << "PLC is not connected!" << __FUNCTION__;
	// [注]: 断开时，需将当前发送未成功的命令进行回收，用于重连后的发送
	if (!m_bCanSend && !m_cur_send.second.isEmpty()) {
		m_ls_send.prepend(m_cur_send);
		m_bCanSend = true;
		m_cur_send = QPair<QString,QByteArray>();
	}
	emit sgConnectStatus(false);
}

void lpqtconnPLC::on_socket_error(QAbstractSocket::SocketError err)
{
	if (!m_sock_ptr) return;
	qWarning() << QString("Socket error(%1): %2").arg(err).arg(m_sock_ptr->errorString()) << __FUNCTION__;
	m_sock_ptr->abort();
	m_sock_ptr->close();
	if(!m_tm_auto_connect->isActive())// 未启动时启动自动连接
		m_tm_auto_connect->start(3000);
	//emit sgConnectStatus(false);
}

QString lpqtconnPLC::get_recv_package()
{// 返回去掉头后的数据内容 Len + "0000" + data
	static int head_len = QString(PLCDATA::recv_head).size();
	if (!m_recv_package.contains(PLCDATA::recv_head))
		return "";//无完整有效数据
	if (!m_recv_package.startsWith(PLCDATA::recv_head)) {
		qWarning() << "PLC_remove_invalid_data " << __FUNCTION__;
		m_recv_package.remove(0, m_recv_package.indexOf(PLCDATA::recv_head));// 去掉冗余数据
	}
	if (m_recv_package.size() < (head_len + 4))
		return "";//数据不足
	// 解析数据长度
	bool ok;
	int len = m_recv_package.mid(head_len, 4).toInt(&ok, 16);
	if (!ok) {
		// 出现无法解析的数据，此时进行丢弃
		m_recv_package.remove(0, head_len + 4);
		return get_recv_package();
	}
	// 根据长度判断数据量是否足够
	if (m_recv_package.size() < (head_len + len + 4))
		return "";//数据不足
	// 返回去掉头后的数据内容
	QString res = m_recv_package.mid(head_len, len + 4);
	m_recv_package.remove(0, head_len + len + 4);
	return res;
}

// b_auto_del=true-自动移除解析数据 false-不移除
bool lpqtconnPLC::praseString(QString &val_total, QVariant& out_val, int w_num, int type,bool b_auto_del)
{
	bool ok;
	int len = val_total.length();
	if (len < (w_num * 4))
		return false;//数据量不足，不进行解析
	if (w_num < 1) return false;
	len = w_num * 4;
	switch (type)
	{
		case (int)emDataType::PLC_INT://  int	w_num=1
			out_val = val_total.left(4 * w_num).toInt(&ok, 16);
			break;
		case (int)emDataType::PLC_SID://  sid "1,2,3"  多个int组成一个string,用逗号隔开
		{
			QString val;
			for (int i = 0; i < w_num; i++)
				val += QString("%1,").arg(val_total.mid(i * 4, 4).toInt(&ok, 16));
			val.chop(1);
			out_val = val;
			break;
		}
		case (int)emDataType::PLC_TIME:// time w_num=7  2023-09-01 12:12:22.000
		{
			if (w_num != 7)
				return false;
			QString val = QString("%1-%2-%3 %4:%5:%6.%7")
				.arg(val_total.mid(0 * 4, 4).toInt(&ok, 16), 4, 10, QChar('0'))		// 年
				.arg(val_total.mid(1 * 4, 4).toInt(&ok, 16), 2, 10, QChar('0'))		// 月
				.arg(val_total.mid(2 * 4, 4).toInt(&ok, 16), 2, 10, QChar('0'))		// 日
				.arg(val_total.mid(3 * 4, 4).toInt(&ok, 16), 2, 10, QChar('0'))		// 时
				.arg(val_total.mid(4 * 4, 4).toInt(&ok, 16), 2, 10, QChar('0'))		// 分
				.arg(val_total.mid(5 * 4, 4).toInt(&ok, 16), 2, 10, QChar('0'))		// 秒
				.arg(val_total.mid(6 * 4, 4).toInt(&ok, 16), 3, 10, QChar('0'));	// 毫秒
			out_val = val;
			break;
		}
		case (int)emDataType::PLC_STR:// panel_id/lot_id/string
		{
			QString val = val_total.mid(0, len);
			out_val = QString(QByteArray::fromHex(val.toLatin1()));
			break;
		}
		case (int)emDataType::PLC_SOURCE:
		default:
		{
			out_val = val_total.mid(0, len);
			break;
		}
	}
	if(b_auto_del)
		val_total = val_total.mid(len);

	return true;
}

void lpqtconnPLC::pf_analyze(const QString& cmd, const QString& data)
{
	if (!m_mpReadAddr.contains(cmd)) return;
	auto& p = m_mpReadAddr.value(cmd);
	QString total = data.mid(8);// 去除 len+"0000", 提取data部分
	switch (p.decode_type)
	{
		case (int)emDecodeType::D_KEY:
		{
			QVariantMap vmp;
			for (auto key : p.keys) {
				QVariant val;
				if( !praseString(total, val, 1, (int)emDataType::PLC_INT, true))
					break;
				vmp[key] = val;
			}
			if (cmd == PLCDATA::C_STATIS)
				emit sgResultStatis(vmp);
			else
				emit sgResultRead(cmd, vmp);
			break;
		}
		case (int)emDecodeType::D_REG:// read_status
		{
			QVariantMap vmp;
			foreach(auto reg, p.mpRegs) {
				int reg_pos = reg.addr.toInt() - p.addr.toInt();
				if (reg_pos < 0)
					continue;
				QVariant val;
				if( !praseString(total.mid(reg_pos*4), val, 1, (int)emDataType::PLC_INT))
					break;
				int val_n = val.toInt();
				QString txt=QString("warn:%1 返回了未知值:%2").arg(reg.addr).arg(val_n);
				if (val_n == reg.ok_val)
					txt = reg.ok_txt;
				else if (val_n == reg.ng_val)
					txt = "warn:" + reg.ng_txt;
				if (cmd == PLCDATA::C_STATUS) {// PLC状态 : 进行缓存
					if (m_mp_plc_status_.value(reg_pos, -1) != val_n) {
						vmp[reg.addr] = txt;
						m_mp_plc_status_[reg_pos] = val_n;
						m_mp_plc_status_s[reg.addr] = txt;
					}
				}
				else
					vmp[reg.addr] = txt;// 通用方法 （注：此处无需识别txt是否为空,应有接收者自行处理）
			}
			if (cmd == PLCDATA::C_STATUS) {
				if (vmp.count() > 0)
					emit sgResultStatus(vmp);// 定制: 发送变化的内容(空的也发送)
			}
			else
				emit sgResultRead(cmd, vmp); // 通用: 全发送
			break;
		}
		case (int)emDecodeType::D_DIY:
		{
			QVariantMap vmp;
			foreach(auto diy, p.mpDecodes) {
				int pos_ = diy.addr_pos.toInt() - p.addr.toInt();
				if (pos_ < 0)
					continue;
				QVariant val;
				if (!praseString(total.mid(pos_ * 4), val, diy.cnt, diy.data_type))
					break;
				vmp[diy.key_] = val;
			}
			emit sgResultRead(cmd, vmp);
			break;
		}
		case (int)emDecodeType::D_NULL:
		default:
		{
			QVariantMap vmp;
			vmp[p.addr] = total;
			emit sgResultRead(cmd, vmp);
			break;
		}
	}
}

void lpqtconnPLC::on_data_received()
{
	QString data_recv = m_sock_ptr->readAll();
	QString cmd = m_cur_send.first;
	if (m_bPrint)
		qDebug() <<"recv. cmd="<<cmd << data_recv << __FUNCTION__;
	m_recv_package.append(data_recv);
	bool b_recv_ok = false;
	while (1) {// 需要将数据处理完
		QString pack_str = get_recv_package();
		if (pack_str.count() < 4)
			break;
		
		b_recv_ok = true;
		if (cmd == PLCDATA::C_HEART)
			m_heartbeat_out_ = 0;
		if(cmd.startsWith("send_"))
			continue;

		if (cmd == PLCDATA::C_STATIS) // PLC 计数应答
			m_b_can_statis = true;
		else if (cmd == PLCDATA::C_STATUS) 	// PLC 设备状态信息应答
			m_b_can_status = true;

		if (cmd.startsWith("read_")) 
			pf_analyze(cmd, pack_str);
	}
	if (b_recv_ok) {
		m_b_guard_ = true;
		m_bCanSend = true;
		send_binary_dataEx();
	}
	else
		qWarning() << "imperfect recv. cur cache: " << m_recv_package << __FUNCTION__;
}

void lpqtconnPLC::on_auto_connect()
{
	if (m_sock_ptr->state() == QAbstractSocket::SocketState::ConnectingState) 
		return;
	if (m_sock_ptr->state() == QAbstractSocket::SocketState::ConnectedState)
		return;
	
	m_sock_ptr->abort();
	m_sock_ptr->close();
	m_sock_ptr->connectToHost(m_host_ip, m_port);
	qDebug() << "PLC reconnecting..." << m_host_ip << m_port << __FUNCTION__;
}

void lpqtconnPLC::on_send_heartbeat()
{// 心跳
	if (m_sock_ptr->state() != QAbstractSocket::SocketState::ConnectedState) {
		m_tm_heart_beat_->stop();// 断开时，停止心跳包
		return;
	}
	m_heartbeat_count_++;
	if (m_heartbeat_count_ >= 65535) 
		m_heartbeat_count_ = 0;

	m_heartbeat_out_++;
	if (m_heartbeat_out_sp > 1 && m_heartbeat_out_ > m_heartbeat_out_sp)
		emit sgWarnHeartbeatOut(m_heartbeat_out_);

	on_send_data(PLCDATA::C_HEART, QList<int>() << m_heartbeat_count_<< m_nWorkStatus, false);
}

void lpqtconnPLC::on_ask_statis()
{// 计数请求
	if (m_sock_ptr->state() != QAbstractSocket::SocketState::ConnectedState) {
		m_tm_statis_->stop();// 断开时，停止计数请求
		return;
	}
	if (!m_b_can_statis) return;
	on_read_data(PLCDATA::C_STATIS);
	m_b_can_statis = false;
}

void lpqtconnPLC::on_ask_status()
{// 状态请求
	if (m_sock_ptr->state() != QAbstractSocket::SocketState::ConnectedState) {
		m_tm_status_->stop();// 断开时，停止状态请求
		return;
	}
	if (!m_b_can_status) return;
	on_read_data(PLCDATA::C_STATUS);
	m_b_can_status = false;
}

void lpqtconnPLC::on_guard_plc()
{// 说明: 注意思考为何不直接用 m_bCanSend 做判断，而是需要新增一个 m_b_guard_ 判断
	if (m_sock_ptr->state() != QAbstractSocket::SocketState::ConnectedState) {
		m_tm_guard_->stop();// 断开时，停止守护
		return;
	}
	if (!m_b_guard_) {// 检查标记 false-出现异常  true-安全
		m_bCanSend = true;
		if (!m_cur_send.second.isEmpty()) 
			send_binary_data(m_cur_send.second, m_cur_send.first);
	}

	m_b_guard_ = false;//进行新一轮的标记
}

void lpqtconnPLC::thrdStart()
{
	qDebug() << __FUNCTION__;
	if (this_thrd_ptr_) {
		this_thrd_ptr_->start();
		this_thrd_ptr_->setPriority(QThread::TimeCriticalPriority);
	}
}

void lpqtconnPLC::thrdStop()
{
	qDebug() << __FUNCTION__;
	if (this_thrd_ptr_) {
		this_thrd_ptr_->quit();
		this_thrd_ptr_->deleteLater();
		this_thrd_ptr_ = nullptr;
	}
}

void lpqtconnPLC::on_close()
{
	qDebug() << __FUNCTION__;
	if (m_sock_ptr) {
		m_sock_ptr->abort();
		m_sock_ptr->close();
		delete m_sock_ptr;
		m_sock_ptr = nullptr;
	}
	if (m_tm_auto_connect)
		m_tm_auto_connect->stop();
	if (m_tm_heart_beat_)
		m_tm_heart_beat_->stop();
	if (m_tm_guard_)
		m_tm_guard_->stop();
	if (m_tm_statis_)
		m_tm_statis_->stop();
	if (m_tm_status_)
		m_tm_status_->stop();

	m_mpReadAddr.clear();
	m_mpSendAddr.clear();
}

//////////////////////////////////////////////////////////////////////////
// 辅助函数接口
QString lpqtconnPLC::fun_getCurTime()
{//年/月/日/时/分/秒/毫秒(7字)
	QDateTime dt = QDateTime::currentDateTime();
	QString s_dt = int_to_hex_str(dt.date().year())
		+ int_to_hex_str(dt.date().month())
		+ int_to_hex_str(dt.date().day())
		+ int_to_hex_str(dt.time().hour())
		+ int_to_hex_str(dt.time().minute())
		+ int_to_hex_str(dt.time().second())
		+ int_to_hex_str(dt.time().msec());
	return s_dt;
}

QString lpqtconnPLC::fun_ints2HexStr(const QList<int>& vals, int len /*= 4*/)
{
	QString rst;
	for (int val : vals) 
		rst += int_to_hex_str(val, len);
	return rst;
}

QString lpqtconnPLC::fun_str2HexStr(const QString& src, int num)
{// num=1标识1个字符，比如'A',因此转换后为"41"占2个字节
	QString strhex = src.toLatin1().toHex().toUpper();
	while (strhex.length() < (num * 2)) {
		strhex += "00";
	}
	strhex = strhex.left(num * 2);
	return strhex;
}

