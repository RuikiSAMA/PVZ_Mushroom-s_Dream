#ifndef SHOVEL_H
#define SHOVEL_H

#include <QGraphicsObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

class shovel : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit shovel(QGraphicsObject *parent = nullptr);
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
    void mousePressEvent(QGraphicsSceneMouseEvent *ev) override;
    ~shovel();

signals:
    void changeCursor();

private:
    QPixmap *shovelPixmap;
};

#endif // SHOVEL_H
