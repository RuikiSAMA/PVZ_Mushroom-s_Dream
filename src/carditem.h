#ifndef CARDITEM_H
#define CARDITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QPainter>
#include <QRandomGenerator>
#include <QPropertyAnimation>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>

class CardItme : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit CardItme(int n, int z, QGraphicsObject *parent = nullptr);
    void hideCard();
    void showCard();
    void soonDisappearAnimation();
    void setInvisibel();
    void setIsCardClicked();
    ~CardItme();
signals:
    void changeCursor(int n, CardItme *c);
    void thisHasDeleted();

private:
    void initCard(int n, int z);
    QRectF boundingRect() const override;
    void advance(int phase) override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *ev) override;

private slots:
    void fallDownAnimation();
    void startFlash();
    void flashAnimation();

private:
    bool cardClicked;
    bool IscardClicked;
    bool isVisible;
    int Num;
    int randx;
    int ypos;
    QPixmap cardPixmap;
    // QTimer *cardFallSpeed;
};



#endif // CARDITEM_H
