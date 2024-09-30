#include "lpqtconnOtherApp.h"

lpqtconnOtherApp::lpqtconnOtherApp(const QString& cfg_file /*= nullptr*/, QObject *parent /*= nullptr*/)
{
	qDebug() << CONNOTHERAPP_VER << __FUNCTION__;
	pf_init(cfg_file);

}

lpqtconnOtherApp::~lpqtconnOtherApp()
{
	qDebug() << __FUNCTION__;
	thrdStop();
}
QSharedPointer<lpconnOtherAppBase>lpCreateConnOtherApp(const QString& cfg_file)
{
	return QSharedPointer<lpconnOtherAppBase>(new lpqtconnOtherApp(cfg_file));
}

void lpqtconnOtherApp::on_connected()
{//连接成功
	qDebug() << "connect to OtherApp successful." << m_host_ip << m_port << __FUNCTION__;
	//操作处理
	m_tm_auto_connect->stop();
	sgConnectStatus(true);
}

void lpqtconnOtherApp::on_auto_connect()
{
	if (m_socket_ptr->state() == QAbstractSocket::SocketState::ConnectingState)
		return;
	if (m_socket_ptr->state() == QAbstractSocket::SocketState::ConnectedState)
		return;

	m_socket_ptr->abort();
	m_socket_ptr->close();
	m_socket_ptr->connectToHost(m_host_ip, m_port);
	qDebug() << "OtherApp reconnecting..." << m_host_ip << m_port << __FUNCTION__;
}

void lpqtconnOtherApp::on_data_received()
{
	m_recv_package.clear();
	QString data_recv = m_socket_ptr->readAll();
	if(m_bPrint)
		qDebug() << __FUNCTION__ << data_recv;
	m_recv_package.append(data_recv);
	if (parseReceivedData())
	{
		send_data(true);
	}
	else
	{
		send_data(false);
	}
}

void lpqtconnOtherApp::on_connStatus()
{
	bool b_conn = false;
	if (m_socket_ptr)
	{
		b_conn = (m_socket_ptr->state() == QAbstractSocket::SocketState::ConnectedState);
	}
	emit sgConnectStatus(b_conn);
}

void lpqtconnOtherApp::on_socketError(QAbstractSocket::SocketError err)
{
	if (!m_socket_ptr)
		return;
	qWarning() << QString("Socket error(%1):%2").arg(err).arg(m_socket_ptr->errorString()) << __FUNCTION__;
	m_socket_ptr->abort();
	m_socket_ptr->close();
	if (!m_tm_auto_connect->isActive()) //未启动时启动自动连接
		m_tm_auto_connect->start(3000);
}

void lpqtconnOtherApp::pf_init(const QString& cfg_file /*= nullptr*/)
{
	pf_readConfig(cfg_file);
	//socket 初始化
	m_socket_ptr = new QTcpSocket(this);
	m_socket_ptr->setSocketOption(QAbstractSocket::SendBufferSizeSocketOption, 1024);
	m_socket_ptr->setSocketOption(QAbstractSocket::KeepAliveOption, true);
	connect(m_socket_ptr, &QTcpSocket::connected, this, &lpqtconnOtherApp::on_connected);
	connect(m_socket_ptr, &QTcpSocket::readyRead, this, &lpqtconnOtherApp::on_data_received);
	connect(m_socket_ptr, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(on_socketError(QAbstractSocket::SocketError)));
	// 断线重连时钟
	m_tm_auto_connect = new QTimer(this);
	connect(m_tm_auto_connect, &QTimer::timeout, this, &lpqtconnOtherApp::on_auto_connect);

	//内部消息传递，主要用于进入线程
	connect(this, &lpqtconnOtherApp::sgAskConnStatus, this, &lpqtconnOtherApp::on_connStatus);

	//连接第三方App
	pf_connectOtherApp(m_host_ip, m_port);
	this_thrd_ptr_ = new QThread(this);
	this->moveToThread(this_thrd_ptr_);
	thrdStart();
}

