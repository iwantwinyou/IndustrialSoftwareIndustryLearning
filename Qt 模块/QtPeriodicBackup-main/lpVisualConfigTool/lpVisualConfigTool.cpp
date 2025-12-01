#include "lpVisualConfigTool.h"
#include "include/lpgobalFunction.h"
#include <QMouseEvent>

#pragma execution_character_set("utf-8")
QSharedPointer<lpVisualConfigToolMgr>lpCreateVisualConfigTool(QWidget *parent /* = nullptr */)
{
	return QSharedPointer<lpVisualConfigToolMgr>(new lpVisualConfigTool(parent));
}

lpVisualConfigTool::lpVisualConfigTool(QWidget*parent/*=nullptr*/)
	:lpVisualConfigToolMgr(parent)
{
	qDebug() << "LP_VERSION_EXE " APP_VERSION;
	initUI();
	initConnect();
}

lpVisualConfigTool::~lpVisualConfigTool()
{
	delete m_dataBaseConfig;
	m_dataBaseConfig = nullptr;
	delete m_plcConfig;
	m_plcConfig = nullptr;
	delete ui;
	ui = nullptr;
}

void lpVisualConfigTool::onUpdateTipsShow(QString showTips)
{
	ui->lb_tips->clear();
	ui->lb_tips->setText("Note:" + showTips);
}

void lpVisualConfigTool::onApply()
{
	int currentIndex = ui->tabWidget_config->currentIndex();
	if (currentIndex == ConfigWidgetType::ConfigWidgt_DB) {
		if (!m_dataBaseConfig->hasConfigChanged()) {
			QMessageBox::information(nullptr, tr("弹窗提示:"), tr("配置未修改，无需保存!"));
			return;
		}
		if (m_dataBaseConfig->onSaveConfig()) {
			QMessageBox::information(nullptr, tr("弹窗提示:"), tr("保存成功!"));
		}
		else {
			QMessageBox::warning(nullptr, tr("弹窗提示:"), tr("保存失败!请检查配置!"));
		}
	}
	else if (currentIndex == ConfigWidgetType::ConfigWidgt_PLC) {
		if (!m_plcConfig->hasConfigChanged()) {
			QMessageBox::information(nullptr, tr("弹窗提示:"), tr("配置未修改，无需保存!"));
			return;
		}
		if (m_plcConfig->onSaveConfig()) {
			QMessageBox::information(nullptr, tr("弹窗提示:"), tr("保存成功!"));
		}
		else {
			QMessageBox::warning(nullptr, tr("弹窗提示:"), tr("保存失败!请检查配置!"));
		}
	}
}

void lpVisualConfigTool::initUI()
{
	ui = new Ui_VisualFuncConfigWidget;
	ui->setupUi(this);
	this->setWindowTitle(APP_VERSION);
	loadUi();
}

void lpVisualConfigTool::initConnect()
{
	connect(m_dataBaseConfig, &DataBaseConfig::sgSendShowTips, this, &lpVisualConfigTool::onUpdateTipsShow);
	connect(m_plcConfig, &PLCConfigWidget::sgSendShowTips, this, &lpVisualConfigTool::onUpdateTipsShow);
	connect(ui->btn_apply, &QPushButton::clicked, this, &lpVisualConfigTool::onApply);
	connect(ui->tabWidget_config->tabBar(), &QTabBar::tabBarClicked, this, [this](int index) {
		if (index != ui->tabWidget_config->currentIndex()) {// 在切换前检查当前tab是否有修改
			if (!checkCurrentTabModified()) {
				return;// 阻止切换：不执行任何操作，让tab保持原样
			}
		}
		});
}

void lpVisualConfigTool::loadUi()
{
	loadDataBaseUi();
	loadPLCUi();
}

void lpVisualConfigTool::loadDataBaseUi()
{
	m_dataBaseConfig = new DataBaseConfig();
	m_dataBaseConfig->initUI(ui->tab_db);
}

void lpVisualConfigTool::loadPLCUi()
{
	m_plcConfig = new PLCConfigWidget();
	m_plcConfig->initUI(ui->tab_plc);
}

bool lpVisualConfigTool::checkCurrentTabModified()
{
	int currentIndex = ui->tabWidget_config->currentIndex();
	bool hasModified = false;
	QString configName;
	if (currentIndex == ConfigWidgetType::ConfigWidgt_DB) {
		hasModified = m_dataBaseConfig->hasConfigChanged();
		configName = tr("数据库配置");
	}
	else if (currentIndex == ConfigWidgetType::ConfigWidgt_PLC) {
		hasModified = m_plcConfig->hasConfigChanged();
		configName = tr("PLC配置");
	}

	if (hasModified) {
		QMessageBox::StandardButton reply = QMessageBox::question(
			nullptr,
			tr("未保存的修改"),
			tr("%1有未保存的修改，是否要保存？").arg(configName),
			QMessageBox::Save | QMessageBox::Cancel,
			QMessageBox::Save
		);

		switch (reply) {
		case QMessageBox::Save: {
			if (currentIndex == ConfigWidgetType::ConfigWidgt_DB) {
				return m_dataBaseConfig->onSaveConfig();
			}
			else if (currentIndex == ConfigWidgetType::ConfigWidgt_PLC) {
				return m_plcConfig->onSaveConfig();
			}
			break;
		}
		case QMessageBox::Cancel:
		default:
			return false;
			break;

		}
	}
	return true;
}
