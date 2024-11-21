#ifndef STAR_H
#define STAR_H

#include <QGraphicsObject>
#include "plant.h"

class Star : public Plant
{
    Q_OBJECT
public:
    explicit Star(int N, QGraphicsObject *parent = nullptr);
    QRectF boundingRect() const override;
    int type() const override;
    void shot();

signals:
    void shotBullet(Star *s);
};

#endif // STAR_H
