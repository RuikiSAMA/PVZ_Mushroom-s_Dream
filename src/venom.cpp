#include "venom.h"

Venom::Venom(QGraphicsObject *parent): QGraphicsObject{parent}
{
    collidingType = 0;

    IsFly = true;

    setZValue(1);

    bulletMovie = new QMovie(":/res/bullet/MushroomBullet.gif");
    if(!bulletMovie -> isValid())
        qDebug() << ":/res/bullet/MushroomBullet.gif is not valid";
    bulletMovie -> start();

    bulletExplodeMovie = new QMovie(":/res/bullet/BulletMushRoomExplode_0.gif");
    if(!bulletExplodeMovie -> isValid())
        qDebug() << ":/res/bullet/BulletMushRoomExplode_0.gif is not valid";
    bulletExplodeMovie -> start();
}

void Venom::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(IsFly)
        painter -> drawImage(boundingRect(), bulletMovie -> currentImage());
    else
        painter -> drawImage(QRectF(0, 0, 51, 45), bulletExplodeMovie -> currentImage());
}

QRectF Venom::boundingRect() const
{
    return (QRectF(0, 0, 43, 18));
}

void Venom::advance(int phase)
{
    if(!phase){
        return;
    }

    QList <QGraphicsItem*> collideItems = collidingItems(Qt::IntersectsItemShape);
    if(!collideItems.isEmpty())
        for (QGraphicsItem* item : collideItems) {
            if(item -> type() == 1){
                qDebug() << "Venom collide with PeaShooter!";
                PeaShooter *peashooter = qgraphicsitem_cast<PeaShooter*>(item);
                peashooter -> shot();
                this -> deleteLater();
            }
            else if(item -> type() == 2){
                qDebug() << "Venom collide with Star!";
                Star *star = qgraphicsitem_cast<Star*>(item);
                star -> shot();
                this -> deleteLater();
            }
            else if(item -> type() == 3){
                qDebug() << "Pea collide with TwinPeaShooter!";
                TwinPeaShooter *twps = qgraphicsitem_cast<TwinPeaShooter*>(item);
                twps -> shot();
                this -> deleteLater();
            }
            else if(item -> type() == 4){
                qDebug() << "Pea collide with DoublePeaShooter!";
                DoublePeaShooter *dps = qgraphicsitem_cast<DoublePeaShooter*>(item);
                dps -> shot();
                this -> deleteLater();
            }
            else if(item -> type() == 5){
                qDebug() << "Pea collide with ReDoublePeaShooter!";
                ReDoublePeaShooter *rdps = qgraphicsitem_cast<ReDoublePeaShooter*>(item);
                rdps -> shot();
                this -> deleteLater();
            }
            else if(item -> type() == 6){
                qDebug() << "Pea collide with TriblePeaShooter!";
                TriblePeaShooter *tps = qgraphicsitem_cast<TriblePeaShooter*>(item);
                tps -> shot();
                this -> deleteLater();
            }
        }

    update();

    this -> moveBy(6, 0);

    if(pos().x() < 0 || pos().x() > 1000 || pos().y() < 0 || pos().y() > 600){
        this -> deleteLater();
        // qDebug() << "delete a venom!";
    }
    // if(IsFly)
    //     this -> moveBy(5, 0);
    // else
    //     this -> deleteLater();
}

bool Venom::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    // 获取边界
    QPainterPath otherShape = other->shape();

    // 相交检测
    if (shape().intersects(otherShape.translated(other->pos() - pos())))
        return true;
    else
        return false;
}

void Venom::setIsFly()
{
    IsFly = false;
}

Venom::~Venom()
{
    delete bulletMovie;
    delete bulletExplodeMovie;
}
