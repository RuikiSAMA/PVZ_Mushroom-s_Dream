#ifndef CLOVER_H
#define CLOVER_H

#include <QGraphicsObject>
#include "Plant.h"

class Clover : public Plant
{
    Q_OBJECT
public:
    explicit Clover(int N, QGraphicsObject *parent = nullptr);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
    int type() const override;
    ~Clover();

signals:

private:
};
#endif // CLOVER_H
