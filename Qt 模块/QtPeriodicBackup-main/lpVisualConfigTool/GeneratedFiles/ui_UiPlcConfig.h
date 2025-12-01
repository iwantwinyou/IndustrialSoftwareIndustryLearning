/********************************************************************************
** Form generated from reading UI file 'UiPlcConfig.ui'
**
** Created by: Qt User Interface Compiler version 5.9.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UIPLCCONFIG_H
#define UI_UIPLCCONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PLC
{
public:
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *lb_ip;
    QLineEdit *lineEdit_ip;
    QLabel *lb_port;
    QSpinBox *spinBox_port;
    QPushButton *btn_link;
    QLabel *lb_beat_warn;
    QSpinBox *spinBox_beat_warn;
    QCheckBox *checkBox_print;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QTableWidget *tableWidget_send;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QTableWidget *tableWidget_read;

    void setupUi(QWidget *PLC)
    {
        if (PLC->objectName().isEmpty())
            PLC->setObjectName(QStringLiteral("PLC"));
        PLC->resize(581, 431);
        gridLayout_4 = new QGridLayout(PLC);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        groupBox = new QGroupBox(PLC);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lb_ip = new QLabel(groupBox);
        lb_ip->setObjectName(QStringLiteral("lb_ip"));

        gridLayout->addWidget(lb_ip, 0, 0, 1, 1);

        lineEdit_ip = new QLineEdit(groupBox);
        lineEdit_ip->setObjectName(QStringLiteral("lineEdit_ip"));

        gridLayout->addWidget(lineEdit_ip, 0, 1, 1, 1);

        lb_port = new QLabel(groupBox);
        lb_port->setObjectName(QStringLiteral("lb_port"));

        gridLayout->addWidget(lb_port, 1, 0, 1, 1);

        spinBox_port = new QSpinBox(groupBox);
        spinBox_port->setObjectName(QStringLiteral("spinBox_port"));
        spinBox_port->setMinimum(1);
        spinBox_port->setMaximum(65534);
        spinBox_port->setValue(1025);

        gridLayout->addWidget(spinBox_port, 1, 1, 1, 1);

        btn_link = new QPushButton(groupBox);
        btn_link->setObjectName(QStringLiteral("btn_link"));

        gridLayout->addWidget(btn_link, 1, 2, 1, 1);

        lb_beat_warn = new QLabel(groupBox);
        lb_beat_warn->setObjectName(QStringLiteral("lb_beat_warn"));

        gridLayout->addWidget(lb_beat_warn, 2, 0, 1, 1);

        spinBox_beat_warn = new QSpinBox(groupBox);
        spinBox_beat_warn->setObjectName(QStringLiteral("spinBox_beat_warn"));

        gridLayout->addWidget(spinBox_beat_warn, 2, 1, 1, 1);

        checkBox_print = new QCheckBox(groupBox);
        checkBox_print->setObjectName(QStringLiteral("checkBox_print"));

        gridLayout->addWidget(checkBox_print, 2, 2, 1, 1);


        gridLayout_4->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(PLC);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        tableWidget_send = new QTableWidget(groupBox_2);
        if (tableWidget_send->columnCount() < 3)
            tableWidget_send->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_send->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_send->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_send->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget_send->setObjectName(QStringLiteral("tableWidget_send"));
        tableWidget_send->horizontalHeader()->setDefaultSectionSize(100);

        gridLayout_2->addWidget(tableWidget_send, 0, 0, 1, 1);


        gridLayout_4->addWidget(groupBox_2, 1, 0, 1, 1);

        groupBox_3 = new QGroupBox(PLC);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        tableWidget_read = new QTableWidget(groupBox_3);
        if (tableWidget_read->columnCount() < 5)
            tableWidget_read->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_read->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_read->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_read->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_read->setHorizontalHeaderItem(3, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_read->setHorizontalHeaderItem(4, __qtablewidgetitem7);
        tableWidget_read->setObjectName(QStringLiteral("tableWidget_read"));
        tableWidget_read->horizontalHeader()->setDefaultSectionSize(100);

        gridLayout_3->addWidget(tableWidget_read, 0, 0, 1, 1);


        gridLayout_4->addWidget(groupBox_3, 2, 0, 1, 1);


        retranslateUi(PLC);

        QMetaObject::connectSlotsByName(PLC);
    } // setupUi

    void retranslateUi(QWidget *PLC)
    {
        PLC->setWindowTitle(QApplication::translate("PLC", "Form", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("PLC", "\345\212\237\350\203\275\345\217\202\346\225\260", Q_NULLPTR));
        lb_ip->setText(QApplication::translate("PLC", "PLC IP", Q_NULLPTR));
        lb_port->setText(QApplication::translate("PLC", "PLC \347\253\257\345\217\243", Q_NULLPTR));
        btn_link->setText(QApplication::translate("PLC", "\346\265\213\350\257\225\350\277\236\346\216\245", Q_NULLPTR));
        lb_beat_warn->setText(QApplication::translate("PLC", "\345\277\203\350\267\263\346\212\245\350\255\246", Q_NULLPTR));
        checkBox_print->setText(QApplication::translate("PLC", "\346\211\223\345\215\260\351\200\232\344\277\241\350\257\246\346\203\205", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("PLC", "\345\215\217\350\256\256\345\217\202\346\225\260-\345\217\221\351\200\201", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_send->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("PLC", "\345\220\215\347\247\260", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_send->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("PLC", "\345\234\260\345\235\200", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_send->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("PLC", "\350\257\264\346\230\216", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("PLC", "\345\215\217\350\256\256\345\217\202\346\225\260-\350\257\267\346\261\202", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_read->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("PLC", "\345\220\215\347\247\260", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_read->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QApplication::translate("PLC", "\345\234\260\345\235\200", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_read->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QApplication::translate("PLC", "\345\255\227\346\225\260", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_read->horizontalHeaderItem(3);
        ___qtablewidgetitem6->setText(QApplication::translate("PLC", "\347\273\223\346\236\204\347\261\273\345\236\213", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_read->horizontalHeaderItem(4);
        ___qtablewidgetitem7->setText(QApplication::translate("PLC", "\350\257\264\346\230\216", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PLC: public Ui_PLC {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UIPLCCONFIG_H
