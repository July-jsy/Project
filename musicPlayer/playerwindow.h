#ifndef PLAYERWINDOW_H
#define PLAYERWINDOW_H

#include <QMainWindow>
#include<QDir>
#include<QFileDialog>
#include<QString>
#include<QMediaPlayer>//播放器对象
#include<QMediaPlaylist>//音乐播放列表
#include<QListWidgetItem>//列表每一行的对象类型
#include "ui_playerwindow.h"
//使用set容器保存历史记录

#include<set>
#include"loginwindow.h"
#include"dbmanager.h"
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class PlayerWindow;
}
QT_END_NAMESPACE

class PlayerWindow : public QMainWindow
{
    Q_OBJECT

public:
    PlayerWindow(QString name,QWidget *parent = nullptr);
    ~PlayerWindow();

private slots:
    void on_pushButton_pre_clicked();

    void on_pushButton_play_clicked();

    void on_pushButton_next_clicked();

    void on_pushButton_musicDir_clicked();

    void on_pushButton_account_clicked();


    void on_comboBox_currentIndexChanged(int index);

    void slot_positionChanged(qint64 position);

    void on_horizontalSlider_sliderMoved(int position);

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_horizontalSlider_volume_sliderMoved(int position);

    void dealHistory();

private:
    Ui::PlayerWindow *ui;

    QMediaPlayer *player;

    QMediaPlaylist *playerList;

    int n=0;

    QStringList musicNames;

    set<songInfo> historySet;

    QString userName;
};
#endif // PLAYERWINDOW_H
