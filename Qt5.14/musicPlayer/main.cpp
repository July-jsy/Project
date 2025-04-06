#include "playerwindow.h"
#include"loginwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //更改启动窗口
    QSettings *set=new QSettings("user.ini",QSettings::IniFormat);
    QString userName=set->value("user/username").toString();
    QString passWord=set->value("user/password").toString();
    if(userName.isEmpty()&&passWord.isEmpty())
    {
        LoginWindow *w=new LoginWindow;
    }
    else
    {
        PlayerWindow *p=new PlayerWindow(userName);
        p->show();
    }
    //PlayerWindow w;
    //w.show();
    return a.exec();
}
