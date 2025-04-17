#include "dbmanager.h"


DbManager *DbManager::dbFace=nullptr;

DbManager::DbManager()
{
    //加载数据库驱动
    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("face.db");//构建目录下
    db.open();

    //创建人员表
    /*
     * 表明 user
     * 字段： id       整型  主键 自增
     *      name      字符串 用户名
     *    startTime   datetime 开始考试的时间
     *   endTime      datetime 结束考试的时间
     * */
    QString sql = "create table if not exists user ( "
                  "id integer primary key autoincrement,"
                  "name varchar(20),"
                  "startTime datetime,"
                  "endTime datetime);";

    QSqlQuery query;
    bool ok = query.exec(sql);
    if(ok)
        qDebug()<<"成功";
    else
        qDebug()<<"失败";

}


DbManager *DbManager::getFace()
{
    if(dbFace==nullptr)
    {
        dbFace=new DbManager;
    }
    return dbFace;
}

bool DbManager::insertUser(QString name)
{
    QString sql="insert into user(name,startTime) values (?,datetime('now','localtime'));";
    QSqlQuery query;
    query.prepare(sql);
    //0:第一个问号
    query.bindValue(0,name);
    bool ok=query.exec();
    if(ok)
        qDebug()<<"insert sus";
    else
        qDebug()<<"insert failed";
    return ok;
}



int DbManager::getUserId()
{
    QString sql="select last_insert_rowid();";
    QSqlQuery query;
    query.exec(sql);
    int id=-1;
    //提取返回的结果集中的整数id
    //query.next()  过来去结果集  箭头所指的行有数据 next函数的返回值 true
    while(query.next())
    {
        id=query.record().value(0).toInt();
    }
    qDebug()<<"id"<<id;
    return id;
}



bool DbManager::updateEndTime(int id)
{
    QString sql = "update user set endTime = datetime('now', 'localtime') where id = ?;";
    QSqlQuery query;
    query.prepare(sql);
    bool ok=query.exec();
    if(ok)
        qDebug()<<"update sus";
    else
        qDebug()<<"update failed";
    return ok;
}



void DbManager::selectInfo(vector<UserData> &v)
{
    QString sql="select * from user;";
    QSqlQuery query;
    query.exec(sql);

    while (query.next())
    {
        UserData data;
        data.id=query.value(0).toInt();
        data.name=query.value(1).toString();
        data.start=query.value(2).toDateTime();
        data.end=query.value(3).toDateTime();

        v.push_back(data);

    }
    qDebug()<<"v.size"<<v.size();
}

