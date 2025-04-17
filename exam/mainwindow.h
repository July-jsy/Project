#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDebug>
#include<QLabel>
#include<opencv2/opencv.hpp>
#include<opencv2/face.hpp>
#include<QTimerEvent>
#include<vector>
#include<QFile>
#include<QFileDialog>
#include<QMessageBox>
#include<cstdlib>
#include<ctime>
#include"excelhelper.h"
#include"dbmanager.h"


using namespace cv;
using namespace cv::face;
using namespace std;


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


struct PointAndName
{
    int rand_x;
    int rand_y;
    QString name;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //重写父类的虚函数
    void timerEvent(QTimerEvent *event);
    //显示图像
    void showImg();

    bool changeLabelImg(Mat face,PointAndName &v,int flag);

public slots:
    void recvExamInfo(QString cource,int count);

private slots:
    void on_pushButton_choice_clicked();

    void on_pushButton_leave_clicked();

    void on_pushButton_derive_clicked();

private:
    Ui::MainWindow *ui;
    CascadeClassifier classifier;//级联分类器，查找人脸
    vector<Rect> findFace;//存储  级联分类器找到的人脸矩形位置的容器
    Mat frame;//提取到的一帧图像
    VideoCapture vc;

    //人脸识别器对象
    Ptr<FaceRecognizer> recoginzer;
    //参考人数
    int userCount;
    //map用来存储正在考试的用户信息
    //key：id主键
    //value:结构体(x,y,name)
    map<int,PointAndName> map_users;

    //表格操作对象
    ExcelHelper helper;

};
#endif // MAINWINDOW_H
