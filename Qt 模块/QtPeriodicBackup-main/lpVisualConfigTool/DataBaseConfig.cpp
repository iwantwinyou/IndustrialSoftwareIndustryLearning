#include "DataBaseConfig.h"
#include <QSqlError>
#pragma execution_character_set("utf-8")
DataBaseConfig::DataBaseConfig(QWidget *parent /*= nullptr*/)
	:QWidget(parent)
{
	init();
}

DataBaseConfig::~DataBaseConfig()
{

}

void DataBaseConfig::initUI(QWidget *widget)
{
	pUi = new Ui_Database;
	pUi->setupUi(widget);
	initDataShow();
	initConnect();
}

bool DataBaseConfig::onSaveConfig()
{
	// 检查配置是否被修改
	if (!hasConfigChanged()) {
		return false; 
	}
	m_dbHostName = pUi->lineEdit_hostName->text();
	m_dbName = pUi->lineEdit_dbName->text();
	int currentIndex = pUi->comboBox_strategy->currentIndex();
	m_createStrategy = pUi->comboBox_strategy->itemData(currentIndex).toInt();
	// 获取阈值（只在显示时获取，避免隐藏时的无效值）
	if (m_createStrategy == 2) {
		m_flaws_threshold_w = pUi->spinBox_flaws->value();
	}
	// 读取原始JSON文件
	auto &data = gobalFun::f_readFile("./lpIPUConfig/DbConfig.json");
	if (data.isNull()) {
		qWarning() << "Failed to read DbConfig.josn!" << __FUNCTION__;
		return false;
	}

	QJsonDocument doc = QJsonDocument::fromJson(data);
	QJsonObject rootObj = doc.object();
	QJsonObject dataBaseObj = rootObj.value("dataBase").toObject();
	// 更新数据
	dataBaseObj["DbHostName"] = m_dbHostName;
	dataBaseObj["databaseName"] = m_dbName;
	dataBaseObj["createStrategy"] = m_createStrategy;
	dataBaseObj["productionThreshold_w"] = m_flaws_threshold_w;

	rootObj["dataBase"] = dataBaseObj;
	// 写回文件
	bool saveSuccess=gobalFun::f_saveJson(rootObj, QString("./lpIPUConfig/DbConfig.json"));
	if (saveSuccess) {
		recordOriginalConfig();// 保存成功后更新原始配置记录
	}
	else {
		qWarning() << "Failed to save config file" << __FUNCTION__;
	}

	return saveSuccess;
}

void DataBaseConfig::updateFlawsVisibility(int strategy)
{
	if (strategy == 2) {
		pUi->spinBox_flaws->show();
		pUi->lb_flaws_db->show();
	}
	else {
		pUi->spinBox_flaws->hide();
		pUi->lb_flaws_db->hide();
	}
}

void DataBaseConfig::recordOriginalConfig()
{
	m_originalDbHostName = m_dbHostName;
	m_originalDbName = m_dbName;
	m_originalCreateStrategy = m_createStrategy;
	m_originalFlawsThreshold = m_flaws_threshold_w;
	m_isConfigChanged = false;
}

void DataBaseConfig::setupChangeConnections()
{
	connect(pUi->lineEdit_hostName, &QLineEdit::textChanged, this, &DataBaseConfig::onConfigChanged);
	connect(pUi->lineEdit_dbName, &QLineEdit::textChanged, this, &DataBaseConfig::onConfigChanged);
	connect(pUi->comboBox_strategy, QOverload<int>::of(&QComboBox::currentIndexChanged),
		this, &DataBaseConfig::onConfigChanged);
	connect(pUi->spinBox_flaws, QOverload<int>::of(&QSpinBox::valueChanged),
		this, &DataBaseConfig::onConfigChanged);
}

bool DataBaseConfig::hasConfigChanged() const
{
	return m_isConfigChanged;
}

void DataBaseConfig::onStrategyChanged(int index)
{
	int strategy = pUi->comboBox_strategy->itemData(index).toInt();
	updateFlawsVisibility(strategy);
}

void DataBaseConfig::initConnect()
{
	connect(pUi->comboBox_strategy, QOverload<int>::of(&QComboBox::currentIndexChanged),
		this, &DataBaseConfig::onStrategyChanged);
	connect(pUi->btn_testLink, &QPushButton::clicked, this, &DataBaseConfig::onTestLink);
	connect(pUi->btn_dbInit, &QPushButton::clicked, this, &DataBaseConfig::onInitDataBase);
}

