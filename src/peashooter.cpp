#include "peashooter.h"

PeaShooter::PeaShooter(int N, QGraphicsObject *parent)
    : Plant{N, parent}
{}

QRectF PeaShooter::boundingRect() const
{
    return (QRectF(0, 0, 63, 70));
}

void PeaShooter::shot()
{
    emit shotBullet(this);
}


PeaShooter::~PeaShooter()
{}

int PeaShooter::type() const
{
    return 1;
}
