#pragma once

#include <QDialog>
#include <QComboBox>
#include <QMenu>
#include <QVariantMap>
#include "ui_UiReadTableSet.h"

class UiReadTableSet : public QDialog
{
	Q_OBJECT

public:
	UiReadTableSet(QWidget *parent = Q_NULLPTR);
	~UiReadTableSet();
signals:
	void sgAddDataToReadTable(const QVariantMap &vm);
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
	QVariantMap getReadDiyData() const;
	void validateReadTableCell(int row, int column);//read_表输入合法性检查
private:
	Ui::UiReadTableSet ui;
	QMenu *m_contextMenu;
	int m_currentRow{ -1 };
};
