#include "scaredmushroom.h"

ScaredMushroom::ScaredMushroom(QGraphicsObject *parent)
: QGraphicsObject{parent}
{
    setZValue(1);

    plantMovie = new QMovie(":/res/Plants/plant0.gif");
    if(!plantMovie -> isValid())
        qDebug() << "QMovie :/res/Plants/plant0.gif is not valid";

    plantMovie -> start();

    QTimer::singleShot(8000,[=](){
        init();
    });
}

void ScaredMushroom::advance(int phase)
{
    if(!phase)
        return;
    update();
}

void ScaredMushroom::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter -> drawImage(boundingRect(), plantMovie -> currentImage());
}

QRectF ScaredMushroom::boundingRect() const
{
    return QRect(0, 0, 48, 68);
}

void ScaredMushroom::init()
{
    QTimer *Timer = new QTimer(this);
    Timer -> start(2000);
    connect(Timer, &QTimer::timeout, this, &ScaredMushroom::creatVemon);
}

void ScaredMushroom::creatVemon()
{
    Venom *venom = new Venom();
    venom -> setPos(this -> x() + 45, this -> y() + 34);
    scene() -> addItem(venom);
}

ScaredMushroom::~ScaredMushroom()
{
    delete plantMovie;
}