void lpqtconnOtherApp::pf_readConfig(const QString& cfg_file /*= nullptr*/)
{
	QString cfg_path = OTHERAPP::CFG_PATH;
	if (!cfg_file.isEmpty())
		cfg_path = cfg_file;
	QFile file(cfg_path);
	if (!file.exists())
	{
		qWarning() << "File does not exist!" << cfg_path;
		return;
	}
	if (!file.open(QFile::ReadOnly | QIODevice::Text)) 
	{
		qWarning() << "read failed!" << cfg_path << __FUNCTION__;
		return;
	}
	QJsonObject obj = QJsonDocument::fromJson(file.readAll()).object();
	file.close();
	//配置
	QJsonObject j1 = obj.value("config").toObject();
	m_host_ip = j1.value("tcp_server_ip").toString();
	m_port = j1.value("tcp_server_port").toInt(6000);
	m_bPrint = j1.value("b_print").toBool();
}

void lpqtconnOtherApp::pf_connectOtherApp(const QString& ip, quint16 port)
{
	qDebug() << ip << port << __FUNCTION__;
	//连接状态下，先断开原连接
	if (m_socket_ptr->state() == QAbstractSocket::SocketState::ConnectedState)
	{
		m_socket_ptr->abort();
		m_socket_ptr->close();
	}
	if (m_tm_auto_connect->isActive())
		m_tm_auto_connect->stop();
	if (ip.isEmpty())
	{
		qWarning() << "tcp_server_ip is empty!" << __FUNCTION__;
	}
	//进行连接
	m_socket_ptr->connectToHost(ip, port);
	if (!m_socket_ptr->waitForConnected(100)) //连接失败，触发重连机制
	{
		qWarning() << "connect to OtherApp failed!" << ip << port << __FUNCTION__;
		m_tm_auto_connect->start(3000);
		return;
	}
}

bool lpqtconnOtherApp::parseReceivedData()
{
	bool parseSuccess = true;//标志位，看解析是否成功
	while (m_recv_package.size() >= 12) 
	{ // 消息长度(6) + 消息类型(6)
		QString messageLengthStr = m_recv_package.left(6);
		QString messageTypeStr = m_recv_package.mid(6, 6);

		// 将消息长度字符串转换为整数
		bool ok;
		int messageLength = messageLengthStr.toInt(&ok, 16);
		if (!ok) 
		{
			qWarning() << "Invalid message length!";
			return false;
		}
		// 检查接收包长度是否足够
		int test = m_recv_package.size();
		if (m_recv_package.size() < 12 + messageLength) 
		{
			return true; // 数据不完整，等待更多数据
		}
		// 提取 Recipeld，长度为32个字符,（我们的模板和检测参数一致）
		QString modelName = m_recv_package.mid(12, 32).trimmed();
		// 提取 JobName，长度为32个字符
		QString jobName = m_recv_package.mid(12 + 32, 32).trimmed();
		qDebug() << "ModelName: " << modelName << "JobName: " << jobName;
		emit sgChangeJobName(modelName,jobName);
		 //移除已解析的数据
		m_recv_package = m_recv_package.mid(12 + messageLength);
		//m_recv_package.remove(0, 12 + messageLength);
		if (m_recv_package.size() < 12) 
		{
			return true; // 等待更多数据
		}
	}
	return parseSuccess;
}

void lpqtconnOtherApp::send_data(bool isSucess)
{
	QByteArray feedbackMessage;
	QString message;
	if (isSucess)
	{
		message = OTHERAPP::dataLen + INT + "0";
		feedbackMessage = message.toUtf8();
	}
	else
	{
		message = OTHERAPP::dataLen + INT + "1";
		feedbackMessage = message.toUtf8();
	}
	//发送
	if (m_socket_ptr->state() != QAbstractSocket::ConnectedState)
		return;
	m_socket_ptr->write(feedbackMessage);
	m_socket_ptr->flush();
	if (m_bPrint)
		qDebug() << "send. feedbackMessage=" << feedbackMessage << __FUNCTION__;

}

void lpqtconnOtherApp::thrdStart()
{
	qDebug() << __FUNCTION__;
	if (this_thrd_ptr_)
	{
		this_thrd_ptr_->start();
		this_thrd_ptr_->setPriority(QThread::TimeCriticalPriority);
	}
}

void lpqtconnOtherApp::thrdStop()
{
	qDebug() << __FUNCTION__;
	if (this_thrd_ptr_)
	{
		this_thrd_ptr_->quit();
		this_thrd_ptr_->deleteLater();
		this_thrd_ptr_ = nullptr;
	}
}