#include "PLCConfigWidget.h"
#include <QTcpSocket>
#include <QMouseEvent>
#include <QEvent>
#include "UiDiySet.h"
#include "UiReadTableSet.h"

#pragma execution_character_set("utf-8")
PLCConfigWidget::PLCConfigWidget(QWidget *parent)
	: QWidget(parent)
{
	init();
}

PLCConfigWidget::~PLCConfigWidget()
{
}

void PLCConfigWidget::initUI(QWidget *widget)
{
	pUi = new Ui_PLC;
	pUi->setupUi(widget);
	pUi->tableWidget_read->setSelectionBehavior(QAbstractItemView::SelectRows);
	pUi->tableWidget_read->setSelectionMode(QAbstractItemView::SingleSelection);
	pUi->tableWidget_send->setSelectionBehavior(QAbstractItemView::SelectRows);
	pUi->tableWidget_send->setSelectionMode(QAbstractItemView::SingleSelection);
	pUi->tableWidget_read->viewport()->installEventFilter(this);
	pUi->tableWidget_send->viewport()->installEventFilter(this);
	initDataShow();
	initProtocolShow();
	initConnect();
}

bool PLCConfigWidget::hasConfigChanged() const
{
	QString current_ip = pUi->lineEdit_ip->text();
	int current_port = pUi->spinBox_port->value();
	int current_heart_beat_warn = pUi->spinBox_beat_warn->value();
	bool current_print = pUi->checkBox_print->isChecked();
	if (current_ip != m_origin_ip || current_port != m_origin_port || current_heart_beat_warn != m_origin_heart_beat_warn || current_print != b_origin_print)
		return true;
	// 只比较表格相关的协议数据
	QVariantMap currentSendData = getSendTableData();
	QVariantMap currentReadData = getReadTableData();
	// 从原始协议数据中提取表格相关数据
	QVariantMap originTableData;
	for (auto it = m_originMp.begin(); it != m_originMp.end(); ++it) {
		QString key = it.key();
		if (key.startsWith("read_") || key.startsWith("send_")) {
			originTableData[key] = it.value();
		}
	}
	// 合并当前表格数据
	QVariantMap currentTableData;
	currentTableData.unite(currentSendData);
	currentTableData.unite(currentReadData);
	// 比较表格数据是否改变
	return currentTableData != originTableData;
	//if (m_protocolMp != m_originMp)
	//	return true;
	//return false;
	//return m_isConfigChanged;
}

bool PLCConfigWidget::onSaveConfig()
{
	if (!hasConfigChanged()) {
		return false;
	}
	m_ip = pUi->lineEdit_ip->text();
	m_port = pUi->spinBox_port->value();
	m_heart_beat_warn = pUi->spinBox_beat_warn->value();
	b_print = pUi->checkBox_print->isChecked();
	auto &data = gobalFun::f_readFile("./lpIPUConfig/lpPLCConfig.json");
	if (data.isNull()) {
		qWarning() << "Failed to read lpPLCConfig.josn!" << __FUNCTION__;
		return false;
	}

	QJsonDocument doc = QJsonDocument::fromJson(data);
	QJsonObject rootObj = doc.object();
	QJsonObject configObj = rootObj.value("config").toObject();
	// 更新config数据
	configObj["tcp_server_ip"] = m_ip;
	configObj["tcp_server_port"] = m_port;
	configObj["t_heartbeat_out_warn"] = m_heart_beat_warn;
	configObj["b_print"] = b_print;

	QJsonObject protocolObj = rootObj.value("protocol").toObject();
	QVariantMap originalProtocolMp = protocolObj.toVariantMap();

	// 获取当前表格数据
	QVariantMap sendTableMp = getSendTableData();
	QVariantMap readTableMp = getReadTableData();
	// 只更新表格相关的数据，保留其他协议数据
	// 先移除所有以"read_"和"send_"开头的字段
	QStringList keysToRemove;
	for (auto it = originalProtocolMp.begin(); it != originalProtocolMp.end(); ++it) {
		QString key = it.key();
		if (key.startsWith("read_") || key.startsWith("send_")) {
			keysToRemove.append(key);
		}
	}
	// 移除旧的表格数据
	foreach(const QString &key, keysToRemove) {
		originalProtocolMp.remove(key);
	}
	// 添加新的表格数据
	originalProtocolMp.unite(sendTableMp);
	originalProtocolMp.unite(readTableMp);

	// 更新protocol对象
	protocolObj = QJsonObject::fromVariantMap(originalProtocolMp);
	//QJsonObject protocolObj = QJsonObject::fromVariantMap(m_protocolMp);
	rootObj["protocol"] = protocolObj;
	rootObj["config"] = configObj;
	// 写回文件
	bool saveSuccess = gobalFun::f_saveJson(rootObj, QString("./lpIPUConfig/lpPLCConfig.json"));
	if (saveSuccess) {
		m_protocolMp = originalProtocolMp;// 更新内存中的m_protocolMp
		recordOriginalConfig();// 保存成功后更新原始配置记录
		
	}
	else {
		qWarning() << "Failed to save config file" << __FUNCTION__;
	}

	return saveSuccess;
}

