#ifndef BULLETREPEA_H
#define BULLETREPEA_H

#include "plant.h"
#include "Zombie.h"
#include "Star.h"
#include "peashooter.h"
#include <QGraphicsObject>
#include <QPainter>
#include <QMovie>
#include "twinpeashooter.h"
#include "doublepeashooter.h"
#include "triblepeashooter.h"
#include "redoublepeashooter.h"

class bulletRePea : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit bulletRePea(Plant * , QGraphicsObject *parent = nullptr);
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
    bool collidesWithItem(const QGraphicsItem *other,
                          Qt::ItemSelectionMode mode)const override;
    void advance(int phase) override;
    void setIsFly();
    ~bulletRePea();

signals:
    void deletebullet();

private:
    Plant *originPlant;
    QMovie *bulletPeaMovie;
    QMovie *bulletPeaExplodeMovie;
};

#endif // BULLETREPEA_H
