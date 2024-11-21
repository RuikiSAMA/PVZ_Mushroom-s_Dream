#ifndef TWINPEASHOOTER_H
#define TWINPEASHOOTER_H

#include <QGraphicsObject>
#include "plant.h"
class TwinPeaShooter : public Plant
{
    Q_OBJECT
public:
    explicit TwinPeaShooter(int N, QGraphicsObject *parent = nullptr);
    QRectF boundingRect() const override;
    int type() const override;
    void shot();
signals:
    void shotBullet(TwinPeaShooter *);
};

#endif // TWINPEASHOOTER_H
