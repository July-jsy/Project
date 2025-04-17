#include "dbmanager.h"

DbManager *DbManager::dbptr=new DbManager;
DbManager::DbManager()
{
    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("music.db");
    db.open();
    createTable();
}

DbManager::DbManager(const DbManager&)
{

}

void DbManager::createTable()
{
    QString sql="create table if not exists history(id integer primary key autoincrement,userName varchar(20),musicName varchar(50),updateTime datetime);";
    QSqlQuery query;
    bool ok=query.exec(sql);
    if(ok)
    {
        qDebug()<<" create history sus";
    }
    else
    {
        qDebug()<<"create history failed";
    }
    sql="create table if not exists user(id integer primary key autoincrement,userName varchar(20),passWord varchar(50));";
    ok=query.exec(sql);
    if(ok)
    {
        qDebug()<<" create user sus";
    }
    else
    {
        qDebug()<<"create user failed";
    }

}

DbManager *DbManager::getDbPtr()
{
    return dbptr;
}
//插入历史记录
bool DbManager::insertHistory(songInfo info)
{
    QString sql="insert into history(userName,musicName,updateTime)values(?,?,datetime('now','localtime'));";
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(0,info.userName);
    query.bindValue(1,info.musicName);
    //query.bindValue(2,info,updateTime);


    bool ok=query.exec();
    if(ok)
    {
        qDebug()<<"insert history sus";
    }
    else
    {
        qDebug()<<"insert history failed";
    }
    return ok;
}
#include<QSqlRecord>
void DbManager::selectHistoryInfos(vector<songInfo> &vec,QString name)
{
    QString sql="select * from history where userName=?;";
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(0,name);
    query.exec();
    while (query.next())
    {
        QString musicName=query.record().value(2).toString();
        //QString time=query.record().value(3).toDateTime().toString("yyyy-MM-dd hh:mm:ss");
        QDateTime time=query.record().value(3).toDateTime();


        songInfo info;
        info.musicName=musicName;
        info.updateTime=time;
        vec.push_back(info);
    }
}

bool DbManager::selectUsername(QString name)
{
    QString sql="select count(*) from user where userName=?;";
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(0,name);
    query.exec();
    int count=-1;
    while (query.next()) {
        count=query.record().value(0).toInt();
        qDebug()<<"count:"<<count;
        if(count>0)
        {
            return true;
        }
        else
        {
            return false;
        }

    }
    return true;
}

bool DbManager::insertUser(QString name, QString pass)
{
    QString sql="insert into user(userName,passWord)values(?,?);";
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(0,name);
    query.bindValue(1,pass);
    //query.bindValue(2,info,updateTime);


    bool ok=query.exec();
    if(ok)
    {
        qDebug()<<"insert user sus";
    }
    else
    {
        qDebug()<<"insert user failed";
    }

    return true;
}

bool DbManager::userLogin(QString name, QString pass)
{
    QString sql="select count(*) from user where userName=? and passWord=?;";
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(0,name);
    query.bindValue(1,pass);
    query.exec();
    int count=-1;

    while(query.next())
    {
        count=query.record().value(0).toInt();
        qDebug()<<"count:"<<count;
        if(count>0)
        {
            return true;
        }
        else
        {
            return false;
        }

    }
    return false;
}
DbManager::~DbManager()
{
    db.close();
}
