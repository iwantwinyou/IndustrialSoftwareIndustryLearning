@@@QtThreadTest.h
//使用线程demo
//来源于  https://mp.weixin.qq.com/s/DiNiU85f68UqYFp32_tGdA
//date: 2024/5/22
#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtThreadTest.h"
#include <QThread>

class QTextEdit;
class ReadingThread :public QThread
{
public:
	ReadingThread(QTextEdit *textEdit,QObject *parent =nullptr);
	virtual ~ReadingThread();

	void stop();
protected:
	void run()override;
private:
	QTextEdit *m_textEdit;

	bool m_stopped;//线程结束标志
};

class QtThreadTest : public QWidget
{
	Q_OBJECT

public:
	QtThreadTest(QWidget *parent = Q_NULLPTR);

private:
	//Ui::QtThreadTestClass ui;

	ReadingThread *m_readingThread;
};

####QtThreadTest.cpp
#include "QtThreadTest.h"
#include <QFile>
#include <QTextStream>
#include <QTextEdit>
#include <QtWidgets>
QtThreadTest::QtThreadTest(QWidget *parent)
	: QWidget(parent)
{
	//ui.setupUi(this);

	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	mainLayout->setSpacing(6);
	mainLayout->setMargin(6);

	this->setLayout(mainLayout);

	QTextEdit *textEdit = new QTextEdit(this);
	mainLayout->addWidget(textEdit);


	QPushButton *startBtn = new QPushButton(QStringLiteral("开始启动"),this);
	mainLayout->addWidget(startBtn);

	QPushButton *finishBtn = new QPushButton(QStringLiteral("结束"), this);
	mainLayout->addWidget(finishBtn);
	m_readingThread = new ReadingThread(textEdit, this);

	connect(startBtn, &QPushButton::clicked, this, [this]() {
		if (!m_readingThread->isRunning())
		{
			//线程没有运行才启动
			m_readingThread->start();
		}
		else
		{
			qDebug() << "thread is running!!!";
		}
	});

	//方案1：
	//connect(finishBtn,&QPushButton::clicked,this,[this](){
	//	m_readingThread->terminate(); //使用 terminate() 结束线程是非常危险的,它可能在 run() 中的任意地方结束，可能导致死锁、资源没有释放等
	//
	//	m_readingThread->wait(); //等待线程真正的结束执行
	//});

	//方案2：（更好）推荐结束线程的方法是：定义一个变量，用它来控制 run() 中循环的结束。
	connect(finishBtn, &QPushButton::clicked, this, [this]() {
		m_readingThread->stop(); // 提示结束线程执行

		m_readingThread->wait(); //等待线程真正的结束执行
	});
	
	connect(m_readingThread, &QThread::finished, []() {
		qDebug() << "thread finish!!!";
	});

}


ReadingThread::ReadingThread(QTextEdit *textEdit, QObject *parent /*=nullptr*/)
	:QThread(parent),m_textEdit(textEdit)
{

}

ReadingThread::~ReadingThread()
{

}

void ReadingThread::stop()
{
	m_stopped = true;
}

void ReadingThread::run()
{
	QFile file("W:/data.txt");
	if (!file.open(QIODevice::Text | QIODevice::ReadOnly))
	{
		return;
	}

	QTextStream in(&file);
	while (!in.atEnd())
	{
		QString line = in.readLine();
		m_textEdit->append(line);
	}
}