void DataBaseConfig::onTestLink()
{
	m_dbHostName = pUi->lineEdit_hostName->text();
	m_dbName = pUi->lineEdit_dbName->text();
	QSqlDatabase db;
	db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName(m_dbHostName);
	db.setDatabaseName(m_dbName);
	db.setUserName("root");
	db.setPassword("root");
	db.setPort(3306);
	if (db.open()) {
		QString sucessStr= tr("数据库连接成功");
		QMessageBox::information(nullptr, tr("弹窗提示："), sucessStr);
		emit sgSendShowTips(sucessStr);
		db.close();
	}
	else {
		QString lastErrorStr = db.lastError().text();
		QMessageBox::warning(nullptr, tr("弹窗提示："), lastErrorStr);
		emit sgSendShowTips(lastErrorStr);
		qWarning() << "数据库连接失败：" << lastErrorStr << __FUNCTION__;
	}
}

void DataBaseConfig::onInitDataBase()
{
	//如果存在就初始化数据库表,如果不存在就创建数据库，并初始化数据库表
	m_dbHostName = pUi->lineEdit_hostName->text();
	m_dbName = pUi->lineEdit_dbName->text();
	TDbCfg cfg;
	cfg.dbHostName = m_dbHostName;
	cfg.dbDBName = m_dbName;
	bool connect_status = m_database->initDb(&cfg);
	if (connect_status) {
		//QMessageBox::information(this, tr("弹窗提示："), "db link success!");
		qDebug() << "db link success!" << __FUNCTION__;
	}
	else {
		//QMessageBox::warning(this, tr("弹窗提示："), "db link faild!");
		qWarning() << "db link faild!" << __FUNCTION__;
	}
	QString db_main_sql_path = "./ui/sheetschema_main.sql";
	bool loadSqlFile = m_database->runSql(db_main_sql_path);
	if (loadSqlFile) {
		emit sgSendShowTips("main db init success");
		QMessageBox::information(nullptr, tr("弹窗提示："), "main db init success!");
	}
	else{
		QMessageBox::warning(nullptr, tr("弹窗提示："), "main db init failed!");
		emit sgSendShowTips("main db init failed!");
		qWarning() << "main db init failed!" << __FUNCTION__;
	}
}

void DataBaseConfig::onConfigChanged()
{
	QString currentHostName = pUi->lineEdit_hostName->text();
	QString currentDbName = pUi->lineEdit_dbName->text();

	int currentIndex = pUi->comboBox_strategy->currentIndex();
	int currentStrategy = pUi->comboBox_strategy->itemData(currentIndex).toInt();
	int currentThreshold = m_originalFlawsThreshold; // 默认使用原始值
	if (currentIndex == 2) {
		currentThreshold = pUi->spinBox_flaws->value();
	}

	bool changed = (currentHostName != m_originalDbHostName) ||
		(currentDbName != m_originalDbName) ||
		(currentStrategy != m_originalCreateStrategy) ||
		(currentThreshold != m_originalFlawsThreshold);

	m_isConfigChanged = changed;
}

void DataBaseConfig::init()
{
	auto &data = gobalFun::f_readFile("./lpIPUConfig/DbConfig.json");
	if (!data.isNull()) {
		QJsonObject obj = QJsonDocument::fromJson(data).object();
		QJsonObject dataBaseObj = obj.value("dataBase").toObject();
		m_dbHostName = dataBaseObj.value("DbHostName").toString();
		m_dbName= dataBaseObj.value("databaseName").toString();
		m_createStrategy = dataBaseObj.value("createStrategy").toInt();
		m_flaws_threshold_w = dataBaseObj.value("productionThreshold_w").toInt();
	}
	m_database = lpCreateMyDb();
}

void DataBaseConfig::initDataShow()
{
	pUi->comboBox_strategy->clear();
	pUi->comboBox_strategy->addItem(tr("按小时"), 0);
	pUi->comboBox_strategy->addItem(tr("按月"), 1);
	pUi->comboBox_strategy->addItem(tr("按产量"), 2);
	pUi->comboBox_strategy->addItem(tr("按天"), 3);

	pUi->lineEdit_hostName->setText(m_dbHostName);
	pUi->lineEdit_dbName->setText(m_dbName);
	pUi->spinBox_flaws->setValue(m_flaws_threshold_w);
	// 根据数据值查找并设置当前项
	int index = pUi->comboBox_strategy->findData(m_createStrategy);
	if (index != -1) {
		pUi->comboBox_strategy->setCurrentIndex(index);
	}
	pUi->spinBox_flaws->setValue(m_flaws_threshold_w);
	updateFlawsVisibility(m_createStrategy);
	// 记录原始配置并建立修改监听
	recordOriginalConfig();
	setupChangeConnections();
}
