#include "UiDiySet.h"
#include <QMessageBox>

#pragma execution_character_set("utf-8")
UiDiySet::UiDiySet(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	ui.tab_reg->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.tab_diy->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.tab_diy->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tab_diy->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.tab_reg->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tab_reg->setSelectionMode(QAbstractItemView::SingleSelection);
	setDialogType(DialogType::Diy_dialog);
	setupContextMenu();
	initConnect();
}

UiDiySet::~UiDiySet()
{
}

void UiDiySet::setDialogType(DialogType type)
{
	switch (type){
		case Reg_dialog: 
			ui.tab_diy->hide();
			break;
		case Diy_dialog:
		default: 
			ui.tab_reg->hide();
			break;
	}
}

void UiDiySet::initTableData(DialogType type, QVariantMap vm, const QString &addr, const int cnt, const QString &fieldPath)
{
	m_originalData = vm;
	m_readParentKey = fieldPath;
	ui.lb_addr_data->setText(addr);
	ui.lb_cnt_data->setText(QString::number(cnt));
	switch (type) {
	case Reg_dialog: {
		ui.tab_diy->hide();
		ui.tab_reg->show();
		// 遍历reg数据
		int row = 0;
		for (auto it = vm.begin(); it != vm.end(); ++it) {
			QString address = it.key();
			QVariantMap itemData = it.value().toMap();
			ui.tab_reg->insertRow(row);

			QTableWidgetItem *addrItem = new QTableWidgetItem(address);
			ui.tab_reg->setItem(row, 0, addrItem);

			QTableWidgetItem *trueValueItem = new QTableWidgetItem();
			if (itemData.contains("true_value")) {
				trueValueItem->setText(itemData.value("true_value").toString());
			}
			ui.tab_reg->setItem(row, 1, trueValueItem);

			QTableWidgetItem *trueAliasItem = new QTableWidgetItem();
			if (itemData.contains("true_alias")) {
				trueAliasItem->setText(itemData.value("true_alias").toString());
			}
			ui.tab_reg->setItem(row, 2, trueAliasItem);

			QTableWidgetItem *falseValueItem = new QTableWidgetItem();
			if (itemData.contains("false_value")) {
				falseValueItem->setText(itemData.value("false_value").toString());
			}
			ui.tab_reg->setItem(row, 3, falseValueItem);

			QTableWidgetItem *falseAliasItem = new QTableWidgetItem();
			if (itemData.contains("false_alias")) {
				falseAliasItem->setText(itemData.value("false_alias").toString());
			}
			ui.tab_reg->setItem(row, 4, falseAliasItem);

			row++;
		}
		break;
	}
	case Diy_dialog:
	default:
		ui.tab_reg->hide();
		int row = 0;
		for (auto it = vm.begin(); it != vm.end(); ++it) {
			QString address = it.key();
			QVariantMap itemData = it.value().toMap();

			ui.tab_diy->insertRow(row);

			QTableWidgetItem *addrItem = new QTableWidgetItem(address);
			ui.tab_diy->setItem(row, 0, addrItem);

			QTableWidgetItem *keyItem = new QTableWidgetItem();
			if (itemData.contains("key")) {
				keyItem->setText(itemData.value("key").toString());
			}
			ui.tab_diy->setItem(row, 1, keyItem);

			QTableWidgetItem *cntItem = new QTableWidgetItem();
			if (itemData.contains("cnt")) {
				cntItem->setText(itemData.value("cnt").toString());
			}
			ui.tab_diy->setItem(row, 2, cntItem);

			QComboBox *typeComboBox = new QComboBox();
			setTypeComboBox(typeComboBox);

			QTableWidgetItem *typeItem = new QTableWidgetItem();
			if (itemData.contains("type")) {
				int typeValue = itemData.value("type").toInt();
				typeComboBox->setCurrentIndex(typeValue); 
			}
			ui.tab_diy->setCellWidget(row, 3, typeComboBox);

			//说明列，一些提示信息
			QTableWidgetItem *tipItem = new QTableWidgetItem();
			if (itemData.contains("tip")) {//有tip信息就加载
				tipItem->setText(itemData.value("tip").toString());
			}
			ui.tab_diy->setItem(row, 4, tipItem);

			row++;
		}
		break;
	}
}

void UiDiySet::initConnect()
{
	connect(ui.btn_cancel, &QPushButton::clicked, this,&QDialog::reject);
	connect(ui.btn_confirm, &QPushButton::clicked, this,&UiDiySet::onConfirmButtonClicked);
	connect(ui.tab_diy, &QTableWidget::customContextMenuRequested,
		this, &UiDiySet::onCustomContextMenuRequested);
	connect(ui.tab_reg, &QTableWidget::customContextMenuRequested,
		this, &UiDiySet::onCustomContextMenuRequested);
	bool ok= connect(ui.tab_diy, &QTableWidget::cellChanged, this, &UiDiySet::validateReadTableCell);
	connect(ui.tab_reg, &QTableWidget::cellChanged, this, &UiDiySet::validateReadTableCell);
}

