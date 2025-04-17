#ifndef DBMANAGER_H
#define DBMANAGER_H

#include<QSqlDatabase>
#include<QSqlQuery>
#include<QDebug>
#include<QSqlRecord>
#include<QDateTime>
#include<vector>
using namespace std;

struct UserData
{
    int id;
    QString name;
    QDateTime start;
    QDateTime end;
};
/*
 * 单例模式
 * 保证一个类只能创建一个实例化对象
 * 1.类外不能创建对象（构造和拷贝私有权限）
 * 2.私有权限的静态成员指针（指向唯一实例化对象）
 * 3.公有的   静态成员函数（返回 指向对象的指针）
 *
 *
 * */
class DbManager
{

    DbManager();
    DbManager(const DbManager &){}
    static DbManager *dbFace;
    QSqlDatabase db;
public:
    static DbManager *getFace();
    //插入用户，插入成功后
    bool insertUser(QString name);
    //获取用户的id
    int getUserId();
    //离开考试时，更新离开的时间
    bool updateEndTime(int id);
    //提取数据库表中所有的数据，保存到容器中
    void selectInfo(vector<UserData> &v);


};

#endif // DBMANAGER_H
