#include "mypushbutton.h"

myPushButton::myPushButton(QString img0, QString img1)
{   //  按钮初始化
    this -> imgbutton0 = img0;  //  按下前图片
    this -> imgbutton1 = img1;  //  按下后图片

    QPixmap pix;
    bool ret = pix.load(imgbutton0);
    if(!ret)    //  判断是否可以正常加载图片
        qDebug() << QString("faild to load %1").arg(img0);

    //  设置按钮尺寸
    this -> setFixedSize(pix.width(), pix.height());

    //  设置按钮风格
    this -> setStyleSheet("QPushButton{border:0px;}");  //  按钮边界为 0 像素

    //  设置按钮图标
    this -> setIcon(pix);

    //  设置图标大小
    this -> setIconSize(QSize(pix.width(), pix.height()));
}

void myPushButton::bounceAnimation0()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    //  "geometry" 为

    //  设置动画时间间隔
    animation -> setDuration(150);

    //  设置起始位置
    animation -> setStartValue(
        QRect(this -> x(), this -> y(), this -> width(), this -> height()));

    //  设置结束位置
    animation -> setEndValue(
        QRect(this -> x(), this -> y() + 5, this -> width(), this -> height()));

    //  设置弹跳过程中动画效果  QEasingCurve 中有多种弹跳效果
    animation -> setEasingCurve(QEasingCurve::OutQuad);

    //  切换按下图片
    this -> setIcon(QPixmap(imgbutton1));

    //  执行动画
    animation -> start(QAbstractAnimation::DeleteWhenStopped);
    //  参数为枚举值，实现在动画结束后释放对象，防止内存泄漏
}

void myPushButton::bounceAnimation1()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");

    animation -> setDuration(50);

    animation -> setStartValue(
        QRect(this -> x(), this -> y() + 5, this -> width(), this -> height()));
    //  注意：弹下动画函数会改变按钮位置，因此初始位置为弹下后的位置

    animation -> setEndValue(
        QRect(this -> x(), this -> y(), this -> width(), this -> height()));
    //  回到弹下前的位置

    //  设置动画过渡类型
    animation -> setEasingCurve(QEasingCurve::OutQuad);

    //  开始动画
    animation -> start(QAbstractAnimation::DeleteWhenStopped);
}
