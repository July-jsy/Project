#include "playerwindow.h"
#include "ui_playerwindow.h"

PlayerWindow::PlayerWindow(QString name,QWidget *parent)
    : QMainWindow(parent),userName(name)
    , ui(new Ui::PlayerWindow)
{
    ui->setupUi(this);
    ui->label_user->setText(name);
    player=new QMediaPlayer(this);
    playerList=new QMediaPlaylist(this);
    playerList->setPlaybackMode(QMediaPlaylist::Loop);
    //关联信号与槽：player播放器 当播放歌曲的进度位置发生改变时，就会发出信号，同时发出当前播放位置在哪
    connect(player,&QMediaPlayer::positionChanged,this,&PlayerWindow::slot_positionChanged);
    //初始音量
    player->setVolume(ui->horizontalSlider_volume->value());

    //提取当前所有用户记录
    vector<songInfo> v;
    DbManager::getDbPtr()->selectHistoryInfos(v,userName);
    for(auto info:v)
    {
        historySet.insert(info);
        ui->listWidget_history->addItem(info.musicName);
    }
}

PlayerWindow::~PlayerWindow()
{
    delete ui;

}
//上一曲
void PlayerWindow::on_pushButton_pre_clicked()
{
    if (playerList->mediaCount() == 0) return; // 防止空列表
    playerList->previous();
    player->play();
    ui->pushButton_play->setIcon(QIcon(":icon/pause.png"));
    dealHistory();
    //循环模式
    // int currentIndex = playerList->currentIndex();//查询当前索引
    // int preIndex = (currentIndex - 1+playerList->mediaCount()) % playerList->mediaCount();
    // playerList->setCurrentIndex(preIndex);
    // ui->label_name->setText(musicNames[preIndex]);
    // player->play();
}

//播放
void PlayerWindow::on_pushButton_play_clicked()
{
    if(player->state()==QMediaPlayer::PlayingState)//函数的返回值，播放器的状态
    {
        player->pause();
        ui->pushButton_play->setIcon(QIcon(":icon/play.png"));
    }
    else //if(player->state()==QMediaPlayer::PausedState||player->state()==QMediaPlayer::StoppedState)
    {
        player->play();
        ui->pushButton_play->setIcon(QIcon(":icon/pause.png"));
    }
    dealHistory();


}

//下一曲
void PlayerWindow::on_pushButton_next_clicked()
{

    if (playerList->mediaCount() == 0) return; // 防止空列表
    playerList->next();
    player->play();
    ui->pushButton_play->setIcon(QIcon(":icon/pause.png"));
    dealHistory();

    //循环模式
    // int currentIndex=playerList->currentIndex();
    // int nextIndex = (currentIndex + 1) % playerList->mediaCount();

    //     playerList->setCurrentIndex(nextIndex);
    //     ui->label_name->setText(musicNames[nextIndex]);
    //     player->play();
}

//导入歌单
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
            // for(auto it=musicNames.begin();it!=musicNames.end();it++)
            // {
            //     playerList->addMedia(QUrl(path+"/"+(*it)));
            // }
            //qDebug() << "Current file path:" << path;
            for(auto name:musicNames)
            {
                // playerList->addMedia(QUrl::fromLocalFile(path + QDir::separator() + name));
                //qDebug() << "Current file path:" << path+"/"+name;
                playerList->addMedia(QUrl::fromLocalFile(path+"/"+name));
            }
            player->setPlaylist(playerList);
            playerList->setCurrentIndex(0);
            ui->label_name->setText(musicNames[0]);

        }
    }


}

//切换账号
void PlayerWindow::on_pushButton_account_clicked()
{
    this->close();
    LoginWindow *p=new LoginWindow;
}




//切换功能                                          参数：是信号发出来的，接受信号给的资源
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

void PlayerWindow::slot_positionChanged(qint64 position)
{
    //qDebug()<<position;
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
}

//进度条拖动播放
void PlayerWindow::on_horizontalSlider_sliderMoved(int position)
{
    player->setPosition(position);
}


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


void PlayerWindow::on_horizontalSlider_volume_sliderMoved(int position)
{
    player->setVolume(position);
}

void PlayerWindow::dealHistory()
{
    QString musicName=musicNames.at(playerList->currentIndex());
    //临时构建一个结构体
    songInfo info;
    info.musicName=musicName;
    info.userName=userName;
    if(historySet.count(info)==0)
    {
        bool ok=DbManager::getDbPtr()->insertHistory(info);
        if(ok)
        {
            ui->listWidget_history->addItem(musicName);
            historySet.insert(info);
        }
    }
}

