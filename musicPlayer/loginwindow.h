#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QObject>
#include<QQmlApplicationEngine>
#include<QDebug>
#include"dbmanager.h"
#include"playerwindow.h"
#include<QSettings>
class LoginWindow : public QObject
{
    Q_OBJECT
public:
    explicit LoginWindow(QObject *parent = nullptr);
private:
    QQmlApplicationEngine engine;

    //qml文件的根元素指针
    QObject *rootObject;
public slots:
    void slot_btnclicked(QString name,QString pass,int flag);

    void slot_recvUserInfo(QString name,QString pass);
signals:
};

#endif // LOGINWINDOW_H
