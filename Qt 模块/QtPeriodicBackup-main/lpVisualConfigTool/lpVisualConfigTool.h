/*
file:lpVisualFuncConfigTool.h
date:2025/10/21
brief:参数可视化主界面  json文件的增删改  在ui界面进行操作
author:wuchaoxi
copyright:杭州利珀科技有限公司
*/
#pragma once

#include "lpvisualconfigtool_global.h"
#include "ui_lpVisualFuncConfigTool.h"
#include "lpFuncConfigDefine.h"
#include "DataBaseConfig.h"
#include "PLCConfigWidget.h"

class LPVISUALCONFIGTOOL_EXPORT lpVisualConfigTool:public lpVisualConfigToolMgr
{
public:
	lpVisualConfigTool(QWidget*parent=nullptr);
	~lpVisualConfigTool();
private slots:
	void onUpdateTipsShow(QString showTips);
	void onApply();
private:
	void initUI();
	void initConnect();
	void loadUi();// 加载所有UI模块
	void loadDataBaseUi();//加载数据库配置界面
	void loadPLCUi();

	bool checkCurrentTabModified();
private:
	Ui_VisualFuncConfigWidget *ui;
	DataBaseConfig *m_dataBaseConfig;
	PLCConfigWidget *m_plcConfig;
	int m_currentTabIndex{ 0 };
};
