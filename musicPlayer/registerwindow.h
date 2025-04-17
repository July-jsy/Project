#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QObject>
#include<QQmlApplicationEngine>
#include<QDebug>
class registerwindow : public QObject
{
    Q_OBJECT
public:
    explicit registerwindow(QObject *parent = nullptr);
private:
    QQmlApplicationEngine engine;
    QQmlApplicationEngine engineTip;
    QObject *rootObject;
public slots:
    void slot_recv_registerInfo(QString name,QString pass);
signals:
    void sendRegisterInfo(QString name,QString pass);
};

#endif // REGISTERWINDOW_H
