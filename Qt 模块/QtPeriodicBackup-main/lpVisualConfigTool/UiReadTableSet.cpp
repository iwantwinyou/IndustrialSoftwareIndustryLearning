#include "UiReadTableSet.h"
#include <QTableWidget>
#include <QMessageBox>

#pragma execution_character_set("utf-8")
UiReadTableSet::UiReadTableSet(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	setupContextMenu();
	initConnect();
}

UiReadTableSet::~UiReadTableSet()
{
}

void UiReadTableSet::initConnect()
{
	connect(ui.btn_cancel, &QPushButton::clicked, this, &QDialog::reject);
	connect(ui.btn_confirm, &QPushButton::clicked, this, &UiReadTableSet::onConfirmButtonClicked);
	connect(ui.tableWidget, &QTableWidget::customContextMenuRequested,
		this, &UiReadTableSet::onCustomContextMenuRequested);
	connect(ui.tableWidget, &QTableWidget::cellChanged, this, &UiReadTableSet::validateReadTableCell);
}

void UiReadTableSet::onCustomContextMenuRequested(const QPoint &pos)
{
	QTableWidget *table = qobject_cast<QTableWidget*>(sender());
	if (!table) return;

	QTableWidgetItem *item = table->itemAt(pos);
	if (item) {
		m_currentRow = item->row();
	}
	else {
		m_currentRow = -1; // 点击在空白处
	}
	m_contextMenu->exec(table->viewport()->mapToGlobal(pos));
}

void UiReadTableSet::onAddRow()
{
	int newRow = (m_currentRow >= 0) ? m_currentRow + 1 : ui.tableWidget->rowCount();//在选中行的下一行添加
	ui.tableWidget->insertRow(newRow);
	QTableWidgetItem *nameItem = new QTableWidgetItem(tr(""));
	ui.tableWidget->setItem(newRow, 0, nameItem);

	QTableWidgetItem *addrItem = new QTableWidgetItem(tr(""));
	ui.tableWidget->setItem(newRow, 1, addrItem);

	QTableWidgetItem *cntItem = new QTableWidgetItem("");
	ui.tableWidget->setItem(newRow, 2, cntItem);

	QComboBox *typeComboBox = new QComboBox();
	setTypeComboBox(typeComboBox);
	typeComboBox->setCurrentIndex(0);
	ui.tableWidget->setCellWidget(newRow, 3, typeComboBox);

	QTableWidgetItem *tipItem = new QTableWidgetItem("");
	ui.tableWidget->setItem(newRow, 4, tipItem);
}

void UiReadTableSet::onDeleteRow()
{
	if (!ui.tableWidget || m_currentRow < 0 || m_currentRow >= ui.tableWidget->rowCount()) {
		return;
	}
	QMessageBox::StandardButton reply = QMessageBox::question(
		nullptr,
		tr("确认删除"),
		tr("确定要删除这一行吗？"),
		QMessageBox::Yes | QMessageBox::No,
		QMessageBox::No
	);

	if (reply == QMessageBox::Yes) {
		ui.tableWidget->removeRow(m_currentRow);
		m_currentRow = -1; // 重置当前行
	}
}

void UiReadTableSet::onConfirmButtonClicked()
{
	QVariantMap mp = getReadDiyData();

	emit sgAddDataToReadTable(mp);
	accept();
}

void UiReadTableSet::setTypeComboBox(QComboBox *comboBox)
{
	comboBox->clear();
	comboBox->addItem("diy");
	comboBox->addItem("reg");
}

void UiReadTableSet::setupContextMenu()
{
	m_contextMenu = new QMenu();

	QAction *addAction = new QAction(tr("添加行"), nullptr);
	QAction *deleteAction = new QAction(tr("删除行"), nullptr);

	m_contextMenu->addAction(addAction);
	m_contextMenu->addAction(deleteAction);

	connect(addAction, &QAction::triggered, this, &UiReadTableSet::onAddRow);
	connect(deleteAction, &QAction::triggered, this, &UiReadTableSet::onDeleteRow);
	ui.tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
}