bool PLCConfigWidget::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::MouseButtonPress) {
		QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

		if (obj == pUi->tableWidget_read->viewport()) {
			if (mouseEvent->button() == Qt::RightButton) {
				handleContextMenu(pUi->tableWidget_read, mouseEvent->pos());
				return true;
			}
		}
		else if (obj == pUi->tableWidget_send->viewport()) {
			if (mouseEvent->button() == Qt::RightButton) {
				handleContextMenu(pUi->tableWidget_send, mouseEvent->pos());
				return true;
			}
		}
	}
	return QWidget::eventFilter(obj, event);
}

void PLCConfigWidget::initConnect()
{
	connect(pUi->btn_link, &QPushButton::clicked, this, &PLCConfigWidget::onTestLink);
	connect(pUi->tableWidget_read, &QTableWidget::itemDoubleClicked, this, &PLCConfigWidget::onDiyItemDoubleClicked);
	connect(pUi->tableWidget_send, &QTableWidget::cellChanged, this, &PLCConfigWidget::validateSendTableCell);	// 连接单元格变化信号进行实时验证
	connect(pUi->tableWidget_send, &QTableWidget::cellChanged,this, &PLCConfigWidget::onSendCellChanged);
}

void PLCConfigWidget::onTestLink()
{
	m_ip = pUi->lineEdit_ip->text();
	m_port = pUi->spinBox_port->value();
	QTcpSocket socket;
	socket.connectToHost(m_ip, m_port);
	if (socket.waitForConnected(3000)) {
		QMessageBox::information(nullptr, tr("弹窗提示："), tr("PLC连接成功"));
		emit sgSendShowTips(tr("PLC连接成功"));
	}
	else {
		QMessageBox::warning(nullptr, tr("弹窗提示："), tr("PLC连接失败"));
		emit sgSendShowTips(tr("PLC连接失败"));
		qWarning() << "plc link failed!" <<__FUNCTION__;
	}
}

void PLCConfigWidget::onDiyItemDoubleClicked(QTableWidgetItem *item)
{
	if (item->column() == 3) {
		int row = item->row();
		QTableWidgetItem *nameItem = pUi->tableWidget_read->item(row, 0);
		QTableWidgetItem *typeItem = pUi->tableWidget_read->item(row, 3);
		if (!nameItem) return;
		QString fieldPath = nameItem->text();
		if (m_protocolMp.contains(fieldPath)) {
			QVariantMap readData = m_protocolMp[fieldPath].toMap();
			QString addr = readData.value("addr").toString();
			int cnt = readData.value("cnt").toInt();
			if (readData.contains("diy")) {
				QVariantMap diyData = readData.value("diy").toMap();
				UiDiySet *uiDiySet = new UiDiySet(nullptr);
				connect(uiDiySet, &UiDiySet::sgDiyDataUpdated, this,&PLCConfigWidget::onUpdataData);
				connect(uiDiySet, &UiDiySet::sgSendShowTips, this, &PLCConfigWidget::sgSendShowTips);
				uiDiySet->initTableData(Diy_dialog, diyData,addr,cnt, fieldPath);
				uiDiySet->exec();
				uiDiySet->deleteLater();
			}
			else if (readData.contains("reg")) {
				QVariantMap regData = readData.value("reg").toMap();
				UiDiySet *uiDiySet = new UiDiySet(nullptr);
				connect(uiDiySet, &UiDiySet::sgDiyDataUpdated, this, &PLCConfigWidget::onUpdataData);
				connect(uiDiySet, &UiDiySet::sgSendShowTips, this, &PLCConfigWidget::sgSendShowTips);
				uiDiySet->initTableData(Reg_dialog, regData, addr, cnt, fieldPath);
				uiDiySet->exec();
				uiDiySet->deleteLater();
			}
		}
		else {//如果是自己新建行，需要添加diy或者reg的信息,因为加载的mp里面没有新key的信息
			QString type = typeItem->text();
			QVariantMap mp;
			if (type == "diy") {
				UiDiySet *uiDiySet = new UiDiySet(nullptr);
				connect(uiDiySet, &UiDiySet::sgDiyDataUpdated, this, &PLCConfigWidget::onUpdataData);
				connect(uiDiySet, &UiDiySet::sgSendShowTips, this, &PLCConfigWidget::sgSendShowTips);
				uiDiySet->initTableData(Diy_dialog, mp, "", 1, fieldPath);
				uiDiySet->exec();
				uiDiySet->deleteLater();
			}
			else if (type == "reg") {
				UiDiySet *uiDiySet = new UiDiySet(nullptr);
				connect(uiDiySet, &UiDiySet::sgDiyDataUpdated, this, &PLCConfigWidget::onUpdataData);
				connect(uiDiySet, &UiDiySet::sgSendShowTips, this, &PLCConfigWidget::sgSendShowTips);
				uiDiySet->initTableData(Reg_dialog, mp, "", 1, fieldPath);
				uiDiySet->exec();
				uiDiySet->deleteLater();
			}
		}
	}
}

