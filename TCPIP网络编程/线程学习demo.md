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
	//QFile file("W:/data.txt");
	//if (!file.open(QIODevice::Text | QIODevice::ReadOnly))
	//{
	//	return;
	//}

	//QTextStream in(&file);
	//while (!in.atEnd())
	//{
	//	QString line = in.readLine();
	//	m_textEdit->append(line);
	//}

	QFile file("W:/qt/Docs/Qt-5.9.9/qtgui/qtgui.index");
	if (!file.open(QIODevice::Text | QIODevice::ReadOnly))
	{
		return;
	}

	QTextStream in(&file);
	while (!in.atEnd())
	{
		QString line = in.readLine();
		//此时会崩溃
		//m_textEdit->append(line);
		//Qt 中一个线程里不能直接调用另一个线程的对象的函数，解决这个问题很简单，把 textEdit->append(line) 替换为 QMetaObject::invokeMethod(textEdit, "append", Q_ARG(QString, line)) 即可，想要知道为什么，请参考 线程一调用线程二中函数的正确姿势。
		QMetaObject::invokeMethod(m_textEdit, "append", Q_ARG(QString, line));
		//为了减少 UI 线程更新界面的频率，读取一行后暂停 1ms，就能看到内容不停的被添加到 text edit 中，证明了读取文件的线程没有阻塞 UI 线程
		QThread::msleep(1);
	}
}


**重用线程**
线程结束运行后仍然可以再次调用 start() 重新启动。使用这个特性，可以重复利用线程执行任务，而不是每次都创建一个新的线程，创建线程需要和操作系统打交道，是很消耗资源的操作，所以能够重用就尽量重用，Qt 提供了线程池 QThreadPool 就是为了重复利用线程，避免大量的创建线程，提高程序的效率。

**总结**
本节使用简单的例子介绍了继承 QThread 实现多线程，在新线程中执行耗时任务，强调不要随意使用 terminate() 结束线程并给出了结束线程的简单方法，最后提示为了提高程序效率，应尽量的重复利用线程，避免大量创建新线程浪费资源。
