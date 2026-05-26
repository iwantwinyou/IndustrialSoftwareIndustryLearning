#include "lpqtconnnOtherApp.h"
#include "lpqtConfig/include/lpServerSheetCfg.h"

lpqtconnnOtherApp::lpqtconnnOtherApp(QObject *parent/*=nullptr*/)
{
	loadConfig();
	initServer();
}

lpqtconnnOtherApp::~lpqtconnnOtherApp()
{
	if (m_tcpSocket) {
		m_tcpSocket->abort();
		m_tcpSocket->close();
		delete m_tcpSocket;
		m_tcpSocket = nullptr;
	}
	if (m_tcpServer) {
		m_tcpServer->close();
		delete m_tcpServer;
		m_tcpServer = nullptr;
	}
}

void lpqtconnnOtherApp::loadConfig()
{
	QVariantMap extend_var = lpServerSheetCfg::instance()->getCfg()->t_srv_cfg_.extend_funtion_.toMap();
	QVariantMap change_model_vmp = extend_var.value("auto_change_model").toMap();
	m_host_ip = change_model_vmp.value("tcp_server_ip").toString();
	m_port = change_model_vmp.value("tcp_server_port").toInt();
	m_bPrint = change_model_vmp.value("b_print").toBool();
}

void lpqtconnnOtherApp::onNewConnection()
{
	qDebug() << __FUNCTION__;
	m_tcpSocket = m_tcpServer->nextPendingConnection();//获取与客户端通信的socket
	connect(m_tcpSocket, &QTcpSocket::readyRead, this, &lpqtconnnOtherApp::on_data_received);
}

void lpqtconnnOtherApp::on_data_received()
{
	m_recv_package.clear();
	QString data_recv = m_tcpSocket->readAll();
	if (m_bPrint)
		qDebug() << __FUNCTION__ << data_recv;
	m_recv_package.append(data_recv);
	parseReceivedData();
}

void lpqtconnnOtherApp::on_socketError(QAbstractSocket::SocketError err)
{
	qDebug() << "error " << m_tcpServer->errorString();
}

void lpqtconnnOtherApp::on_send_data(bool isSucess)
{
	QByteArray feedbackMessage;
	QString message;
	if (isSucess){
		message = OTHERAPP::dataLen + INT + "0";
		feedbackMessage = message.toUtf8();
	}
	else{
		message = OTHERAPP::dataLen + INT + "1";
		feedbackMessage = message.toUtf8();
	}
	//发送
	if (m_tcpSocket->state() != QAbstractSocket::ConnectedState)
		return;
	m_tcpSocket->write(feedbackMessage);
	m_tcpSocket->flush();
	if (m_bPrint)
		qDebug() << "send. feedbackMessage=" << feedbackMessage << __FUNCTION__;
}

void lpqtconnnOtherApp::on_close()
{
	qDebug() << __FUNCTION__;
	if (m_tcpSocket){
		m_tcpSocket->abort();
		m_tcpSocket->close();
		delete m_tcpSocket;
		m_tcpSocket = nullptr;

	}
}

void lpqtconnnOtherApp::initServer()
{
	m_tcpSocket = new QTcpSocket(this);
	m_tcpServer = new QTcpServer(this);
	if (m_tcpServer->isListening()) {
		closeServer();
	}
	connect(m_tcpServer, &QTcpServer::newConnection, this, &lpqtconnnOtherApp::onNewConnection);
	connect(m_tcpServer, &QTcpServer::acceptError, this, &lpqtconnnOtherApp::on_socketError);
	if (!m_tcpServer->listen(QHostAddress::Any, m_port)) {//开始监听
		qWarning() << __FUNCTION__ << "tcp server bind fail!";
	}	
}

void lpqtconnnOtherApp::closeServer()
{	//停止服务
	m_tcpServer->close();
	//断开与客户端的连接
	m_tcpSocket->disconnectFromHost();
	if (m_tcpSocket->state() != QAbstractSocket::UnconnectedState) {
		m_tcpSocket->abort();
	}
}

bool lpqtconnnOtherApp::parseReceivedData()
{
	bool parseSuccess = true;//标志位，看解析是否成功
	while (m_recv_package.size() >= 12)
	{ // 消息长度(6) + 消息类型(6)
		QString messageLengthStr = m_recv_package.left(6);
		QString messageTypeStr = m_recv_package.mid(6, 6);

		// 将消息长度字符串转换为整数
		bool ok;
		int messageLength = messageLengthStr.toInt(&ok, 16);
		if (!ok) {
			qWarning() << "Invalid message length!";
			parseSuccess = false;
		}
		// 提取 Recipeld，长度为32个字符,（料号跟型号不完全一致）
		QString modelName = m_recv_package.mid(12, 32).trimmed();
		// 提取 JobName，长度为32个字符
		QString jobName = m_recv_package.mid(12 + 32, 32).trimmed();
		if (modelName.isEmpty() || jobName.isEmpty()){
			on_send_data(false); // 如果解析失败
		}
		qDebug() << "ModelName: " << modelName << "JobName: " << jobName;
		emit sgChangeJobName(modelName, jobName);
		//移除已解析的数据
		m_recv_package = m_recv_package.mid(12 + messageLength);
		if (m_recv_package.size() < 12){
			parseSuccess = true;
		}
	}
	return parseSuccess;
}

