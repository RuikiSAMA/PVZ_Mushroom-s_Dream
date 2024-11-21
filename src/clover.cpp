#include "clover.h"



Clover::Clover(int N, QGraphicsObject *parent)
    : Plant {N, parent}
{

}

QRectF Clover::boundingRect() const
{
    return QRect(-15, -105, 164, 190);
}

QPainterPath Clover::shape() const
{
    QPainterPath path;
    path.addRect(QRect(-15, -105, 160, 180));
    return path;
}

void Clover::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter -> drawImage(QRect(-10, -5, 90, 90), plantMovie -> currentImage());
    // painter->setPen(QPen(Qt::black, 0, Qt::SolidLine));
    // painter->setBrush(Qt::NoBrush);
    // painter->drawRect(boundingRect() + QMarginsF(0,-100,-80,-30));
}

int Clover::type() const
{
    return 8;
}

Clover::~Clover()
{

}
