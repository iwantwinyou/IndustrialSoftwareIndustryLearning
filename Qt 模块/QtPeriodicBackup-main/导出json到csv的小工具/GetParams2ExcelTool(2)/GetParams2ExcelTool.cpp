#include "GetParams2ExcelTool.h"
#include <QDir>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QtConCurrent>
#pragma execution_character_set("utf-8")

GetParams2ExcelTool::GetParams2ExcelTool(QWidget *parent)
	: QWidget(parent)
{
	qDebug() << "V1.0.1.0" << __FUNCTION__;
	ui.setupUi(this);
	m_work_thread_ptr = new workThreadCtrl(this);
	QString path = qApp->applicationDirPath() + "//lpIPUConfig//detectParam";
	m_allParamsInfoMap = m_work_thread_ptr->getAllParamsInfo(path);
	connect(ui.pushButton, &QPushButton::clicked, this, &GetParams2ExcelTool::onSaveData2Csv);
	connect(this, &GetParams2ExcelTool::sgExportFinished, this,&GetParams2ExcelTool::onExportFinished);
}

void GetParams2ExcelTool::onSaveData2Csv()
{
	QString csvFilePath = QFileDialog::getSaveFileName(this, tr("保存CSV文件"), "", tr("CSV文件(*.csv);;所有文件(*.*)"));
	if (csvFilePath.isEmpty()) {
		emit sgExportFinished(false);
		return;
	}
	QtConcurrent::run([this, csvFilePath]() {
		QFile file(csvFilePath);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
			qWarning() << "Failed to open CSV file for writing:" << csvFilePath;
			emit sgExportFinished(false);
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
		emit sgExportFinished(true);
		});
}

void GetParams2ExcelTool::onExportFinished(bool success)
{
	if (success) {
		QMessageBox::information(this, "提示", "导出成功！");
		qDebug() << "CSV file saved successfully.";
	}
	else {
		QMessageBox::warning(this, "提示", "导出失败！");
		qDebug() << "Failed to save CSV file.";
	}
}
