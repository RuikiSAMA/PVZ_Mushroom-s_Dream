#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QPropertyAnimation>

class myPushButton : public QPushButton
{
    Q_OBJECT
public:
    myPushButton(QString img0, QString img1 = "");
    void bounceAnimation0();    //  弹下动画
    void bounceAnimation1();    //  弹回动画

signals:

private:
    QString imgbutton0;
    QString imgbutton1;
};

#endif // MYPUSHBUTTON_H
