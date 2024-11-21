#ifndef BULLETSTAR_H
#define BULLETSTAR_H

#include <QGraphicsObject>
#include <QPainter>
#include <QMovie>
#include "zombie.h"
#include "peashooter.h"
#include "star.h"
#include "twinpeashooter.h"
#include "doublepeashooter.h"
#include "triblepeashooter.h"
#include "redoublepeashooter.h"
#include <cmath>

class bulletStar : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit bulletStar(Plant *, QGraphicsObject *parent = nullptr);
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
    bool collidesWithItem(const QGraphicsItem *other,
                          Qt::ItemSelectionMode mode)const override;
    void advance(int phase) override;
    int type() const override;
    ~bulletStar();

signals:
    void deletebullet();

private:
    int ATK;
    QMovie *bulletMovie;
    Plant *originPlant;
    bool IsDeflection;
    bool IsH;
    QPointF center;
    qreal angle;
    qreal R;
    qreal currentAngle;

};

#endif // BULLETSTAR_H
