/*
file:GetParams2ExcelTool.h
date:2025/3/3
brief:自动获取所有配方中的参数值并输出到表格 的小工具
author:wuchaoxi
copyright:杭州利珀科技有限公司
*/
#pragma once

#include <QtWidgets/QWidget>
#include "ui_GetParams2ExcelTool.h"
#include "workThreadCtrl.h"

class GetParams2ExcelTool : public QWidget
{
	Q_OBJECT

public:
	GetParams2ExcelTool(QWidget *parent = Q_NULLPTR);
signals:
	void sgExportFinished(bool success);
private slots:
	void onSaveData2Csv();
	void onExportFinished(bool success);
private:
	Ui::GetParams2ExcelToolClass ui;
	workThreadCtrl *m_work_thread_ptr{ nullptr };
	QMap<QString, QList<ParamInfo>> m_allParamsInfoMap;
};
