#ifndef DBMANAGER_H
#define DBMANAGER_H
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlQuery>
#include<QSqlRecord>
#include<QDateTime>
#include<vector>
#include<QDebug>
using namespace std;
struct songInfo
{
    QString musicName;
    QString userName;
    int id;
    QDateTime updateTime;
    bool operator <(const songInfo &info)const
    {
        return musicName<info.musicName;
    }
};
class DbManager
{
    DbManager();
    DbManager(const DbManager&);
    static DbManager *dbptr;
    QSqlDatabase db;
    void createTable();
public:
    static DbManager *getDbPtr();
    bool insertHistory(songInfo info);
    //参数为引用类型
    void selectHistoryInfos(vector<songInfo> &vec,QString name);
    //register judge
    bool selectUsername(QString name);

    bool insertUser(QString name,QString pass);

    bool userLogin(QString name,QString pass);
    ~DbManager();
};

#endif // DBMANAGER_H