void PLCConfigWidget::onUpdataData(const QString &fieldPath, const QVariantMap &updatedData)
{
	if (fieldPath.trimmed().isEmpty()) {
		qWarning() << "onUpdataData: empty fieldPath";
		return;
	}

	QVariantMap readData;
	bool existed = false;
	if (m_protocolMp.contains(fieldPath)) {
		readData = m_protocolMp.value(fieldPath).toMap();
		existed = true;
	}
	else {
		// 尝试通过表格中 UserRole 找到旧 key（如果用户重命名过） 或者直接新建
		int row = findReadRowByName(fieldPath);
		if (row >= 0) {
			QTableWidgetItem *addrItem = pUi->tableWidget_read->item(row, 1);
			QTableWidgetItem *cntItem = pUi->tableWidget_read->item(row, 2);
			QTableWidgetItem *tipItem = pUi->tableWidget_read->item(row, 4);
			if (addrItem) readData["addr"] = addrItem->text().trimmed();
			if (cntItem)  readData["cnt"] = cntItem->text().toInt();
			if (tipItem)  readData["tip"] = tipItem->text().trimmed();
		}
		// else：如果没有找到行，也直接新建 map（后续保存会把它写入）
	}
	bool isDiy = false;
	for (auto it = updatedData.begin(); it != updatedData.end(); ++it) {
		if (it.value().type() == QVariant::Map) {
			QVariantMap sub = it.value().toMap();
			if (sub.contains("key") || sub.contains("type") || sub.contains("cnt")) {
				isDiy = true;
				break;
			}
		}
	}

	if (isDiy) {
		readData["diy"] = updatedData;
	}
	else {
		readData["reg"] = updatedData;
	}
	// 写回主 map（若原来存在，覆盖其中的 diy/reg 并保留其它字段）
	m_protocolMp.insert(fieldPath, readData);
	// 在表格里把该行的 UserRole 更新为 fieldPath（用于后续合并与查找）
	int foundRow = findReadRowByName(fieldPath);
	if (foundRow >= 0) {
		QTableWidgetItem *nameItem = pUi->tableWidget_read->item(foundRow, 0);
		if (nameItem) nameItem->setData(Qt::UserRole, fieldPath);
	}
	//m_isConfigChanged = true;
}

