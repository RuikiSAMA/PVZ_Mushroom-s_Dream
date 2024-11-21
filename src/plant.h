#ifndef PLANT_H
#define PLANT_H

#include <QObject>
#include <QGraphicsObject>
#include <QMovie>
#include <QPainter>
#include <QTimer>

class Plant : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit Plant(int N, QGraphicsObject *parent = nullptr);
    int HP;
    void advance(int phase) override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
    int type() const override;
    void beHiting();
    ~Plant();

signals:
    void plantDie(QPointF);

protected:
    int Num;
    QMovie *plantMovie;
};

#endif // PLANT_H
