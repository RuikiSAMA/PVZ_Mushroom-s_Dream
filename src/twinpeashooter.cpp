#include "twinpeashooter.h"

TwinPeaShooter::TwinPeaShooter(int N, QGraphicsObject *parent)
    : Plant{N, parent}
{}

QRectF TwinPeaShooter::boundingRect() const
{
    return QRect(0, 0, 85, 71);
}

int TwinPeaShooter::type() const
{
    return 3;
}

void TwinPeaShooter::shot()
{
    emit shotBullet(this);
}
