/********************************************************************************
** Form generated from reading UI file 'UiDiySet.ui'
**
** Created by: Qt User Interface Compiler version 5.9.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UIDIYSET_H
#define UI_UIDIYSET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_UiDiySet
{
public:
    QGridLayout *gridLayout;
    QLabel *lb_addr;
    QLabel *lb_addr_data;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QLabel *lb_cnt;
    QLabel *lb_cnt_data;
    QTableWidget *tab_diy;
    QTableWidget *tab_reg;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btn_cancel;
    QPushButton *btn_confirm;

    void setupUi(QDialog *UiDiySet)
    {
        if (UiDiySet->objectName().isEmpty())
            UiDiySet->setObjectName(QStringLiteral("UiDiySet"));
        UiDiySet->resize(553, 392);
        gridLayout = new QGridLayout(UiDiySet);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lb_addr = new QLabel(UiDiySet);
        lb_addr->setObjectName(QStringLiteral("lb_addr"));

        gridLayout->addWidget(lb_addr, 0, 0, 2, 2);

        lb_addr_data = new QLabel(UiDiySet);
        lb_addr_data->setObjectName(QStringLiteral("lb_addr_data"));
        lb_addr_data->setMaximumSize(QSize(100, 100));

        gridLayout->addWidget(lb_addr_data, 0, 2, 2, 2);

        horizontalSpacer = new QSpacerItem(424, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 4, 1, 3);

        horizontalSpacer_2 = new QSpacerItem(442, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 3, 2, 4);

        lb_cnt = new QLabel(UiDiySet);
        lb_cnt->setObjectName(QStringLiteral("lb_cnt"));

        gridLayout->addWidget(lb_cnt, 2, 0, 1, 1);

        lb_cnt_data = new QLabel(UiDiySet);
        lb_cnt_data->setObjectName(QStringLiteral("lb_cnt_data"));

        gridLayout->addWidget(lb_cnt_data, 2, 1, 1, 2);

        tab_diy = new QTableWidget(UiDiySet);
        if (tab_diy->columnCount() < 5)
            tab_diy->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tab_diy->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tab_diy->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tab_diy->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tab_diy->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tab_diy->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tab_diy->setObjectName(QStringLiteral("tab_diy"));

        gridLayout->addWidget(tab_diy, 3, 0, 1, 7);

        tab_reg = new QTableWidget(UiDiySet);
        if (tab_reg->columnCount() < 5)
            tab_reg->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tab_reg->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tab_reg->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tab_reg->setHorizontalHeaderItem(2, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tab_reg->setHorizontalHeaderItem(3, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tab_reg->setHorizontalHeaderItem(4, __qtablewidgetitem9);
        tab_reg->setObjectName(QStringLiteral("tab_reg"));

        gridLayout->addWidget(tab_reg, 4, 0, 1, 7);

        horizontalSpacer_3 = new QSpacerItem(356, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 5, 0, 1, 5);

        btn_cancel = new QPushButton(UiDiySet);
        btn_cancel->setObjectName(QStringLiteral("btn_cancel"));
        btn_cancel->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(btn_cancel, 5, 5, 1, 1);

        btn_confirm = new QPushButton(UiDiySet);
        btn_confirm->setObjectName(QStringLiteral("btn_confirm"));
        btn_confirm->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(btn_confirm, 5, 6, 1, 1);


        retranslateUi(UiDiySet);

        QMetaObject::connectSlotsByName(UiDiySet);
    } // setupUi

    void retranslateUi(QDialog *UiDiySet)
    {
        UiDiySet->setWindowTitle(QApplication::translate("UiDiySet", "\345\217\202\346\225\260\350\256\276\347\275\256", Q_NULLPTR));
        lb_addr->setText(QApplication::translate("UiDiySet", "\350\265\267\345\247\213\345\234\260\345\235\200\357\274\232", Q_NULLPTR));
        lb_addr_data->setText(QApplication::translate("UiDiySet", "test1", Q_NULLPTR));
        lb_cnt->setText(QApplication::translate("UiDiySet", "\346\200\273\345\255\227\346\225\260\357\274\232", Q_NULLPTR));
        lb_cnt_data->setText(QApplication::translate("UiDiySet", "test2", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tab_diy->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("UiDiySet", "\345\234\260\345\235\200", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tab_diy->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("UiDiySet", "key", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tab_diy->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("UiDiySet", "\345\255\227\346\225\260", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tab_diy->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("UiDiySet", "\346\225\260\346\215\256\347\261\273\345\236\213", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tab_diy->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("UiDiySet", "\350\257\264\346\230\216", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = tab_reg->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QApplication::translate("UiDiySet", "\345\234\260\345\235\200", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = tab_reg->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QApplication::translate("UiDiySet", "true_value", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem7 = tab_reg->horizontalHeaderItem(2);
        ___qtablewidgetitem7->setText(QApplication::translate("UiDiySet", "true_alias", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem8 = tab_reg->horizontalHeaderItem(3);
        ___qtablewidgetitem8->setText(QApplication::translate("UiDiySet", "false_value", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem9 = tab_reg->horizontalHeaderItem(4);
        ___qtablewidgetitem9->setText(QApplication::translate("UiDiySet", "false_alias", Q_NULLPTR));
        btn_cancel->setText(QApplication::translate("UiDiySet", "\345\217\226\346\266\210", Q_NULLPTR));
        btn_confirm->setText(QApplication::translate("UiDiySet", "\347\241\256\345\256\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class UiDiySet: public Ui_UiDiySet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UIDIYSET_H
