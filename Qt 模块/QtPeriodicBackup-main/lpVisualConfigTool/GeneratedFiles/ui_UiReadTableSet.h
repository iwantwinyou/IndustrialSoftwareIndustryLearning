/********************************************************************************
** Form generated from reading UI file 'UiReadTableSet.ui'
**
** Created by: Qt User Interface Compiler version 5.9.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UIREADTABLESET_H
#define UI_UIREADTABLESET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UiReadTableSet
{
public:
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_cancel;
    QPushButton *btn_confirm;

    void setupUi(QWidget *UiReadTableSet)
    {
        if (UiReadTableSet->objectName().isEmpty())
            UiReadTableSet->setObjectName(QStringLiteral("UiReadTableSet"));
        UiReadTableSet->resize(525, 280);
        gridLayout = new QGridLayout(UiReadTableSet);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tableWidget = new QTableWidget(UiReadTableSet);
        if (tableWidget->columnCount() < 5)
            tableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        gridLayout->addWidget(tableWidget, 0, 0, 1, 3);

        horizontalSpacer = new QSpacerItem(342, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        btn_cancel = new QPushButton(UiReadTableSet);
        btn_cancel->setObjectName(QStringLiteral("btn_cancel"));

        gridLayout->addWidget(btn_cancel, 1, 1, 1, 1);

        btn_confirm = new QPushButton(UiReadTableSet);
        btn_confirm->setObjectName(QStringLiteral("btn_confirm"));

        gridLayout->addWidget(btn_confirm, 1, 2, 1, 1);


        retranslateUi(UiReadTableSet);

        QMetaObject::connectSlotsByName(UiReadTableSet);
    } // setupUi

    void retranslateUi(QWidget *UiReadTableSet)
    {
        UiReadTableSet->setWindowTitle(QApplication::translate("UiReadTableSet", "\350\257\267\346\261\202\345\217\202\346\225\260\350\256\276\347\275\256", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("UiReadTableSet", "\345\220\215\347\247\260", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("UiReadTableSet", "\345\234\260\345\235\200", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("UiReadTableSet", "\345\255\227\346\225\260", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("UiReadTableSet", "\347\273\223\346\236\204\347\261\273\345\236\213", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("UiReadTableSet", "\350\257\264\346\230\216", Q_NULLPTR));
        btn_cancel->setText(QApplication::translate("UiReadTableSet", "\345\217\226\346\266\210", Q_NULLPTR));
        btn_confirm->setText(QApplication::translate("UiReadTableSet", "\347\241\256\345\256\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class UiReadTableSet: public Ui_UiReadTableSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UIREADTABLESET_H
