#ifndef SCAREDMUSHROOM_H
#define SCAREDMUSHROOM_H

#include <QGraphicsObject>
#include <QTimer>
#include <QGraphicsScene>
#include "venom.h"

class ScaredMushroom : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit ScaredMushroom(QGraphicsObject *parent = nullptr);
    void advance(int phase) override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
    void init();
    ~ScaredMushroom();

signals:

private:
    QMovie *plantMovie;

public slots:
    void creatVemon();
};
#endif // SCAREDMUSHROOM_H
