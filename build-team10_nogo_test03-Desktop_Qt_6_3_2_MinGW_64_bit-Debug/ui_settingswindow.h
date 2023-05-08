/********************************************************************************
** Form generated from reading UI file 'settingswindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSWINDOW_H
#define UI_SETTINGSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label2;
    QLineEdit *ipEdit;
    QLineEdit *portEdit;
    QPushButton *reSetButton;
    QPushButton *reConnectButton;
    QLabel *connectLabel;
    QPushButton *beginButton;
    QComboBox *usercolorBox;
    QLabel *label4;
    QLabel *label3;
    QLineEdit *usernameEdit;
    QPushButton *setButton;
    QLabel *label_2;
    QPushButton *disconnectButton;
    QTextEdit *textEdit;
    QLineEdit *sendEdit;
    QPushButton *sendButton;
    QLabel *label_3;
    QLineEdit *timeEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SettingsWindow)
    {
        if (SettingsWindow->objectName().isEmpty())
            SettingsWindow->setObjectName(QString::fromUtf8("SettingsWindow"));
        SettingsWindow->resize(800, 600);
        centralwidget = new QWidget(SettingsWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 30, 69, 20));
        label2 = new QLabel(centralwidget);
        label2->setObjectName(QString::fromUtf8("label2"));
        label2->setGeometry(QRect(40, 70, 69, 20));
        ipEdit = new QLineEdit(centralwidget);
        ipEdit->setObjectName(QString::fromUtf8("ipEdit"));
        ipEdit->setGeometry(QRect(110, 30, 171, 27));
        portEdit = new QLineEdit(centralwidget);
        portEdit->setObjectName(QString::fromUtf8("portEdit"));
        portEdit->setGeometry(QRect(110, 70, 171, 27));
        reSetButton = new QPushButton(centralwidget);
        reSetButton->setObjectName(QString::fromUtf8("reSetButton"));
        reSetButton->setGeometry(QRect(110, 120, 92, 29));
        reConnectButton = new QPushButton(centralwidget);
        reConnectButton->setObjectName(QString::fromUtf8("reConnectButton"));
        reConnectButton->setGeometry(QRect(110, 170, 92, 29));
        connectLabel = new QLabel(centralwidget);
        connectLabel->setObjectName(QString::fromUtf8("connectLabel"));
        connectLabel->setGeometry(QRect(120, 230, 141, 20));
        beginButton = new QPushButton(centralwidget);
        beginButton->setObjectName(QString::fromUtf8("beginButton"));
        beginButton->setGeometry(QRect(400, 360, 92, 29));
        usercolorBox = new QComboBox(centralwidget);
        usercolorBox->addItem(QString());
        usercolorBox->addItem(QString());
        usercolorBox->setObjectName(QString::fromUtf8("usercolorBox"));
        usercolorBox->setGeometry(QRect(270, 300, 89, 28));
        label4 = new QLabel(centralwidget);
        label4->setObjectName(QString::fromUtf8("label4"));
        label4->setGeometry(QRect(270, 270, 91, 21));
        label3 = new QLabel(centralwidget);
        label3->setObjectName(QString::fromUtf8("label3"));
        label3->setGeometry(QRect(120, 270, 91, 21));
        usernameEdit = new QLineEdit(centralwidget);
        usernameEdit->setObjectName(QString::fromUtf8("usernameEdit"));
        usernameEdit->setGeometry(QRect(112, 300, 141, 27));
        setButton = new QPushButton(centralwidget);
        setButton->setObjectName(QString::fromUtf8("setButton"));
        setButton->setGeometry(QRect(400, 300, 92, 29));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 230, 69, 20));
        disconnectButton = new QPushButton(centralwidget);
        disconnectButton->setObjectName(QString::fromUtf8("disconnectButton"));
        disconnectButton->setGeometry(QRect(260, 230, 92, 29));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(530, 30, 231, 311));
        sendEdit = new QLineEdit(centralwidget);
        sendEdit->setObjectName(QString::fromUtf8("sendEdit"));
        sendEdit->setGeometry(QRect(530, 350, 221, 27));
        sendButton = new QPushButton(centralwidget);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        sendButton->setGeometry(QRect(650, 390, 92, 29));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(190, 360, 69, 20));
        timeEdit = new QLineEdit(centralwidget);
        timeEdit->setObjectName(QString::fromUtf8("timeEdit"));
        timeEdit->setGeometry(QRect(260, 360, 113, 27));
        SettingsWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SettingsWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        SettingsWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(SettingsWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        SettingsWindow->setStatusBar(statusbar);

        retranslateUi(SettingsWindow);

        QMetaObject::connectSlotsByName(SettingsWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SettingsWindow)
    {
        SettingsWindow->setWindowTitle(QCoreApplication::translate("SettingsWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("SettingsWindow", "IP:", nullptr));
        label2->setText(QCoreApplication::translate("SettingsWindow", "PORT:", nullptr));
        reSetButton->setText(QCoreApplication::translate("SettingsWindow", "reset", nullptr));
        reConnectButton->setText(QCoreApplication::translate("SettingsWindow", "reconnect", nullptr));
        connectLabel->setText(QCoreApplication::translate("SettingsWindow", "connect   fail", nullptr));
        beginButton->setText(QCoreApplication::translate("SettingsWindow", "begin", nullptr));
        usercolorBox->setItemText(0, QCoreApplication::translate("SettingsWindow", "b", "b"));
        usercolorBox->setItemText(1, QCoreApplication::translate("SettingsWindow", "w", "w"));

        label4->setText(QCoreApplication::translate("SettingsWindow", "your color", nullptr));
        label3->setText(QCoreApplication::translate("SettingsWindow", "username", nullptr));
        setButton->setText(QCoreApplication::translate("SettingsWindow", "set", nullptr));
        label_2->setText(QCoreApplication::translate("SettingsWindow", "\345\256\242\346\210\267\347\253\257\357\274\232", nullptr));
        disconnectButton->setText(QCoreApplication::translate("SettingsWindow", "disconnect", nullptr));
        sendButton->setText(QCoreApplication::translate("SettingsWindow", "send", nullptr));
        label_3->setText(QCoreApplication::translate("SettingsWindow", "set time", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingsWindow: public Ui_SettingsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSWINDOW_H
