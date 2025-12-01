#pragma once
#include <QPushButton>
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTreeView>
#include <QMessageBox>
#include <QLabel>
#include <QLineEdit>

#include "include/lpgobalFunction.h"
#define APP_VERSION "lpFuncConfigTool V1.0.1.0 "

#include "lpqtDb/include/lpqtdb_global.h"
#if _DEBUG 
#pragma comment (lib, "lpqtDb/lib/lpqtDbd.lib")
#else
#pragma comment (lib, "lpqtDb/lib/lpqtDb.lib")
#endif

enum ConfigWidgetType
{
	ConfigWidgt_DB=0,//数据库界面
	ConfigWidgt_PLC  //PLC
};
