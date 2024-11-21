#ifndef VENOM_H
#define VENOM_H

#include "peashooter.h"
#include "star.h"
#include <QGraphicsObject>
#include <QPainter>
#include <QMovie>
#include "twinpeashooter.h"
#include "doublepeashooter.h"
#include "triblepeashooter.h"
#include "redoublepeashooter.h"

class Venom : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit Venom(QGraphicsObject *parent = nullptr);
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem *other,
                          Qt::ItemSelectionMode mode)const override;
    void setIsFly();
    ~Venom();

private:
    QMovie *bulletMovie;
    QMovie *bulletExplodeMovie;
    bool IsFly;
    mutable int collidingType;
};
#endif // VENOM_H
