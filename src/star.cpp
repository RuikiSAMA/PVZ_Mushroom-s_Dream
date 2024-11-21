#include "star.h"

Star::Star(int N, QGraphicsObject *parent)
    : Plant{N, parent}
{}

QRectF Star::boundingRect() const
{
    return QRect(0, 0, 68, 61);
}

int Star::type() const
{
    return 2;
}

void Star::shot()
{
    // qDebug() << "shot a star";
    emit shotBullet(this);
}
