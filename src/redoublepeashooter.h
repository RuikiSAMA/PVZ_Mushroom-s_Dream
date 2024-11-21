#ifndef REDOUBLEPEASHOOTER_H
#define REDOUBLEPEASHOOTER_H

#include <QGraphicsObject>
#include "Plant.h"

class ReDoublePeaShooter : public Plant
{
    Q_OBJECT
public:
    explicit ReDoublePeaShooter(int N, QGraphicsObject *parent = nullptr);
    QRectF boundingRect() const override;
    int type() const override;
    void shot();

signals:
    void shotBullet(ReDoublePeaShooter *d);
};

#endif // REDOUBLEPEASHOOTER_H
