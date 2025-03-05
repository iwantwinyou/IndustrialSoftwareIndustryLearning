#include "GetParams2ExcelTool.h"
#include <QDir>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#pragma execution_character_set("utf-8")

GetParams2ExcelTool::GetParams2ExcelTool(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_work_thread_ptr = new workThreadCtrl(this);
	QString path = qApp->applicationDirPath() + "//lpIPUConfig//detectParam";
	m_allParamsInfoMap = m_work_thread_ptr->getAllParamsInfo(path);
	connect(ui.pushButton, &QPushButton::clicked, this, &GetParams2ExcelTool::saveData2Csv);
}

void GetParams2ExcelTool::saveData2Csv()
{
	//QString csvFilePath = QFileDialog::getSaveFileName(this, tr("保存CSV文件"), "", tr("CSV文件(*.csv);;所有文件(*.*)"));
	//if (csvFilePath.isEmpty()) {
	//	return;
	//}

	//QFile file(csvFilePath);
	//if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
	//	qWarning() << "Failed to open CSV file for writing:" << csvFilePath;
	//	return;
	//}

	//QTextStream out(&file);
	//out.setCodec("UTF-8");

	////确定列标题
	//QStringList headers;
	//for (auto it = m_allParamsInfoMap.constBegin(); it != m_allParamsInfoMap.constEnd(); ++it) {
	//	headers << it.key();//json文件名作为列标题
	//}
	//// 写入 CSV 表头
	////out << "stationName,ParamName,ParamValue,FileName\n"; 
	//out << "stationName,ParamName,";
	//out << headers.join(",") << "\n";
	//for (auto it = m_allParamsInfoMap.constBegin(); it != m_allParamsInfoMap.constEnd(); ++it) {
	//	QString fileName = it.key(); // 获取文件名
	//	QList<ParamInfo> paramsList = it.value(); // 获取参数列表

	//	// 遍历参数列表
	//	for (const ParamInfo& param : paramsList) {
	//		QVariant var = param.ShowValue;
	//		// 根据 QVariant 的类型导出不同的值
	//		QString valueStr;
	//		switch (var.type()) {
	//		case QMetaType::Int: 
	//			valueStr = QString::number(var.toInt());
	//			break;
	//		case QMetaType::Double: 
	//			valueStr = QString::number(var.toDouble());
	//			break;
	//		case QMetaType::QString: 
	//			valueStr = var.toString();
	//			break;
	//		case QMetaType::Bool: 
	//			valueStr = var.toBool() ? "true" : "false";
	//			break;
	//		default: 
	//			valueStr = var.toString(); 
	//			break;
	//		}
	//		// 写入 CSV 行：文件名, 参数名, 参数值
	//		//out<<param.stationName<< "," << param.ShowText << ","<<valueStr<< ","<<fileName <<"\n";
	//		out << param.stationName << "," << param.ShowText << ",";
	//		for (int i = 0; i < headers.size(); ++i) {
	//			bool found = false;
	//			for (const ParamInfo& p : paramsList) {
	//				if (p.stationName == param.stationName && p.ShowText == param.ShowText && headers[i] == it.key()) {
	//					valueStr = p.ShowValue.toString();
	//					found = true;
	//					break;
	//				}
	//			}
	//			if (!found) {
	//				valueStr = ""; // 如果没有找到对应的值，则为空字符串
	//			}
	//			if (i < headers.size() - 1) {
	//				out << valueStr << ",";
	//			}
	//			else {
	//				out << valueStr << "\n";
	//			}
	//		}
	//	}
	//}

	//file.close();

	//QMessageBox::information(this, "提示", "导出成功！");
	//qDebug() << "CSV file saved successfully:" << csvFilePath;
	QString csvFilePath = QFileDialog::getSaveFileName(this, tr("保存CSV文件"), "", tr("CSV文件(*.csv);;所有文件(*.*)"));
	if (csvFilePath.isEmpty()) {
		return;
	}

	QFile file(csvFilePath);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		qWarning() << "Failed to open CSV file for writing:" << csvFilePath;
		return;
	}

	QTextStream out(&file);
	out.setCodec("UTF-8");

	// 确定所有的工位名称
	QStringList stationNames;
	QMap<QString, QStringList> paramsForStations; // 存储每个工位对应的参数名称
	QMap<QString, QStringList> valuesForStations; // 存储每个工位对应的参数值
	for (auto it = m_allParamsInfoMap.constBegin(); it != m_allParamsInfoMap.constEnd(); ++it) {
		const QList<ParamInfo>& paramsList = it.value();
		for (const ParamInfo& param : paramsList) {
			if (!stationNames.contains(param.stationName)) {
				stationNames << param.stationName;
			}
			paramsForStations[param.stationName].append(param.ShowText);
			valuesForStations[param.stationName].append(param.ShowValue.toString());
		}
	}

	// 写入 CSV 表头
	out << "stationName,ParamName";
	for (const QString& fileName : m_allParamsInfoMap.keys()) {
		out << "," << fileName;
	}
	out << "\n";

	// 遍历所有工位
	for (const QString& stationName : stationNames) {
		out << stationName;
		QStringList params = paramsForStations[stationName];
		QStringList values = valuesForStations[stationName];
		for (int i = 0; i < params.size(); ++i) {
			out << "," << params[i];
			for (const QString& fileName : m_allParamsInfoMap.keys()) {
				bool found = false;
				for (const ParamInfo& param : m_allParamsInfoMap[fileName]) {
					if (param.stationName == stationName && param.ShowText == params[i]) {
						out << "," << param.ShowValue.toString();
						found = true;
						break;
					}
				}
				if (!found) {
					out << ",";
				}
			}
			out << "\n";
		}
	}

	file.close();

	QMessageBox::information(this, "提示", "导出成功！");
	qDebug() << "CSV file saved successfully:" << csvFilePath;
}