void UiDiySet::onCustomContextMenuRequested(const QPoint &pos)
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

void UiDiySet::onAddRow()
{
	QTableWidget *currentTable = getCurrentTable();
	if (!currentTable) return;

	int newRow = (m_currentRow >= 0) ? m_currentRow + 1 : currentTable->rowCount();//在选中行的下一行添加
	currentTable->insertRow(newRow);
	if (currentTable == ui.tab_diy) {
		setupNewDiyRow(newRow);
	}
	else if (currentTable == ui.tab_reg) {
		setupNewRegRow(newRow);
	}
	currentTable->scrollToItem(currentTable->item(newRow, 0));
}

void UiDiySet::onDeleteRow()
{
	QTableWidget *currentTable = getCurrentTable();
	if (!currentTable || m_currentRow < 0 || m_currentRow >= currentTable->rowCount()) {
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
		currentTable->removeRow(m_currentRow);
		m_currentRow = -1; // 重置当前行
	}
}

void UiDiySet::onConfirmButtonClicked()
{
	QVariantMap updatedDataMp;
	if (ui.tab_diy->isVisible()) {
		updatedDataMp= getDiyData();
	}
	else{
		updatedDataMp = getRegData();
	}

	emit sgDiyDataUpdated(m_readParentKey,updatedDataMp);
	accept();
}

void UiDiySet::setTypeComboBox(QComboBox *comboBox)
{
	comboBox->clear();
	comboBox->addItem(tr("0-整型"), 0);
	comboBox->addItem(tr("1-字符串"), 1);    
	comboBox->addItem(tr("2-时间"), 2);      
	comboBox->addItem("3-SID", 3);
	comboBox->addItem(tr("4-PLC原始数据"), 4);
}

void UiDiySet::setupContextMenu()
{
	m_contextMenu = new QMenu();

	QAction *addAction = new QAction(tr("添加行"), nullptr);
	QAction *deleteAction = new QAction(tr("删除行"), nullptr);

	m_contextMenu->addAction(addAction);
	m_contextMenu->addAction(deleteAction);

	connect(addAction, &QAction::triggered, this, &UiDiySet::onAddRow);
	connect(deleteAction, &QAction::triggered, this, &UiDiySet::onDeleteRow);
	ui.tab_diy->setContextMenuPolicy(Qt::CustomContextMenu);
	ui.tab_reg->setContextMenuPolicy(Qt::CustomContextMenu);
}

QTableWidget* UiDiySet::getCurrentTable() const
{
	if (ui.tab_diy->isVisible()) {
		return ui.tab_diy;
	}
	else if (ui.tab_reg->isVisible()) {
		return ui.tab_reg;
	}
	return nullptr;
}

void UiDiySet::setupNewDiyRow(int row)
{
	QTableWidgetItem *addrItem = new QTableWidgetItem(tr("新地址"));
	ui.tab_diy->setItem(row, 0, addrItem);

	QTableWidgetItem *keyItem = new QTableWidgetItem(tr("新键名"));
	ui.tab_diy->setItem(row, 1, keyItem);

	QTableWidgetItem *cntItem = new QTableWidgetItem("1");
	ui.tab_diy->setItem(row, 2, cntItem);

	QComboBox *typeComboBox = new QComboBox();
	setTypeComboBox(typeComboBox);
	typeComboBox->setCurrentIndex(0); 
	ui.tab_diy->setCellWidget(row, 3, typeComboBox);
}

void UiDiySet::setupNewRegRow(int row)
{
	QTableWidgetItem *addrItem = new QTableWidgetItem(tr(""));
	ui.tab_reg->setItem(row, 0, addrItem);

	for (int col = 1; col < ui.tab_reg->columnCount(); ++col) {
		QTableWidgetItem *item = new QTableWidgetItem("");
		ui.tab_reg->setItem(row, col, item);
	}
}

QVariantMap UiDiySet::getDiyData() const
{
	QVariantMap result;
	int rowcount= ui.tab_diy->rowCount();
	for (int row = 0; row < ui.tab_diy->rowCount(); ++row) {
		QTableWidgetItem *addrItem = ui.tab_diy->item(row, 0);
		if (!addrItem || addrItem->text().trimmed().isEmpty()) {
			continue;
		}
		QString address = addrItem->text().trimmed();
		QVariantMap itemData;

		QTableWidgetItem *keyItem = ui.tab_diy->item(row, 1);
		if (keyItem && !keyItem->text().trimmed().isEmpty()) {
			itemData["key"] = keyItem->text().trimmed();
		}

		QTableWidgetItem *cntItem = ui.tab_diy->item(row, 2);
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

		QComboBox *typeComboBox = qobject_cast<QComboBox*>(ui.tab_diy->cellWidget(row, 3));
		if (typeComboBox) {
			int typeValue = typeComboBox->currentData().toInt();
			itemData["type"] = typeValue;
		}

		//说明列，一些提示信息
		QTableWidgetItem *tipItem = ui.tab_diy->item(row, 4);
		if (tipItem && !tipItem->text().trimmed().isEmpty()) {
			itemData["tip"] = tipItem->text().trimmed();
		}


		if (!itemData.isEmpty()) {
			result[address] = itemData;
		}
	}

	return result;
}

