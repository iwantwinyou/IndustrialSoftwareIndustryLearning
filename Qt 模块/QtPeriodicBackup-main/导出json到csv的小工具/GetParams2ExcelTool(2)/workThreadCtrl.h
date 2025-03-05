#pragma once
#include <qobject.h>
#include <QThread>
#include <QList>
#include <QVariant>

struct ParamInfo {
	QString stationName;//工位名称
	QString ShowText; //参数文本显示
	QVariant ShowValue; //参数值
};
class workThreadCtrl :public QObject
{
	Q_OBJECT
public:
	workThreadCtrl(QObject *parent = nullptr);
	~workThreadCtrl();

	void initThread();
	void closeThread();
	QStringList getAllParamsFileNames()const;
	QList<ParamInfo>getparamsInfo(const QString &jsonFilePath);
	QMap<QString, QList<ParamInfo>> getAllParamsInfo(const QString &dirPath);
signals:

private slots:

private:
	QThread *m_this_thread_ptr{ nullptr };
};