void PLCConfigWidget::onAddDataToReadTable(const QVariantMap &newData)
{
	for (auto it = newData.begin(); it != newData.end(); ++it) {
		QVariantMap itemMp = it.value().toMap();
		int row = (m_currentRow >= 0) ? m_currentRow + 1 : pUi->tableWidget_read->rowCount();
		pUi->tableWidget_read->insertRow(row);
		for (auto itMp = itemMp.begin(); itMp != itemMp.end(); ++itMp) {
			QTableWidgetItem *nameItem = new QTableWidgetItem(itemMp.value("name").toString());
			pUi->tableWidget_read->setItem(row, 0, nameItem);
			QTableWidgetItem *addrItem = new QTableWidgetItem(itemMp.value("addr").toString());
			pUi->tableWidget_read->setItem(row, 1, addrItem);
			QTableWidgetItem *cntItem = new QTableWidgetItem(itemMp.value("cnt").toString());
			pUi->tableWidget_read->setItem(row, 2, cntItem);
			QTableWidgetItem*typeItem = new QTableWidgetItem(itemMp.value("type").toString());
			typeItem->setFlags(typeItem->flags() & ~Qt::ItemIsEditable);
			pUi->tableWidget_read->setItem(row, 3, typeItem);
			if (itemMp.contains("tip")) {
				QTableWidgetItem *tipItem = new QTableWidgetItem(itemMp.value("tip").toString());
				pUi->tableWidget_read->setItem(row, 4, tipItem);
			}
		}
		row++;
	}
}

void PLCConfigWidget::onSendCellChanged(int row, int col)
{
	if (col != 0 && col != 1) return;
	auto *nameItem = pUi->tableWidget_send->item(row, 0);
	if (!nameItem) return;
	QString key = nameItem->text().trimmed();
	QString newVal = pUi->tableWidget_send->item(row, col)->text().trimmed();
	m_delta.erase(std::remove_if(m_delta.begin(), m_delta.end(),
		[&](const CellDelta &d)
		{ return d.key == key && d.col == col; }),
		m_delta.end());
	m_delta.append({ key, col, newVal });
}

void PLCConfigWidget::init()
{
	auto &data = gobalFun::f_readFile("./lpIPUConfig/lpPLCConfig.json");
	if (!data.isNull()) {
		QJsonObject obj = QJsonDocument::fromJson(data).object();
		QJsonObject configObj = obj.value("config").toObject();
		m_ip = configObj.value("tcp_server_ip").toString();
		m_port = configObj.value("tcp_server_port").toInt();
		m_heart_beat_warn = configObj.value("t_heartbeat_out_warn").toInt();
		b_print = configObj.value("b_print").toBool();
		QJsonObject protocolObj = obj.value("protocol").toObject();
		m_protocolMp = protocolObj.toVariantMap();
		m_originMp = m_protocolMp;
		m_origin_ip = m_ip;
		m_origin_port = m_port;
		m_origin_heart_beat_warn = m_heart_beat_warn;
		b_origin_print = b_print;
	}
}

void PLCConfigWidget::initDataShow()
{
	pUi->lineEdit_ip->setText(m_ip);
	pUi->spinBox_port->setValue(m_port);
	pUi->spinBox_beat_warn->setValue(m_heart_beat_warn);
	pUi->checkBox_print->setChecked(b_print);
}

void PLCConfigWidget::initProtocolShow()
{
	pUi->tableWidget_read->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	pUi->tableWidget_send->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	for (auto it = m_protocolMp.begin(); it != m_protocolMp.end(); ++it) {
		QString key = it.key();
		QVariant value = it.value();
		if (key.startsWith("read_")) {
			int row = 0;
			QVariantMap readMp = value.toMap();
			pUi->tableWidget_read->insertRow(row);
			QTableWidgetItem *nameItem = new QTableWidgetItem(key);
			pUi->tableWidget_read->setItem(row, 0, nameItem);
			for (auto readIt = readMp.begin(); readIt != readMp.end(); ++readIt) {
				QString readKey = readIt.key();
				QVariant showValue = readIt.value();

				if (readKey == "addr") {
					QTableWidgetItem *addrItem = new QTableWidgetItem(showValue.toString());
					pUi->tableWidget_read->setItem(row, 1, addrItem);
				}
				else if (readKey == "cnt") {
					QTableWidgetItem *cntItem = new QTableWidgetItem(showValue.toString());
					pUi->tableWidget_read->setItem(row, 2, cntItem);
				}
				else if (readKey == "diy") {
					QTableWidgetItem *diyItem = new QTableWidgetItem(readKey);
					diyItem->setFlags(diyItem->flags() & ~Qt::ItemIsEditable);
					pUi->tableWidget_read->setItem(row, 3, diyItem);
				}
				else if (readKey == "reg") {
					QTableWidgetItem *regItem = new QTableWidgetItem(readKey);
					regItem->setFlags(regItem->flags() & ~Qt::ItemIsEditable);
					pUi->tableWidget_read->setItem(row, 3, regItem);
				}
				else if (readKey == "keys") {
					QTableWidgetItem *keysItem = new QTableWidgetItem(readKey);
					keysItem->setFlags(keysItem->flags() & ~Qt::ItemIsEditable);
					pUi->tableWidget_read->setItem(row, 3, keysItem);
				}
				else if (readKey == "tip") {
					QTableWidgetItem *tipItem = new QTableWidgetItem(showValue.toString());
					pUi->tableWidget_read->setItem(row, 4, tipItem);
				}
			}
			row++;
		}
		else if (key.startsWith("send_")) {
			int row = 0;
			pUi->tableWidget_send->insertRow(row);
			QTableWidgetItem *nameItem = new QTableWidgetItem(key);
			pUi->tableWidget_send->setItem(row, 0, nameItem);
			QTableWidgetItem *valueItem = new QTableWidgetItem(value.toString());
			pUi->tableWidget_send->setItem(row, 1, valueItem);
			QTableWidgetItem *tipItem = new QTableWidgetItem("");//提示说明列，初始为空
			tipItem->setFlags(tipItem->flags() & ~Qt::ItemIsEditable);
			pUi->tableWidget_send->setItem(row, 2, tipItem);
			row++;
		}
	}
}

