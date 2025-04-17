# 音乐播放器

## 1.项目概述

本项目是基于Qt框架开发的完整多媒体应用，包含用户注册，用户登录，歌单导入，历史记录等功能。c++作为后端逻辑语言，qml、Qt quick设计前端界面，sqlite为数据存储。

## 2.功能详解

### 2.1登录窗口

![image-20250406101443311](D:\July\BaiduSyncdisk\音乐播放器.assets\image-20250406101443311.png)

登录验证，去数据库匹配登录的用户名和密码，匹配成功返回正确，匹配失败返回错误。

```c++
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
```

自动登录，使用到ini。检测到ini中有数据，则不用进行二次登录。

```c++
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
```

### 2.2注册窗口

![image-20250406103031059](D:\July\BaiduSyncdisk\音乐播放器.assets\image-20250406103031059.png)

用户名非空检查以及唯一性检查。

```c++
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
```

### 2.3播放器核心

#### 播放模式切换

```c++
void PlayerWindow::on_comboBox_currentIndexChanged(int index)
{
    switch (index)
    {
    case 0:
        //列表
        playerList->setPlaybackMode(QMediaPlaylist::Loop);
        break;
    case 1:
        //随机
        playerList->setPlaybackMode(QMediaPlaylist::Random);
        break;
    case 2:
        //单曲
        playerList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        break;
    default:
        break;

    }
}
```

#### 歌单导入

```c++
void PlayerWindow::on_pushButton_musicDir_clicked()
{
    QString path=QFileDialog::getExistingDirectory(this,"选择歌曲目录","D:/Download/music");

    if(!path.isEmpty())
    {
        QDir dir(path,"*.mp3");
        if(dir.exists())
        {
            musicNames=dir.entryList(QDir::Files,QDir::Name);
            ui->listWidget->addItems(musicNames);
            for(auto name:musicNames)
            {
                playerList->addMedia(QUrl::fromLocalFile(path+"/"+name));
            }
            player->setPlaylist(playerList);
            playerList->setCurrentIndex(0);
            ui->label_name->setText(musicNames[0]);
        }
    }
}
```

#### 历史记录

结构体

```c++
struct songInfo {
    QString musicName;
    QString userName;
    QDateTime updateTime;
    // 重载<运算符用于set排序
    bool operator <(const songInfo &info) const {
        return musicName < info.musicName;
    }
};
```

播放记录插入数据库

```c++
bool DbManager::insertHistory(songInfo info)
{
    QString sql="insert into history(userName,musicName,updateTime)values(?,?,datetime('now','localtime'));";
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(0,info.userName);
    query.bindValue(1,info.musicName);
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
```

查询历史记录

```c++
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
```

## 3.技术点

### 1.信号与槽机制

滑动条跟随歌曲动，以及进度条拖动播放

```c++
 //关联信号与槽：player播放器 当播放歌曲的进度位置发生改变时，就会发出信号，同时发出当前播放位置在哪
connect(player,&QMediaPlayer::positionChanged,this,&PlayerWindow::slot_positionChanged);	

//进度条
    qint64 musicLength=player->duration();//毫秒为单位
    ui->horizontalSlider->setMaximum(musicLength);
    ui->horizontalSlider->setValue(position);
    //显示歌名
    int index=playerList->currentIndex();
    QString musicname=musicNames.at(index);
    ui->label_name->setText(musicname);
    //歌曲时长
    int len=musicLength/1000;
    int min=len/60;
    int sec=len%60;
    //实时歌曲时长
    int current_min=position/1000/60;
    int current_sec=position/1000%60;
    //                                                     宽度2位 10进制 不够补0
    QString time=QString("[%1:%2 %3:%4]").arg(current_min,2,10,QChar('0')).arg(current_sec,2,10,QChar('0')).arg(min,2,10,QChar('0')).arg(sec,2,10,QChar('0'));
    ui->label_time->setText(time);

//进度条拖动播放
void PlayerWindow::on_horizontalSlider_sliderMoved(int position)
{
    player->setPosition(position);
}
```

音量滑动条

```c++
void PlayerWindow::on_horizontalSlider_volume_sliderMoved(int position)
{
    player->setVolume(position);
}
//初始音量
    player->setVolume(ui->horizontalSlider_volume->value());

```

双击播放

```c++
void PlayerWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    //根据给我的行指针获取当前行号
    int index=ui->listWidget->row(item);
    //播放双击行的哥
    playerList->setCurrentIndex(index);
    // 直接播放，而不是调用 on_pushButton_play_clicked()
    player->play();
    //改变播放图标
    ui->pushButton_play->setIcon(QIcon(":icon/pause.png"));
    //加入历史记录
    dealHistory();
}
```

### 2.自定义信号使用

登录窗口：点击登录按钮时，向登录界面类发出一个自定义信号，带出输入框中的账号和密码，类做校验

注册窗口：点击注册按钮，向注册窗口类发出信号，发出 账号和密码，类做数据库表的插入。

```c++
    //Signal：login 0，register 1
    signal btnclicked(string name,string pass,int flag)
        //登录
        onClicked: {
                    console.log("login")
                    btnclicked(username.text,password.text,0)

                }
		//注册
		onClicked: {
                    console.log("register")
                    btnclicked(username.text,password.text,1)
                }
```

注册窗口成功后将账号密码发送至登录页面并显示账号密码

```c++
//信号
signals:
    void sendRegisterInfo(QString name,QString pass);
//通过自定义信号发送账号和密码
emit sendRegisterInfo(name,pass);
//关联自定义信号与槽
connect(rootObject,SIGNAL(registerbtnclicked(QString,QString)),this,SLOT(slot_recv_registerInfo(QString,QString)));

```

## 4.实现配置

​	INI（Initialization）:

​	是一种简单的配置文件格式，被广泛用于存储应用程序的配置信息

特点:	

​	使用[section]分配置区块

​	每个区块包含多个键值对

单例模式:

​	使用饿汉式初始化,封装数据库功能模块和人员表的操作，保证管理类只有一个，并方便窗口操作数据库（将数据库操作封装到单例模式类中，所有的窗口使用同一个数据库）。

容器QStringList:

​	 选择文件夹之后，提取文件夹下所有的文件保存到容器中。