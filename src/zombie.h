#ifndef ZOMBIE_H
#define ZOMBIE_H

// #include "bulletpea.h"
#include <QObject>
#include <QGraphicsObject>
#include <QGraphicsScene>
#include <QMovie>
#include <QPainter>
#include "Star.h"
#include "peashooter.h"
#include "twinpeashooter.h"
#include "doublepeashooter.h"
#include "triblepeashooter.h"
#include "redoublepeashooter.h"
#include "clover.h"

class Zombie : public QGraphicsObject{
    Q_OBJECT
public:
    explicit Zombie(int N, QGraphicsObject *parent = nullptr);
    QRectF boundingRect() const override;
    void advance(int phase) override;
    QPainterPath shape() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
    bool collidesWithItem(const QGraphicsItem *other,
                          Qt::ItemSelectionMode mode)const override;
    int type() const override;
    int HP;

protected:
    int Num;
    QMovie *zombieMovie;
    QMovie *zombieEatingMovie;
    QMovie *zombieDieMovie;
    int ATK;

private:
    bool IsLiving;
    bool IsEating;

signals:
    void gameover();
};

#endif // ZOMBIE_H
