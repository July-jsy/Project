#include "examdialog.h"
#include "ui_examdialog.h"

ExamDialog::ExamDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ExamDialog)
{
    ui->setupUi(this);
    //给下拉菜单中添加人数  30-45
    QStringList nums;
    for(int i=30;i<=45;i++)
    {
        nums<<QString::number(i);
    }
    //将容器中的数显示到控件上
    ui->comboBox->addItems(nums);

}

ExamDialog::~ExamDialog()
{
    delete ui;
}

//开始考试
void ExamDialog::on_pushButton_clicked()
{
    //获取 输入框输入的科目
    QString cource=ui->lineEdit->text();
    //获取下拉菜单中的人数
    int count=ui->comboBox->currentText().toInt();

    //判空
    if(cource.isEmpty())
    {
        QMessageBox::information(this,"","输入科目名称");
        return ;
    }
    //创建下一个窗口对象
    MainWindow *mw=new MainWindow;
    //this当前窗口发出sendExamInfo
    //mw下一个窗口的槽函数来响应
    connect(this,&ExamDialog::sendExamInfo,mw,&MainWindow::recvExamInfo);

    mw->show();
    //发送自定义信号
    emit sendExamInfo(cource,count);
    //关闭当前窗口
    this->close();
}

