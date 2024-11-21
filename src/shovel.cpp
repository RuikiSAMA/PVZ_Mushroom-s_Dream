#include "shovel.h"

shovel::shovel(QGraphicsObject *parent)
    : QGraphicsObject{parent}
{
    shovelPixmap = new QPixmap;
    shovelPixmap -> load(":/res/shovel.png");
}

void shovel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter -> drawPixmap(boundingRect().topLeft(), *shovelPixmap);
}

QRectF shovel::boundingRect() const
{
    return QRect(0, 0, 76, 34);
}

void shovel::mousePressEvent(QGraphicsSceneMouseEvent *ev)
{
    if(ev -> button() == Qt::LeftButton ){
        //  .contains(QPointF) Returns true if the given point is inside or on the edge of the rectangle; otherwise returns false.
        // cardClicked = true;
        // IscardClicked = true;
        emit changeCursor();
        qDebug() << "Clicked shovel！";
    }
}

shovel::~shovel()
{
    delete shovelPixmap;
}
