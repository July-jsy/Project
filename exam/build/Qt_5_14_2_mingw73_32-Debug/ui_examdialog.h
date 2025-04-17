/********************************************************************************
** Form generated from reading UI file 'examdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXAMDIALOG_H
#define UI_EXAMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ExamDialog
{
public:
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QComboBox *comboBox;
    QPushButton *pushButton;

    void setupUi(QDialog *ExamDialog)
    {
        if (ExamDialog->objectName().isEmpty())
            ExamDialog->setObjectName(QString::fromUtf8("ExamDialog"));
        ExamDialog->resize(980, 609);
        label = new QLabel(ExamDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(260, 20, 461, 131));
        QFont font;
        font.setPointSize(72);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        lineEdit = new QLineEdit(ExamDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(370, 220, 251, 71));
        label_2 = new QLabel(ExamDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(380, 320, 71, 71));
        comboBox = new QComboBox(ExamDialog);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(470, 330, 141, 41));
        pushButton = new QPushButton(ExamDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(370, 440, 241, 111));
        QFont font1;
        font1.setPointSize(20);
        pushButton->setFont(font1);

        retranslateUi(ExamDialog);

        QMetaObject::connectSlotsByName(ExamDialog);
    } // setupUi

    void retranslateUi(QDialog *ExamDialog)
    {
        ExamDialog->setWindowTitle(QCoreApplication::translate("ExamDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("ExamDialog", "\350\200\203\345\234\272", nullptr));
        lineEdit->setText(QString());
        lineEdit->setPlaceholderText(QCoreApplication::translate("ExamDialog", "\350\257\267\350\276\223\345\205\245\350\200\203\350\257\225\347\247\221\347\233\256\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("ExamDialog", "\350\200\203\350\257\225\344\272\272\346\225\260\357\274\232", nullptr));
        pushButton->setText(QCoreApplication::translate("ExamDialog", "\345\274\200\345\247\213\350\200\203\350\257\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ExamDialog: public Ui_ExamDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXAMDIALOG_H
