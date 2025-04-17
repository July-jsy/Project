#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //级联分类器的初始化  配置一个模型文件
    classifier=CascadeClassifier("D:/DevTools/Qt/OpenCV/opencv3.4-install/install/etc/haarcascades/haarcascade_frontalface_alt2.xml");

    //face.xml 用来保存录入的人脸信息（人脸信息+标签）
    QFile file("face.xml");
    if(file.exists())
    {
        recoginzer=FaceRecognizer::load<LBPHFaceRecognizer>("face.xml");
    }
    else
    {
        recoginzer=LBPHFaceRecognizer::create();
    }
    //设置阈值：可信度》阈值，识别失败
    recoginzer->setThreshold(150);
    srand(time(0));

    if(vc.open(0))
    {
        startTimer(50);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::recvExamInfo(QString cource, int count)
{
    qDebug()<<cource<<count;

    userCount=count;

    //显示标题
    ui->label->setText(cource+"考试");
    //根据count人数,动态创建label控件,添加到网格布局
    //每行七个
    int row=0, index=0;
    while (true)
    {

        for(int i=0;i<7;i++)
        {
            if(index==count)
                return ;


            QLabel *label=new QLabel;

            //设置一个objectname属性，最初为0
            label->setObjectName("0");

            //增加线的效果
            label->setFrameShape(QFrame::Box);

            //设置显示图片
            QPixmap p(":/avater.png");
            p=p.scaled(QSize(60,60));
            label->setPixmap(p);

            //添加到网格布局中           添加俄控件 行 列 占用1行 占用1列
            ui->gridLayout->addWidget(label,row,i,1,1);
            index++;

        }
        //换行
        row++;
    }
}
void MainWindow::timerEvent(QTimerEvent *event)
{
    //提取一帧图像
    vc>>frame;
    //翻转图像
    flip(frame,frame,1);
    //灰度图
    Mat gray;
    cvtColor(frame,gray,CV_BGR2GRAY);
    //查找人脸,画框
    classifier.detectMultiScale(gray,findFace);
    //画框：找到第一个人脸上画框
    if(findFace.size()>0)
    {
        rectangle(frame,findFace[0],Scalar(0,0,255));
    }
    //显示一帧图像
    showImg();

}

void MainWindow::showImg()
{
    QImage img(frame.data,
               frame.cols,
               frame.rows,
               frame.cols*frame.channels(),
               QImage::Format_BGR888
               );
    QPixmap p=QPixmap::fromImage(img);
    ui->label_video->setPixmap(p);
    ui->label_video->resize(QSize(p.size()));
}



//face显示的人脸图片
//pointAndName  结构体
//rand_x rand_y  通过xy找到对应的label的值
//flag标志位0:离开 1开始考试
//返回值:真-->重复   假-->可选
bool MainWindow::changeLabelImg(Mat face, PointAndName &v, int flag)
{
    //获取对应的坐标位置的label控件  参数：行，列
    //父类指针
    QWidget *w=ui->gridLayout->itemAtPosition(v.rand_x,v.rand_y)->widget();

    //父子类指针的转换
    QLabel *label=dynamic_cast<QLabel*>(w);

    if(flag==0)//离开
    {
        label->setText(v.name+"结束考试");
        return false;
    }

    QString objectName=label->objectName();
    if(objectName=="1")
    {
        qDebug()<<"有人了";
        return true;
    }

    //更改属性，变为有人坐
    label->setObjectName("1");

    //坐标位置 显示人脸照片
    QImage img(face.data,face.cols,face.rows,face.cols*face.channels(),QImage::Format_BGR888);

    QPixmap p=QPixmap::fromImage(img);
    p=p.scaled(QSize(80,80));//调整图片的大小
    //增加线的效果
    label->setFrameShape(QFrame::Box);
    label->setPixmap(p);
    return false;
}


//选座
void MainWindow::on_pushButton_choice_clicked()
{
    //获取输入的姓名
    QString name=ui->lineEdit->text();
    if(name.isEmpty())
    {
        QMessageBox::information(this,"","请输入姓名");
        return ;
    }
    //容错：摄像头前是否有有效的人脸
    if(findFace.size()==0)
    {
        QMessageBox::information(this,"","未识别有效人脸");
        return ;
    }
    //截取有效的人脸
    Mat face=frame(findFace[0]).clone();
    Mat gray;

    //统一操作  灰度  100*100
    cvtColor(face,gray,CV_BGR2GRAY);
    cv::resize(gray,gray,Size(100,100));

    //获取人脸图片---》保存到容器中
    vector<Mat> studyFaces;
    studyFaces.push_back(gray);

    //数据库操作   获取当前用户id的主键-->作为这个用户的标签值
    bool ok=DbManager::getFace()->insertUser(name);
    if(!ok)
    {
        QMessageBox::information(this,"","用户插入失败");
        return ;
    }

    //数据库获取 当前用户的主键id-》作为这个用户的标签值
    int id=DbManager::getFace()->getUserId();
    if(id==-1)
    {
        QMessageBox::information(this,"","用户插入失败2");
        return ;

    }
    vector<int> studyLables;
    studyLables.push_back(id);

    //人脸识别器  录入的过程(保存到xml文件中-->人脸容器+标签容器)
    recoginzer->update(studyFaces,studyLables);
    recoginzer->save("face.xml");

    //坐标  选座位  显示人脸
    PointAndName value;
    do
    {
        int num=rand()%userCount;
        int x=num/7;//行
        int y=num%7;//列

        value.rand_x=x;
        value.rand_y=y;
        value.name=name;
    }while(changeLabelImg(face,value,1));
    QMessageBox::information(this,"","录入成功");

    //保存到map容器中
    map_users[id]=value;//修改

}

//离开
void MainWindow::on_pushButton_leave_clicked()
{
    if(findFace.size()==0)
    {
        QMessageBox::information(this,"","未识别到人脸");
        return ;
    }

    //级联分类器找到待离开时的人脸图片
    Mat face=frame(findFace[0]).clone();

    cvtColor(face,face,CV_BGR2GRAY);
    cv::resize(face,face,Size(100,100));

    //人脸识别  预测 成功--》标签+可信度
    int label=-1;
    double confidence=0;

    recoginzer->predict(face,label,confidence);
    if(label==-1)
    {
        QMessageBox::information(this,"","识别失败");
        return ;
    }

    //标签==》map的key
    PointAndName value=map_users[label];

    //弹窗提示是否离开
    int choose=QMessageBox::information(this,"",value.name+"确定结束考试吗？",QMessageBox::Ok|QMessageBox::Cancel);

    if(choose==QMessageBox::Ok)
    {
        //通过坐标 更新 网格布局
        changeLabelImg(Mat(),value,0);
        //离开成功  更新表endTime离开时间
        DbManager::getFace()->updateEndTime(label);
    }
}

//导出信息
void MainWindow::on_pushButton_derive_clicked()
{
    //弹窗  选择一个表格文件
    QString path=QFileDialog::getOpenFileName();
    helper.open(path);

    //按照路径 打开文件
    helper.open(path);

    //添加标题
    helper.addTitle(path);

    //容器中数据  写入表格
    vector<UserData> infos;
    DbManager::getFace()->selectInfo(infos);

    helper.addInfos(path,infos);

    //关闭文件
    helper.close();

    //提示，导出成功
    QMessageBox::information(this,"","导出成功");

}





