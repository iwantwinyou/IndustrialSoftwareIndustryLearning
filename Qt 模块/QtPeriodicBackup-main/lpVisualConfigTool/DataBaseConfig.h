/*
file:DataBaseConfig.h
date:2025/11/3
brief:数据库界面 
author:wuchaoxi
copyright:杭州利珀科技有限公司
*/
#pragma once
#include <qwidget.h>
#include <QtSql/QSqlDatabase>
#include "lpFuncConfigDefine.h"
#include "ui_UiDatabase.h"
class DataBaseConfig :public QWidget
{
	Q_OBJECT
public:
	DataBaseConfig(QWidget *parent = nullptr);
	~DataBaseConfig();

	void initUI(QWidget *widget);
	bool hasConfigChanged() const;
signals:
	void sgSendShowTips(QString showTips);
public slots:
	bool onSaveConfig();
private slots:
	void onStrategyChanged(int index);
	void initConnect();
	void onTestLink();
	void onInitDataBase();
	void onConfigChanged(); // 配置改变时
private:
	void init();
	void initDataShow();
	void updateFlawsVisibility(int strategy);
	void recordOriginalConfig(); // 记录原始配置
	void setupChangeConnections(); // 建立修改监听连接
private:
	CqtDbBase* m_database{ nullptr };
	Ui_Database *pUi{ nullptr };
	QString  m_dbHostName;
	QString m_dbName;
	int m_createStrategy{ 0 };
	int m_flaws_threshold_w{ 1000 };
	// 记录原始配置值
	QString m_originalDbHostName;
	QString m_originalDbName;
	int m_originalCreateStrategy;
	int m_originalFlawsThreshold;

	bool m_isConfigChanged {false}; // 配置是否被修改的标志
};