void PLCConfigWidget::handleContextMenu(QTableWidget *table, const QPoint &pos)
{
	QMenu menu;
	QAction *addAction = menu.addAction(tr("添加行"));
	QAction *delAction = menu.addAction(tr("删除行"));

	QAction *selected = menu.exec(table->viewport()->mapToGlobal(pos));
	QTableWidgetItem *item = table->itemAt(pos);
	if (item) {
		m_currentRow = item->row();
	}
	else {
		m_currentRow = -1;
	}

	if (selected == addAction) {
		int newRow = (m_currentRow >= 0) ? m_currentRow + 1 : table->rowCount();
		if (table == pUi->tableWidget_send) {
			table->insertRow(newRow);
			setupSendTableRow(newRow);
		}
		else if (table == pUi->tableWidget_read) {
			UiReadTableSet *uiReadTableSet = new UiReadTableSet(nullptr);
			connect(uiReadTableSet, &UiReadTableSet::sgAddDataToReadTable, this, &PLCConfigWidget::onAddDataToReadTable);
			connect(uiReadTableSet, &UiReadTableSet::sgSendShowTips, this, &PLCConfigWidget::sgSendShowTips);
			uiReadTableSet->exec();
			uiReadTableSet->deleteLater();
		}
		table->scrollToItem(table->item(newRow, 0));
	}
	else if (selected == delAction) {
		if (!table || m_currentRow < 0 || m_currentRow >= table->rowCount()) {
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
			QTableWidgetItem *nameItem = table->item(m_currentRow, 0);
			if (nameItem) {
				QString fieldPath = nameItem->text();
				if (m_protocolMp.contains(fieldPath)) {
					m_protocolMp.remove(fieldPath);
				}
			}
			table->removeRow(m_currentRow);
			m_currentRow = -1;
		}
	}
}

void PLCConfigWidget::setupSendTableRow(int row)
{
	QTableWidgetItem *nameItem = new QTableWidgetItem(tr(""));
	pUi->tableWidget_send->setItem(row, 0, nameItem);

	QTableWidgetItem *addrItem = new QTableWidgetItem(tr(""));
	pUi->tableWidget_send->setItem(row, 1, addrItem);

	QTableWidgetItem *tipItem = new QTableWidgetItem("");
	pUi->tableWidget_send->setItem(row, 2, tipItem);
}

QVariantMap PLCConfigWidget::getSendTableData() const
{
	QVariantMap result;
	for (int row = 0; row < pUi->tableWidget_send->rowCount(); ++row) {
		QTableWidgetItem *keyItem = pUi->tableWidget_send->item(row, 0);
		if (!keyItem || keyItem->text().trimmed().isEmpty()) {
			continue;
		}
		QString key = keyItem->text().trimmed();

		QTableWidgetItem *valueItem = pUi->tableWidget_send->item(row, 1);
		if (valueItem && !valueItem->text().trimmed().isEmpty()) {
			result[key] = valueItem->text().trimmed();
		}
		else {
			result[key] = "";
		}
	}
	return result;
}

