/********************************************************************************
** Form generated from reading UI file 'playwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYWINDOW_H
#define UI_PLAYWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QListWidget *listWidget;
    QComboBox *comboBox;
    QPushButton *pushButton_musicDir;
    QPushButton *pushButton_account;
    QListWidget *listWidget_history;
    QLabel *label_user;
    QLabel *label_history;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_pre;
    QPushButton *pushButton_play;
    QPushButton *pushButton_next;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_voice;
    QSlider *horizontalSlider_volume;
    QWidget *widget2;
    QVBoxLayout *verticalLayout;
    QLabel *label_time;
    QSlider *horizontalSlider;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1044, 637);
        MainWindow->setStyleSheet(QString::fromUtf8("#MainWindow\n"
"{\n"
"border-image: url(:/icon/bg.jpg);\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(140, 20, 531, 361));
        listWidget->setStyleSheet(QString::fromUtf8("background-color:rgba(50,50,50,50);\n"
"color:rgb(255,255,255);\n"
""));
        comboBox = new QComboBox(centralwidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(510, 520, 161, 25));
        pushButton_musicDir = new QPushButton(centralwidget);
        pushButton_musicDir->setObjectName(QString::fromUtf8("pushButton_musicDir"));
        pushButton_musicDir->setGeometry(QRect(10, 120, 101, 51));
        pushButton_account = new QPushButton(centralwidget);
        pushButton_account->setObjectName(QString::fromUtf8("pushButton_account"));
        pushButton_account->setGeometry(QRect(10, 200, 101, 51));
        listWidget_history = new QListWidget(centralwidget);
        listWidget_history->setObjectName(QString::fromUtf8("listWidget_history"));
        listWidget_history->setGeometry(QRect(700, 100, 331, 281));
        listWidget_history->setStyleSheet(QString::fromUtf8("background-color:rgba(50,50,50,50);\n"
"color:rgb(255,255,255);\n"
""));
        label_user = new QLabel(centralwidget);
        label_user->setObjectName(QString::fromUtf8("label_user"));
        label_user->setGeometry(QRect(10, 40, 100, 60));
        QFont font;
        font.setBold(true);
        font.setKerning(true);
        label_user->setFont(font);
        label_user->setMouseTracking(false);
        label_user->setLayoutDirection(Qt::LeftToRight);
        label_user->setAutoFillBackground(false);
        label_user->setAlignment(Qt::AlignCenter);
        label_history = new QLabel(centralwidget);
        label_history->setObjectName(QString::fromUtf8("label_history"));
        label_history->setGeometry(QRect(700, 60, 91, 31));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(140, 470, 301, 81));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_pre = new QPushButton(widget);
        pushButton_pre->setObjectName(QString::fromUtf8("pushButton_pre"));

        horizontalLayout->addWidget(pushButton_pre);

        pushButton_play = new QPushButton(widget);
        pushButton_play->setObjectName(QString::fromUtf8("pushButton_play"));

        horizontalLayout->addWidget(pushButton_play);

        pushButton_next = new QPushButton(widget);
        pushButton_next->setObjectName(QString::fromUtf8("pushButton_next"));

        horizontalLayout->addWidget(pushButton_next);

        widget1 = new QWidget(centralwidget);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(470, 490, 201, 24));
        horizontalLayout_2 = new QHBoxLayout(widget1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_voice = new QLabel(widget1);
        label_voice->setObjectName(QString::fromUtf8("label_voice"));

        horizontalLayout_2->addWidget(label_voice);

        horizontalSlider_volume = new QSlider(widget1);
        horizontalSlider_volume->setObjectName(QString::fromUtf8("horizontalSlider_volume"));
        horizontalSlider_volume->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(horizontalSlider_volume);

        widget2 = new QWidget(centralwidget);
        widget2->setObjectName(QString::fromUtf8("widget2"));
        widget2->setGeometry(QRect(140, 410, 531, 50));
        verticalLayout = new QVBoxLayout(widget2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_time = new QLabel(widget2);
        label_time->setObjectName(QString::fromUtf8("label_time"));

        verticalLayout->addWidget(label_time);

        horizontalSlider = new QSlider(widget2);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(horizontalSlider);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1044, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "\345\210\227\350\241\250\345\276\252\347\216\257", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "\351\232\217\346\234\272\346\222\255\346\224\276", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "\345\215\225\346\233\262\345\276\252\347\216\257", nullptr));

        pushButton_musicDir->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\205\245\346\255\214\345\215\225", nullptr));
        pushButton_account->setText(QCoreApplication::translate("MainWindow", "\345\210\207\346\215\242\350\264\246\345\217\267", nullptr));
        label_user->setText(QCoreApplication::translate("MainWindow", "\345\256\235\345\256\235", nullptr));
        label_history->setText(QCoreApplication::translate("MainWindow", "\345\216\206\345\217\262\350\256\260\345\275\225\357\274\232", nullptr));
        pushButton_pre->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_play->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_next->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        label_voice->setText(QCoreApplication::translate("MainWindow", "\351\237\263\351\207\217", nullptr));
        label_time->setText(QCoreApplication::translate("MainWindow", "\346\255\214\346\233\262\346\227\266\351\225\277", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYWINDOW_H
