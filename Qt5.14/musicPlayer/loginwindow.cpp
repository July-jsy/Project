#include "loginwindow.h"
#include"registerwindow.h"
LoginWindow::LoginWindow(QObject *parent)
    : QObject{parent}
{
    engine.load(QUrl("qrc:/login.qml"));
    //配置信号与槽
    rootObject=engine.rootObjects().first();
    connect(rootObject,SIGNAL(btnclicked(QString ,QString,int)),this,SLOT(slot_btnclicked(QString,QString,int)));
}

void LoginWindow::slot_btnclicked(QString name, QString pass, int flag)
{
    qDebug()<<name<<pass<<flag;
    if(flag)
    {
        //register
        registerwindow *pr=new registerwindow;
        connect(pr,&registerwindow::sendRegisterInfo,this,&LoginWindow::slot_recvUserInfo);
    }
    else
    {
        bool ok=DbManager::getDbPtr()->userLogin(name,pass);
        if(ok)
        {
            PlayerWindow *p=new PlayerWindow(name);
            p->show();

            QSettings *set=new QSettings("user.ini",QSettings::IniFormat);
            //添加兩個鍵值對
            set->setValue("/user/username",name);
            set->setValue("/user/password",pass);
            rootObject->setProperty("visible",false);
        }
        else
        {
            qDebug()<<"login failed";
        }
    }
}

void LoginWindow::slot_recvUserInfo(QString name, QString pass)
{
    QObject *un=rootObject->findChild<QObject*>("username");
    un->setProperty("text",name);
    QObject *pw=rootObject->findChild<QObject*>("password");
    pw->setProperty("text",pass);
}
