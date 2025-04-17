#include "registerwindow.h"
#include"dbmanager.h"
registerwindow::registerwindow(QObject *parent)
    : QObject{parent}
{
    engine.load(QUrl("qrc:/register.qml"));
    rootObject=engine.rootObjects().first();
    connect(rootObject,SIGNAL(registerbtnclicked(QString,QString)),this,SLOT(slot_recv_registerInfo(QString,QString)));
}

void registerwindow::slot_recv_registerInfo(QString name, QString pass)
{
    qDebug()<<"register:"<<name<<pass;
    engineTip.load(QUrl("qrc:/registerTip.qml"));

    QObject *root=engineTip.rootObjects().first();

    QObject *tip=root->findChild<QObject*>("tip");


    if(name.isEmpty()||pass.isEmpty())
    {
        if(tip)
        {
            tip->setProperty("text","账号或者密码不可为空");
        }
        return ;
    }
    if(DbManager::getDbPtr()->selectUsername(name))
    {
        //user already exists
        if(tip)
        {
            tip->setProperty("text","账号已存在");
        }
    }
    else
    {
        bool ok =DbManager::getDbPtr()->insertUser(name,pass);
        if(ok)//register sus
        {
            qDebug()<<"register sus";
            if(tip)
            {
                tip->setProperty("text","注册成功");
            }
            rootObject->setProperty("visible",false);
            emit sendRegisterInfo(name,pass);
        }
        else
        {
            //register failed
            qDebug()<<"register failed";
            if(tip)
            {
                tip->setProperty("text","注册失败");
            }
        }
    }
}
