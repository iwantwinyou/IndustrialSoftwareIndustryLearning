#pragma once

#include <QDialog>
#include <QComboBox>
#include <QMenu>
#include "ui_UiDiySet.h"

enum DialogType
{
	Diy_dialog = 0,//Diy弹窗
	Reg_dialog	  //reg弹窗
};

class UiDiySet : public QDialog
{
	Q_OBJECT

public:
	UiDiySet(QWidget *parent = Q_NULLPTR);
	~UiDiySet();

public:
	void setDialogType(DialogType type);
	void initTableData(DialogType type,QVariantMap vm,const QString &addr, const int cnt, const QString &fieldPath);
signals:
	void sgDiyDataUpdated(const QString &parentKey, const QVariantMap &vm);
	void sgSendShowTips(QString showTips);
private slots:
	void initConnect();
	void onCustomContextMenuRequested(const QPoint &pos);
	void onAddRow();
	void onDeleteRow();
	void onConfirmButtonClicked();
private:
	void setTypeComboBox(QComboBox *comboBox);
	void setupContextMenu();
	QTableWidget* getCurrentTable() const;
	void setupNewDiyRow(int row);
	void setupNewRegRow(int row);
	QVariantMap getDiyData()const;
	QVariantMap getRegData() const;
	void validateReadTableCell(int row, int column);//read_表输入合法性检查
	void validRegTableCell(int row, int column);//新建read_信息子界面reg弹窗，合法性检查
	void validDiyTableCell(int row, int column);//同上，diy弹窗
private:
	Ui::UiDiySet ui;
	QMenu *m_contextMenu;
	int m_currentRow{ -1 }; // 当前右键点击的行
	QVariantMap m_originalData;
	QString m_readParentKey; //read_请求名称的父节点
};
