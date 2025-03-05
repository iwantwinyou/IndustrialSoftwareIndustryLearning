#include "workThreadCtrl.h"
#include<QApplication>
#include <QDir>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>

workThreadCtrl::workThreadCtrl(QObject *parent /*= nullptr*/)
{
	m_this_thread_ptr = new QThread;
	this->moveToThread(m_this_thread_ptr);
	connect(m_this_thread_ptr, &QThread::finished, this, &workThreadCtrl::deleteLater);
	initThread();
}

workThreadCtrl::~workThreadCtrl()
{

}

void workThreadCtrl::initThread()
{
	if (m_this_thread_ptr) {
		m_this_thread_ptr->start();
		m_this_thread_ptr->setPriority(QThread::NormalPriority);
	}
}

void workThreadCtrl::closeThread()
{
	if (m_this_thread_ptr) {
		m_this_thread_ptr->quit();
		m_this_thread_ptr->deleteLater();
		m_this_thread_ptr = nullptr;
	}
}

QStringList workThreadCtrl::getAllParamsFileNames() const
{
	QStringList fileNameList;
	QString path = qApp->applicationDirPath() + "//lpIPUConfig//detectParam";
	QDir dir(path);
	if (!dir.exists()) {
		qWarning() << "dir is not exist!" << __FUNCTION__;
		return QStringList();
	}

	QFileInfoList file_lists = dir.entryInfoList(QDir::Files |QDir::NoDotAndDotDot);
	for (const auto&fileInfo : file_lists) {
		QString name = fileInfo.fileName();
		if (name.endsWith(".json")) {
			name.chop(5);
		}
		fileNameList.append(name);
	}	
	return fileNameList;
}

QList<ParamInfo> workThreadCtrl::getparamsInfo(const QString &jsonFilePath)
{
	QFile file(jsonFilePath);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qWarning() << "Failed to open file:" << jsonFilePath;
		return QList<ParamInfo>();
	}

	QByteArray jsonData = file.readAll();
	QJsonParseError parseError;
	QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
	if (parseError.error != QJsonParseError::NoError) {
		qWarning() << "Failed to parse Json!" << parseError.errorString();
		file.close();
		return QList<ParamInfo>();
	}

	QJsonObject jsonObj = jsonDoc.object();
	QList<ParamInfo> paramsInfoList;

	for (const QString &key : jsonObj.keys()) {
		if (key.startsWith("station")) {
			QJsonObject stationObj = jsonObj.value(key).toObject();
			QString stationName = stationObj.value("des").toString();
			QJsonObject flaw_paramObj = stationObj.value("flaw_param").toObject();
			QJsonArray param_array = flaw_paramObj.value("algo_array").toArray();
			for (const auto&algoArr : param_array) {
				//paramArray
				QJsonObject algoObj = algoArr.toObject();
				QJsonArray paramArray = algoObj.value("paramArray").toArray();
				for (const auto &paramVar : paramArray) {
					QJsonObject paramObj = paramVar.toObject();
					QString showText = paramObj.value("show").toString();
					QVariant value = paramObj.value("value").toVariant();
					paramsInfoList.append({ stationName,showText, value });
				}

			}
		}
	}
	return paramsInfoList;
}

QMap<QString, QList<ParamInfo>> workThreadCtrl::getAllParamsInfo(const QString &dirPath)
{
	QMap<QString, QList<ParamInfo>> allParamsInfo;
	QStringList fileNames = getAllParamsFileNames();
	for (const QString &fileName : fileNames) {
		QString filePath = dirPath + "/" + fileName + ".json";
		QList<ParamInfo> paramsInfoList = getparamsInfo(filePath);
		allParamsInfo[fileName] = paramsInfoList;
	}
	return allParamsInfo;
}
