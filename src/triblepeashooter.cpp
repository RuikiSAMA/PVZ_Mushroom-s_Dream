#include "triblepeashooter.h"

TriblePeaShooter::TriblePeaShooter(int N, QGraphicsObject *parent)
    : Plant{N, parent}
{}

QRectF TriblePeaShooter::boundingRect() const
{
    return QRect(0, 0, 68, 75);
}

int TriblePeaShooter::type() const
{
    return 6;
}

void TriblePeaShooter::shot()
{
    emit shotBullet(this);
}
