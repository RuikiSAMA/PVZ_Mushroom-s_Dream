#ifndef PEASHOOTER_H
#define PEASHOOTER_H

#include "plant.h"
#include <QGraphicsObject>

class PeaShooter : public Plant
{
    Q_OBJECT
public:
    explicit PeaShooter(int N, QGraphicsObject *parent = nullptr);
    QRectF boundingRect() const override;
    int type() const override;
    void shot();
    ~PeaShooter();

signals:
    void shotBullet(PeaShooter* p);

private:
};

#endif // PEASHOOTER_H
