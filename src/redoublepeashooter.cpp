#include "redoublepeashooter.h"

ReDoublePeaShooter::ReDoublePeaShooter(int N, QGraphicsObject *parent)
    : Plant{N, parent}
{

}

QRectF ReDoublePeaShooter::boundingRect() const
{
    return QRect(0, 0, 66, 66);
}

int ReDoublePeaShooter::type() const
{
    return 5;
}

void ReDoublePeaShooter::shot()
{
    emit shotBullet(this);
}
