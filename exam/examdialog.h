#ifndef EXAMDIALOG_H
#define EXAMDIALOG_H

#include <QDialog>
#include<QMessageBox>
#include"mainwindow.h"

namespace Ui {
class ExamDialog;
}

class ExamDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExamDialog(QWidget *parent = nullptr);
    ~ExamDialog();
//声明一个信号    特点：只有声明，不需要实现
signals:
    void sendExamInfo(QString cource,int count);
private slots:
    void on_pushButton_clicked();

private:
    Ui::ExamDialog *ui;
};

#endif // EXAMDIALOG_H
