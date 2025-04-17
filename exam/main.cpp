#include "mainwindow.h"

#include <QApplication>

#include"examdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    ExamDialog w;
    w.show();
    return a.exec();
}
