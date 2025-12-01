/*
file:PLCConfigWidget.h
date:2025/11/7
brief:PLC界面
author:wuchaoxi
copyright:杭州利珀科技有限公司
*/
#pragma once

#include <QWidget>
#include "ui_UiPlcConfig.h"
#include "lpFuncConfigDefine.h"
struct CellDelta
{
	QString key;      // 协议项名
	int     col;      // 0=name 1=addr 2=cnt 3=type 4=tip
	QString newTxt;   // 用户输入的新值
};
class PLCConfigWidget : public QWidget
{
	Q_OBJECT

public:
	PLCConfigWidget(QWidget *parent = Q_NULLPTR);
	~PLCConfigWidget();

	void initUI(QWidget *widget);
	bool hasConfigChanged() const;
signals:
	void sgSendShowTips(QString showTips);
public slots:
	bool onSaveConfig();
protected:
	bool eventFilter(QObject *obj, QEvent *event)override;
private slots:
	void initConnect();
	void onTestLink();
	void onDiyItemDoubleClicked(QTableWidgetItem *item);
	void onUpdataData(const QString &fieldPath, const QVariantMap &updatedData);
	void onAddDataToReadTable(const QVariantMap &newData);
	void onSendCellChanged(int row, int col);
private:
	void init();
	void initDataShow();
	void initProtocolShow();
	void handleContextMenu(QTableWidget *table, const QPoint &pos);
	void setupSendTableRow(int row);
	QVariantMap getSendTableData()const;
	QVariantMap getReadTableData()const;
	int findReadRowByName(const QString &name) const;
	void recordOriginalConfig();//记录保存前原始的协议数据
	void validateSendTableCell(int row, int column);//send表合法性检查
private:
	Ui_PLC *pUi{ nullptr };
	QString m_ip;
	int m_port{ 1025 };
	int m_heart_beat_warn{ 0 };
	bool b_print{ false };

	QString m_origin_ip;
	int m_origin_port{ 1025 };
	int m_origin_heart_beat_warn{ 0 };
	bool b_origin_print{ false };

	bool m_isConfigChanged{ false }; // 配置是否被修改的标志
	QVariantMap m_protocolMp;
	QVariantMap m_originMp;
	QMenu *m_contextMenu;
	int m_currentRow; // 当前右键点击的行
	QVector<CellDelta> m_delta;   // 增量队列
};
