#ifndef BULLETPEA_H
#define BULLETPEA_H

#include "plant.h"
#include "Zombie.h"
#include <QGraphicsObject>
#include <QPainter>
#include <QMovie>
#include "Star.h"
#include "peashooter.h"
#include "twinpeashooter.h"
#include "doublepeashooter.h"
#include "triblepeashooter.h"
#include "redoublepeashooter.h"

class bulletPea : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit bulletPea(Plant * , QGraphicsObject *parent = nullptr);
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
    bool collidesWithItem(const QGraphicsItem *other,
                          Qt::ItemSelectionMode mode)const override;
    void advance(int phase) override;
    void setIsFly();
    int type() const override;
    ~bulletPea();

private:
    int ATK;
    Plant *originPlant;
    QMovie *bulletPeaMovie;
    QMovie *bulletPeaExplodeMovie;
    bool IsDeflection;
    bool IsV;
    QPointF center;
    qreal angle;
    qreal R;
    qreal currentAngle;

signals:
    void deletebullet();
};

#endif // BULLETPEA_H
