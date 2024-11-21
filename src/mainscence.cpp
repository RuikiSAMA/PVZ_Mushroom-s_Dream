#include "mainscence.h"
#include "ui_mainscence.h"
#include "mypushbutton.h"
#include "grassgroundscence.h"
#include <QPainter>
#include <QLabel>
#include <QVector>
#include <QTimer>
#include <QDebug>

mainScience::mainScience(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mainScience)
{
    ui->setupUi(this);
    //  初始化窗口图标
    setWindowIcon(QIcon(":/res/brain.png"));

    //  初始化窗口标题
    setWindowTitle("Plants vs Zombies");

    //  初始化窗口大小
    setFixedSize(900, 600);

    //  初始化主界面开始按钮
    myPushButton *startButton = new myPushButton(":/res/startButton0.png", ":/res/startButton1.png");

    //  调整按钮位置
    startButton -> move(
        this -> width() * 0.5 + 20, this -> height() * 0.125);

    //  设置按钮父类
    startButton -> setParent(this);


    //  连接按下按钮与槽函数
    connect(startButton, &QPushButton::clicked, [this, startButton](){
        //  显示按钮动画
        startButton -> bounceAnimation0();
        startButton -> bounceAnimation1();

        //  设置僵尸手破土而出动画
        QLabel *hand = new QLabel(this);

        //  设置手的父类
        hand -> setParent(this);

        //  调整手出现位置
        hand -> move(210, 260);

        //  设置手的帧数组
        QVector<QPixmap> handPix;

        for(int i = 0; i < 7; i++){ //  向帧数组中添加帧
            QPixmap pix;
            bool ret = pix.load(QString(":/res/zombiehand%1.png").arg(i));
            if(!ret)    //  判断是否可以正常加载图片
                qDebug() << QString("faild to load hand");
            handPix.append(pix);
        }


        //  添加定时器控制手动画的帧切换间隔
        QTimer *timer = new QTimer(this);

        timer -> start(1000/30);

        connect(timer, &QTimer::timeout, [this, timer, hand, handPix](){
            //  不知道为什么不能传引用，一传引用就崩溃？？

            //  创建，qDebug() 输出帧索引
            static int i = 0;
            qDebug() << "load zombie hand out animation!";

            //  为 hand 标签设定帧
            hand -> setPixmap(handPix[i]);

            //  输出帧
            hand -> show();
            i++;
            if(i == 7){
                timer -> stop();
                emit this -> rotateScence();
                QTimer::singleShot(1000,[=](){
                    //  加载下一场景
                    grassGroundScence *grassScence = new grassGroundScence;
                    grassScence -> hide();

                    //  隐藏主场景，显示草坪场景
                    this -> hide();
                    grassScence -> show();

                    connect(grassScence, &grassGroundScence::returnMainScene, this, &mainScience::show);
                });
            }
        });
    });
}

void mainScience::paintEvent(QPaintEvent *)
{
    //  显示菜单栏背景图
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/res/Surface.png"));
}

mainScience::~mainScience()
{
    delete ui;
}