QVariantMap UiReadTableSet::getReadDiyData() const
{
	QVariantMap result;
	for (int row = 0; row < ui.tableWidget->rowCount(); ++row) {
		QTableWidgetItem *nameItem = ui.tableWidget->item(row, 0);
		if (!nameItem || nameItem->text().trimmed().isEmpty()) {
			continue;
		}
		QVariantMap itemData;
		QString nameStr = nameItem->text().trimmed();
		itemData["name"] = nameStr;

		QTableWidgetItem *addrItem = ui.tableWidget->item(row, 1);
		if (addrItem && !addrItem->text().trimmed().isEmpty()) {
			itemData["addr"] = addrItem->text().trimmed();
		}

		QTableWidgetItem *cntItem = ui.tableWidget->item(row, 2);
		if (cntItem && !cntItem->text().trimmed().isEmpty()) {
			// 验证cnt是否为数字
			bool ok;
			int cntValue = cntItem->text().toInt(&ok);
			if (ok && cntValue > 0) {
				itemData["cnt"] = cntValue;
			}
			else {
				itemData["cnt"] = cntItem->text().trimmed(); // 保持原始文本，让上层处理
			}
		}

		QComboBox *typeComboBox = qobject_cast<QComboBox*>(ui.tableWidget->cellWidget(row, 3));
		if (typeComboBox) {
			QString typeValue = typeComboBox->currentText();
			itemData["type"] = typeValue;
		}

		//说明列，一些提示信息
		QTableWidgetItem *tipItem = ui.tableWidget->item(row, 4);
		if (tipItem && !tipItem->text().trimmed().isEmpty()) {
			itemData["tip"] = tipItem->text().trimmed();
		}

		QString key = QString("item_%1").arg(row);
		result[key] = itemData;
	}
	
	return result;
}

void UiReadTableSet::validateReadTableCell(int row, int column)
{
	if (row >= ui.tableWidget->rowCount()) return;
	if (column > 2) return;

	QTableWidgetItem *item = ui.tableWidget->item(row, column);
	QTableWidgetItem *tipItem = ui.tableWidget->item(row, 4);
	if (!item || !tipItem) return;

	QString text = item->text().trimmed();
	bool isValid = false;
	QString message;
	QString warningMessage;

	if (column == 0) {
		if (text.startsWith("read_") && text.length() > 6) {
			QString rest = text.mid(5); // 去掉"read_"
			QRegularExpression regExp("^[a-zA-Z0-9_]*$");
			if (regExp.match(rest).hasMatch()) {
				isValid = true;
				message = tr("✓ 名称格式正确");
			}
			else {
				warningMessage = tr("只能包含字母、数字、下划线");
			}
		}
		else {
			warningMessage = tr("必须以'read_'开头且长度大于6");
		}
	}
	else if(column==1){
		if (text.isEmpty()) {
			warningMessage = tr("请输入地址");
		}
		else {
			bool ok;
			int addr = text.toInt(&ok);
			if (ok && addr >= 10000 && addr <= 65534) {
				isValid = true;
				message = tr("✓ 地址格式正确");
			}
			else {
				warningMessage = tr("请输入数字，地址范围：10000-65534");
			}
		}
	}
	else if (column == 2) {
		if (text.isEmpty()) {
			warningMessage = tr("请输入字数");
		}
		else {
			bool ok;
			int cnt = text.toInt(&ok);
			if (ok && cnt >= 1 && cnt <= 999) {
				isValid = true;
				message = tr("✓ 字数格式正确");
			}
			else {
				warningMessage = tr("请输入数字,字数范围：1-999");
			}
		}

	}
	if (!warningMessage.isEmpty()) {
		QMessageBox::warning(nullptr, tr("提示"), warningMessage);
		// 重新聚焦到错误的单元格
		ui.tableWidget->setCurrentCell(row, column);
		ui.tableWidget->editItem(item);
	}
	emit sgSendShowTips(message);
}
