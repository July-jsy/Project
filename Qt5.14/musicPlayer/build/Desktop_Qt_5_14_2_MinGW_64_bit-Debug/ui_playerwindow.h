/********************************************************************************
** Form generated from reading UI file 'playerwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYERWINDOW_H
#define UI_PLAYERWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
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

class Ui_PlayerWindow
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
    QLabel *label_name;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_pre;
    QPushButton *pushButton_play;
    QPushButton *pushButton_next;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_voice;
    QSlider *horizontalSlider_volume;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout;
    QLabel *label_time;
    QSlider *horizontalSlider;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *PlayerWindow)
    {
        if (PlayerWindow->objectName().isEmpty())
            PlayerWindow->setObjectName(QString::fromUtf8("PlayerWindow"));
        PlayerWindow->resize(1044, 637);
        PlayerWindow->setStyleSheet(QString::fromUtf8("#PlayerWindow\n"
"{\n"
"border-image: url(:/icon/bg.jpg);\n"
"}"));
        centralwidget = new QWidget(PlayerWindow);
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
        comboBox->setGeometry(QRect(510, 540, 161, 25));
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
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(14);
        font.setBold(false);
        font.setKerning(true);
        label_user->setFont(font);
        label_user->setMouseTracking(false);
        label_user->setLayoutDirection(Qt::LeftToRight);
        label_user->setAutoFillBackground(false);
        label_user->setAlignment(Qt::AlignCenter);
        label_history = new QLabel(centralwidget);
        label_history->setObjectName(QString::fromUtf8("label_history"));
        label_history->setGeometry(QRect(700, 60, 91, 31));
        label_history->setStyleSheet(QString::fromUtf8("color: rgb(170, 255, 0);"));
        label_name = new QLabel(centralwidget);
        label_name->setObjectName(QString::fromUtf8("label_name"));
        label_name->setGeometry(QRect(140, 390, 531, 19));
        label_name->setStyleSheet(QString::fromUtf8("color: rgb(170, 255, 0);"));
        label_name->setAlignment(Qt::AlignCenter);
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(140, 490, 301, 81));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_pre = new QPushButton(layoutWidget);
        pushButton_pre->setObjectName(QString::fromUtf8("pushButton_pre"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/previous.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_pre->setIcon(icon);
        pushButton_pre->setIconSize(QSize(60, 60));

        horizontalLayout->addWidget(pushButton_pre);

        pushButton_play = new QPushButton(layoutWidget);
        pushButton_play->setObjectName(QString::fromUtf8("pushButton_play"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_play->setIcon(icon1);
        pushButton_play->setIconSize(QSize(60, 60));

        horizontalLayout->addWidget(pushButton_play);

        pushButton_next = new QPushButton(layoutWidget);
        pushButton_next->setObjectName(QString::fromUtf8("pushButton_next"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icon/next.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_next->setIcon(icon2);
        pushButton_next->setIconSize(QSize(60, 60));

        horizontalLayout->addWidget(pushButton_next);

        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(470, 510, 201, 24));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_voice = new QLabel(layoutWidget1);
        label_voice->setObjectName(QString::fromUtf8("label_voice"));

        horizontalLayout_2->addWidget(label_voice);

        horizontalSlider_volume = new QSlider(layoutWidget1);
        horizontalSlider_volume->setObjectName(QString::fromUtf8("horizontalSlider_volume"));
        horizontalSlider_volume->setMinimum(0);
        horizontalSlider_volume->setValue(30);
        horizontalSlider_volume->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(horizontalSlider_volume);

        layoutWidget2 = new QWidget(centralwidget);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(140, 430, 531, 50));
        verticalLayout = new QVBoxLayout(layoutWidget2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_time = new QLabel(layoutWidget2);
        label_time->setObjectName(QString::fromUtf8("label_time"));
        label_time->setStyleSheet(QString::fromUtf8("color: rgb(170, 255, 0);"));
        label_time->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(label_time);

        horizontalSlider = new QSlider(layoutWidget2);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(horizontalSlider);

        PlayerWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(PlayerWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1044, 25));
        PlayerWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(PlayerWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        PlayerWindow->setStatusBar(statusbar);

        retranslateUi(PlayerWindow);

        QMetaObject::connectSlotsByName(PlayerWindow);
    } // setupUi

    void retranslateUi(QMainWindow *PlayerWindow)
    {
        PlayerWindow->setWindowTitle(QCoreApplication::translate("PlayerWindow", "MainWindow", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("PlayerWindow", "\345\210\227\350\241\250\345\276\252\347\216\257", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("PlayerWindow", "\351\232\217\346\234\272\346\222\255\346\224\276", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("PlayerWindow", "\345\215\225\346\233\262\345\276\252\347\216\257", nullptr));

        pushButton_musicDir->setText(QCoreApplication::translate("PlayerWindow", "\345\257\274\345\205\245\346\255\214\345\215\225", nullptr));
        pushButton_account->setText(QCoreApplication::translate("PlayerWindow", "\345\210\207\346\215\242\350\264\246\345\217\267", nullptr));
        label_user->setText(QCoreApplication::translate("PlayerWindow", "\345\256\235\345\256\235", nullptr));
        label_history->setText(QCoreApplication::translate("PlayerWindow", "\345\216\206\345\217\262\350\256\260\345\275\225\357\274\232", nullptr));
        label_name->setText(QCoreApplication::translate("PlayerWindow", "\351\237\263\344\271\220", nullptr));
        pushButton_pre->setText(QString());
        pushButton_play->setText(QString());
        pushButton_next->setText(QString());
        label_voice->setText(QCoreApplication::translate("PlayerWindow", "\351\237\263\351\207\217", nullptr));
        label_time->setText(QCoreApplication::translate("PlayerWindow", "\346\255\214\346\233\262\346\227\266\351\225\277", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlayerWindow: public Ui_PlayerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYERWINDOW_H
