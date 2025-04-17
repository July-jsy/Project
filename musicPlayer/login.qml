import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
//外窗口
ApplicationWindow {

    id:root
    width: 1000
    height: 800
    visible: true
    title: qsTr("Hello World")
    color: "lightblue"

    //属性，标题栏隐藏 无框窗口提示,必须要前面的,不然系统桌面菜单栏,看不到软件
    flags: Qt.Window | Qt.FramelessWindowHint

    //窗口拖动
    property int dragx: 0 //属性命令要小写字母开头
    property int dragy: 0
    property bool isDrag: false

    //窗口拖动
    MouseArea{
        width: parent.width
        height: 100
        //鼠标按下
        onPressed: {
            //记录下鼠标按下的坐标，更改标志位
            root.dragx = mouseX;
            root.dragy = mouseY;
            root.isDrag = true
        }
    //鼠标抬起
        onReleased: root.isDrag = false;//鼠标释放
    //位置改变时候
        onPositionChanged: {
        if(root.isDrag){
            console.log("mouseX = ", mouseX)
            console.log("mouseY = ",mouseY)
            //拖动的位置 = 鼠标移动后位置-鼠标按下的位置
            root.x += mouseX - root.dragx
            root.y += mouseY - root.dragy
            }
        }
    }


    //Signal：login 0，register 1
    signal btnclicked(string name,string pass,int flag)


    Rectangle{
        //同外窗口尺寸
        width:parent.width
        height: parent.height
        //居中
        anchors.centerIn: parent
        //渐变色
        gradient: Gradient{
            GradientStop{position:0;color:"#4158d0"}
            GradientStop{position:1;color:"#c850c0"}
            orientation: Gradient.Horizontal
        }

        Rectangle{

            width:800
            height:500
            anchors.centerIn: parent
            radius:10

            Image {
                x:57
                y:100
                width:350
                height:350
                source: "qrc:/../../icon/login.jpg"

            }

            Text {
                id: log
                x:530
                y:130
                width:120
                height: 30

                font.pointSize: 24

                text: qsTr("登录系统")
            }

            TextField{
                id:username
                objectName: "username"
                x:440
                y:220
                width:300
                height: 50
                font.pixelSize: 20

                placeholderText: "输入用户名"

                placeholderTextColor: "#999999"
                color: "#666666"
                //距离左边边框距离 60
                leftPadding: 60
                //背景设置
                background: Rectangle{
                    color: "#e6e6e6"
                    border.color: "#e6e6e6"
                    radius: 25
                }
                //设置左边的用户图标
                Image {
                    width: 20
                    height: 20
                    x:30;
                    y:15
                    source: username.activeFocus ?"qrc:/icon/kaifdog.png":"qrc:/icon/qusefdogicon.png"
                }

            }

            TextField{
                id:password
                objectName: "password"
                x:440
                y:username.y+username.height+10
                width:300
                height: 50
                font.pixelSize: 20
                //暗纹形式
                echoMode: TextInput.Password

                leftPadding: username.leftPadding
                //默认提示文字 提示文字颜色
                placeholderText: "输入密码"

                placeholderTextColor: "#999999"
                color: "#666666"
                //背景设置
                background: Rectangle{
                    color: "#e6e6e6"
                    border.color: "#e6e6e6"
                    radius: 25
                }
                //she'zhi左边的用户图标
                Image {
                    width: 20
                    height: 20
                    x:30
                    y:15
                source: password.activeFocus ?"qrc:/icon/kaisuo.png":"qrc:/icon/suo.png"
                }
            }

            //login
            Button{
                id:login
                x:440
                y:password.y+password.height+10
                width:password.width/2-10
                height: 50
                palette.buttonText:"white"
                font.pixelSize: 20
                text: "登录"
                //点击事件
                onClicked: {
                    console.log("login")
                    btnclicked(username.text,password.text,0)

                }
            background: Rectangle{
                radius: 25
                color: {
                if(login.down)
                    return "#00b846"
                else if(login.hovered)
                    return "#333333"
                else
                    return "#57b864"
                }
            }

            }


            //register
            Button{
                id:register
                x:login.x+login.width+10
                y:password.y+password.height+10
                width:password.width/2-10
                height: 50
                font.pixelSize: 20
                text: "注册"
                palette.buttonText:"white"
                //点击事件
                onClicked: {
                    console.log("register")
                    btnclicked(username.text,password.text,1)
                }

                background: Rectangle{
                    radius: 25
                    color: {
                    if(register.down)
                        return "#00b846"
                    else if(register.hovered)
                        return "#333333"
                    else
                        return "#57b864"
                    }
                }

            }










        }



    }
    //关闭按钮
    Rectangle{
    //右上角的坐标位置
        x:root.width - 35
        y:5
        width: 30
        height: 30
        color: "#00000000" //rgba 最后表示透明度
        Text {
            id: close
            text: qsTr("×")
            color: "black"
            font.pixelSize: 28
            anchors.centerIn: parent
        }
        //鼠标区域事件
        MouseArea{
            anchors.fill: parent
            //设置监听鼠标移入事件，默认不开启
            hoverEnabled: true
            //鼠标进入时
            onEntered: {
                parent.color = "#1BFFFFFF"
            }
            onExited: parent.color = "#00000000" // 鼠标退出时
            onPressed: parent.color = "#FF0000"; //鼠标按下时
            onClicked: root.close() //调用主窗口函数，关闭界面。
        }
    }

}
