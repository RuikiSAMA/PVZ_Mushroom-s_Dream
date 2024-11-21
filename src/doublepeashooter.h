#ifndef DOUBLEPEASHOOTER_H
#define DOUBLEPEASHOOTER_H

#include <QGraphicsObject>
#include "Plant.h"

class DoublePeaShooter : public Plant
{
    Q_OBJECT
public:
    explicit DoublePeaShooter(int N, QGraphicsObject *parent = nullptr);
    QRectF boundingRect() const override;
    int type() const override;
    void shot();

signals:
    void shotBullet(DoublePeaShooter *d);
};

#endif // DOUBLEPEASHOOTER_H
