/********************************************************************************
** Form generated from reading UI file 'lpVisualFuncConfigTool.ui'
**
** Created by: Qt User Interface Compiler version 5.9.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LPVISUALFUNCCONFIGTOOL_H
#define UI_LPVISUALFUNCCONFIGTOOL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VisualFuncConfigWidget
{
public:
    QGridLayout *gridLayout;
    QLabel *lb_tips;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_apply;
    QTabWidget *tabWidget_config;
    QWidget *tab_db;
    QWidget *tab_plc;

    void setupUi(QWidget *VisualFuncConfigWidget)
    {
        if (VisualFuncConfigWidget->objectName().isEmpty())
            VisualFuncConfigWidget->setObjectName(QStringLiteral("VisualFuncConfigWidget"));
        VisualFuncConfigWidget->resize(687, 504);
        gridLayout = new QGridLayout(VisualFuncConfigWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lb_tips = new QLabel(VisualFuncConfigWidget);
        lb_tips->setObjectName(QStringLiteral("lb_tips"));

        gridLayout->addWidget(lb_tips, 1, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(464, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 1, 1, 1);

        btn_apply = new QPushButton(VisualFuncConfigWidget);
        btn_apply->setObjectName(QStringLiteral("btn_apply"));

        gridLayout->addWidget(btn_apply, 1, 2, 1, 1);

        tabWidget_config = new QTabWidget(VisualFuncConfigWidget);
        tabWidget_config->setObjectName(QStringLiteral("tabWidget_config"));
        tab_db = new QWidget();
        tab_db->setObjectName(QStringLiteral("tab_db"));
        tabWidget_config->addTab(tab_db, QString());
        tab_plc = new QWidget();
        tab_plc->setObjectName(QStringLiteral("tab_plc"));
        tabWidget_config->addTab(tab_plc, QString());

        gridLayout->addWidget(tabWidget_config, 0, 0, 1, 3);


        retranslateUi(VisualFuncConfigWidget);

        tabWidget_config->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(VisualFuncConfigWidget);
    } // setupUi

    void retranslateUi(QWidget *VisualFuncConfigWidget)
    {
        VisualFuncConfigWidget->setWindowTitle(QApplication::translate("VisualFuncConfigWidget", "lpVisualFuncConfigTool", Q_NULLPTR));
        lb_tips->setText(QApplication::translate("VisualFuncConfigWidget", "Note:", Q_NULLPTR));
        btn_apply->setText(QApplication::translate("VisualFuncConfigWidget", "\345\272\224\347\224\250", Q_NULLPTR));
        tabWidget_config->setTabText(tabWidget_config->indexOf(tab_db), QApplication::translate("VisualFuncConfigWidget", "\346\225\260\346\215\256\345\272\223\350\256\276\347\275\256", Q_NULLPTR));
        tabWidget_config->setTabText(tabWidget_config->indexOf(tab_plc), QApplication::translate("VisualFuncConfigWidget", "PLC\351\205\215\347\275\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class VisualFuncConfigWidget: public Ui_VisualFuncConfigWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LPVISUALFUNCCONFIGTOOL_H