QVariantMap UiDiySet::getRegData() const
{
	QVariantMap result;
	int rowCout = ui.tab_reg->rowCount();
	for (int row = 0; row < ui.tab_reg->rowCount(); ++row) {
		QTableWidgetItem *addrItem = ui.tab_reg->item(row, 0);
		if (!addrItem || addrItem->text().trimmed().isEmpty()) {
			continue;
		}
		QString address = addrItem->text().trimmed();
		QVariantMap itemData;

		QTableWidgetItem *trueValueItem = ui.tab_reg->item(row, 1);
		if (trueValueItem && !trueValueItem->text().trimmed().isEmpty()) {
			bool ok;
			int cntValue = trueValueItem->text().toInt(&ok);
			if (ok && cntValue > 0) {
				itemData["true_value"] = cntValue;
			}
			else {
				itemData["true_value"] = trueValueItem->text().trimmed();// 保持原始文本，让上层处理
			}
		}

		QTableWidgetItem *tureAliasItem = ui.tab_reg->item(row, 2);
		if (tureAliasItem && !tureAliasItem->text().trimmed().isEmpty()) {
	
			itemData["true_alias"] = tureAliasItem->text().trimmed(); 

		}

		QTableWidgetItem *falseValueItem = ui.tab_reg->item(row, 3);
		if (falseValueItem && !falseValueItem->text().trimmed().isEmpty()) {
			bool ok;
			int cntValue = falseValueItem->text().toInt(&ok);
			if (ok && cntValue > 0) {
				itemData["false_value"] = cntValue;
			}
			else {
				itemData["false_value"] = falseValueItem->text().trimmed();// 保持原始文本，让上层处理
			}
		}

		QTableWidgetItem *falseAliasItem = ui.tab_reg->item(row, 4);
		if (falseAliasItem && !falseAliasItem->text().trimmed().isEmpty()) {

			itemData["false_alias"] = falseAliasItem->text().trimmed();

		}
		if (!itemData.isEmpty()) {
			result[address] = itemData;
		}
	}

	return result;
}

void UiDiySet::validateReadTableCell(int row, int column)
{
	if (ui.tab_diy->isVisible()) {
		validDiyTableCell(row, column);
	}
	else if (ui.tab_reg->isVisible()) {
		validRegTableCell(row, column);
	}
}

void UiDiySet::validRegTableCell(int row, int column)
{
	if (row >= ui.tab_reg->rowCount()) return;

	QTableWidgetItem *item = ui.tab_reg->item(row, column);

	QString text = item->text().trimmed();
	bool isValid = false;
	QString message;
	QString warningMessage;
	if (column == 0) {
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
				warningMessage = tr("地址范围：10000-65534");
			}
		}
	}
	else if (column == 1 || column == 3) {
		bool ok;
		int trueOrFalseValue = text.toInt(&ok);
		if (ok && trueOrFalseValue >= 1 && trueOrFalseValue <= 999) {
			isValid = true;
			message = tr("✓ 取值格式正确");
		}
		else {
			warningMessage = tr("请输入是数字，取值范围：1-999");
		}
	}
	else if (column == 2 || column == 4) {
		QRegularExpression regExp("^[a-zA-Z0-9_]*$");
		if (regExp.match(text).hasMatch()) {
			isValid = true;
			message = tr("✓ 名称格式正确");
		}
		else {
			warningMessage = tr("只能包含字母、数字、下划线");
		}
	}
	if (!warningMessage.isEmpty()) {
		QMessageBox::warning(nullptr, tr("提示"), warningMessage);
		ui.tab_reg->setCurrentCell(row, column);
		ui.tab_reg->editItem(item);
	}
	emit sgSendShowTips(message);
}

void UiDiySet::validDiyTableCell(int row, int column)
{
	if (row >= ui.tab_diy->rowCount()) return;
	QTableWidgetItem *item = ui.tab_diy->item(row, column);
	if (!item) return;

	QString text = item->text().trimmed();
	bool isValid = false;
	QString message;
	QString warningMessage;
	if (column == 0) {
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
	else if (column == 1) {
		QRegularExpression regExp("^[a-zA-Z0-9_]*$");
		if (regExp.match(text).hasMatch()) {
			isValid = true;
			message = tr("✓ 名称格式正确");
		}
		else {
			warningMessage = tr("只能包含字母、数字、下划线");
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
				warningMessage = tr("请输入数字，字数范围：1-999");
			}
		}

	}
	if (!warningMessage.isEmpty()) {
		QMessageBox::warning(nullptr, tr("提示"), warningMessage);
		ui.tab_diy->setCurrentCell(row, column);
		ui.tab_diy->editItem(item);
	}
	emit sgSendShowTips(message);
}
