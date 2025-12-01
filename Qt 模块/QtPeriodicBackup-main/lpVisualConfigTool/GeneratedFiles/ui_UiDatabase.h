/********************************************************************************
** Form generated from reading UI file 'UiDatabase.ui'
**
** Created by: Qt User Interface Compiler version 5.9.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UIDATABASE_H
#define UI_UIDATABASE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Database
{
public:
    QGridLayout *gridLayout;
    QLabel *lb_host_name;
    QLineEdit *lineEdit_hostName;
    QPushButton *btn_testLink;
    QLabel *lb_db_name;
    QLineEdit *lineEdit_dbName;
    QPushButton *btn_dbInit;
    QLabel *lb_db_strategy;
    QComboBox *comboBox_strategy;
    QLabel *lb_flaws_db;
    QSpinBox *spinBox_flaws;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *Database)
    {
        if (Database->objectName().isEmpty())
            Database->setObjectName(QStringLiteral("Database"));
        Database->resize(548, 408);
        gridLayout = new QGridLayout(Database);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lb_host_name = new QLabel(Database);
        lb_host_name->setObjectName(QStringLiteral("lb_host_name"));
        lb_host_name->setMinimumSize(QSize(108, 0));

        gridLayout->addWidget(lb_host_name, 0, 0, 1, 1);

        lineEdit_hostName = new QLineEdit(Database);
        lineEdit_hostName->setObjectName(QStringLiteral("lineEdit_hostName"));

        gridLayout->addWidget(lineEdit_hostName, 0, 1, 1, 1);

        btn_testLink = new QPushButton(Database);
        btn_testLink->setObjectName(QStringLiteral("btn_testLink"));

        gridLayout->addWidget(btn_testLink, 0, 2, 1, 1);

        lb_db_name = new QLabel(Database);
        lb_db_name->setObjectName(QStringLiteral("lb_db_name"));
        lb_db_name->setMinimumSize(QSize(108, 0));

        gridLayout->addWidget(lb_db_name, 1, 0, 1, 1);

        lineEdit_dbName = new QLineEdit(Database);
        lineEdit_dbName->setObjectName(QStringLiteral("lineEdit_dbName"));

        gridLayout->addWidget(lineEdit_dbName, 1, 1, 1, 1);

        btn_dbInit = new QPushButton(Database);
        btn_dbInit->setObjectName(QStringLiteral("btn_dbInit"));

        gridLayout->addWidget(btn_dbInit, 1, 2, 1, 1);

        lb_db_strategy = new QLabel(Database);
        lb_db_strategy->setObjectName(QStringLiteral("lb_db_strategy"));
        lb_db_strategy->setMinimumSize(QSize(108, 0));

        gridLayout->addWidget(lb_db_strategy, 2, 0, 1, 1);

        comboBox_strategy = new QComboBox(Database);
        comboBox_strategy->setObjectName(QStringLiteral("comboBox_strategy"));

        gridLayout->addWidget(comboBox_strategy, 2, 1, 1, 1);

        lb_flaws_db = new QLabel(Database);
        lb_flaws_db->setObjectName(QStringLiteral("lb_flaws_db"));
        lb_flaws_db->setMinimumSize(QSize(108, 0));

        gridLayout->addWidget(lb_flaws_db, 3, 0, 1, 1);

        spinBox_flaws = new QSpinBox(Database);
        spinBox_flaws->setObjectName(QStringLiteral("spinBox_flaws"));
        spinBox_flaws->setMinimum(1);
        spinBox_flaws->setMaximum(99999);

        gridLayout->addWidget(spinBox_flaws, 3, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 257, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 4, 0, 1, 1);


        retranslateUi(Database);

        QMetaObject::connectSlotsByName(Database);
    } // setupUi

    void retranslateUi(QWidget *Database)
    {
        Database->setWindowTitle(QApplication::translate("Database", "Form", Q_NULLPTR));
        lb_host_name->setText(QApplication::translate("Database", "\344\270\273\346\234\272\345\220\215\346\210\226IP\345\234\260\345\235\200", Q_NULLPTR));
        btn_testLink->setText(QApplication::translate("Database", "\346\265\213\350\257\225\350\277\236\346\216\245", Q_NULLPTR));
        lb_db_name->setText(QApplication::translate("Database", "\344\270\273\345\272\223\345\220\215\347\247\260", Q_NULLPTR));
        btn_dbInit->setText(QApplication::translate("Database", "\344\270\273\345\272\223\345\210\235\345\247\213\345\214\226", Q_NULLPTR));
        lb_db_strategy->setText(QApplication::translate("Database", "\345\210\206\345\272\223\347\255\226\347\225\245", Q_NULLPTR));
        lb_flaws_db->setText(QApplication::translate("Database", "\346\214\211\347\274\272\351\231\267\351\207\217\345\210\206\345\272\223\357\274\210\344\270\207\357\274\211", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Database: public Ui_Database {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UIDATABASE_H