QVariantMap PLCConfigWidget::getReadTableData() const
{
	QVariantMap result;
	for (int row = 0; row < pUi->tableWidget_read->rowCount(); ++row) {
		QTableWidgetItem *nameItem = pUi->tableWidget_read->item(row, 0);
		QTableWidgetItem *addrItem = pUi->tableWidget_read->item(row, 1);
		QTableWidgetItem *cntItem = pUi->tableWidget_read->item(row, 2);  
		QTableWidgetItem *typeItem = pUi->tableWidget_read->item(row, 3);
		QTableWidgetItem *tipItem = pUi->tableWidget_read->item(row, 4);

		if (!nameItem || nameItem->text().trimmed().isEmpty()) {
			continue;
		}
		QString name = nameItem->text().trimmed();
		QString addr = addrItem->text().trimmed();
		int     cnt = cntItem->text().toInt();
		QString type = typeItem ? typeItem->text().trimmed() : QString();
		QString tip = tipItem ? tipItem->text().trimmed() : QString();
		QVariantMap itemMap;
		itemMap["addr"] = addr;
		itemMap["cnt"] = cnt;
		if (!tip.isEmpty()) {
			itemMap["tip"] = tip;
		}

		QVariantMap original;
		if (m_protocolMp.contains(name)) {
			original = m_protocolMp.value(name).toMap();
		}
		else {
			QString oldKey = nameItem->data(Qt::UserRole).toString();
			if (!oldKey.isEmpty() && m_protocolMp.contains(oldKey))
				original = m_protocolMp.value(oldKey).toMap();
		}

		QVariantMap finalMap = itemMap;
		if (type == "diy") {
			if (original.contains("diy")) {
				finalMap["diy"] = original.value("diy");
			}
			else {
				// 初次创建 diy，可以初始化为空 map
				finalMap["diy"] = QVariantMap();
			}
		}
		else if (type == "reg") {
			if (original.contains("reg")) {
				finalMap["reg"] = original.value("reg");
			}
			else {
				finalMap["reg"] = QVariantMap();
			}
		}
		else if (type == "keys") {
			if (original.contains("keys")) 
				finalMap["keys"] = original.value("keys");
		}
		result.insert(name, finalMap);
	}
	return result;
}

int PLCConfigWidget::findReadRowByName(const QString &name) const
{
	for (int i = 0; i < pUi->tableWidget_read->rowCount(); ++i) {
		QTableWidgetItem *it = pUi->tableWidget_read->item(i, 0);
		if (it && it->text().trimmed() == name) 
			return i;
		// 也可以比较 UserRole 存的旧 key
		if (it) {
			QString oldKey = it->data(Qt::UserRole).toString();
			if (!oldKey.isEmpty() && oldKey == name) 
				return i;
		}
	}
	return -1;
}

void PLCConfigWidget::recordOriginalConfig()
{
	m_origin_ip = m_ip;
	m_origin_port = m_port;
	m_origin_heart_beat_warn = m_heart_beat_warn;
	b_origin_print = b_print;
	m_originMp = m_protocolMp;
}

void PLCConfigWidget::validateSendTableCell(int row, int column)
{
	if (row >= pUi->tableWidget_send->rowCount()) return;

	QTableWidgetItem *item = pUi->tableWidget_send->item(row, column);
	if (!item) return;

	QString text = item->text().trimmed();
	bool isValid = false;
	QString message;
	QString warningMessage;

	if (column == 0) {
		if (text.startsWith("send_") && text.length() > 6) {
			// 检查是否只包含允许的字符
			QString rest = text.mid(5); // 去掉"send_"
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
			warningMessage = tr("必须以'send_'开头且长度大于6");
		}
	}
	else if (column == 1) {
		bool ok;
		int value = text.toInt(&ok);
		if (ok && value >= 10000 && value <= 65534) {
			isValid = true;
			message = tr("✓ 地址格式正确");
		}
		else {
			warningMessage = tr("请输入数字,地址范围：10000-65534");
		}
	}
	if (!warningMessage.isEmpty()) {
		QMessageBox::warning(nullptr, tr("提示"), warningMessage);
		// 重新聚焦到错误的单元格
		pUi->tableWidget_send->setCurrentCell(row, column);
		pUi->tableWidget_send->editItem(item);
	}
	emit sgSendShowTips(message);
}
