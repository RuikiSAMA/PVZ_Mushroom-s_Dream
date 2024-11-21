#include "doublepeashooter.h"

DoublePeaShooter::DoublePeaShooter(int N, QGraphicsObject *parent)
    : Plant{N, parent}
{

}

QRectF DoublePeaShooter::boundingRect() const
{
    return QRect(0, 0, 66, 66);
}

int DoublePeaShooter::type() const
{
    return 4;
}

void DoublePeaShooter::shot()
{
    emit shotBullet(this);
}
