#ifndef TRIBLEPEASHOOTER_H
#define TRIBLEPEASHOOTER_H

#include <QGraphicsObject>
#include "plant.h"

class TriblePeaShooter : public Plant
{
    Q_OBJECT
public:
    explicit TriblePeaShooter(int N, QGraphicsObject *parent = nullptr);
    QRectF boundingRect() const override;
    int type() const override;
    void shot();

signals:
    void shotBullet(TriblePeaShooter *t);
};

#endif // TRIBLEPEASHOOTER_H
