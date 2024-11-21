#include "plant.h"

Plant::Plant(int n, QGraphicsObject *parent)
    : QGraphicsObject{parent}
{
    setZValue(1);

    //  设置编号
    Num = n;

    //  设置血量
    HP = 100;

    plantMovie = new QMovie(QString(":/res/Plants/plant%1.gif").arg(n));
    if(!plantMovie -> isValid())
        qDebug() << QString("QMovie :/res/Plants/plant%1.gif is not valid").arg(Num);

    //  播放gif
    plantMovie -> start();

    //  控制播放速度
    plantMovie -> setSpeed(100);
}

void Plant::advance(int phase)
{
    if(!phase)
        return;
    if(this -> HP <= 0){
        emit plantDie(pos());
        this -> deleteLater();
    }
    update();
}

void Plant::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter -> drawImage(boundingRect(), plantMovie -> currentImage());
}

int Plant::type() const
{
    return 50;
}

void Plant::beHiting()
{
    QTimer *hitTimer = new QTimer(this);
    hitTimer -> start(1000);
    connect(hitTimer, &QTimer::timeout, this, [=](){
        this -> HP -= 10;
    });
}

Plant::~Plant()
{
    delete plantMovie;
}
