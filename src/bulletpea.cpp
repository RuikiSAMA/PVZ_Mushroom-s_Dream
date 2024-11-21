#include "bulletpea.h"

bulletPea::bulletPea(Plant *plant, QGraphicsObject *parent)
    : QGraphicsObject {parent} , originPlant {plant}
{
    ATK = 10;

    IsDeflection = true;

    angle = M_PI / 100;
    R = 120;

    IsV = false;

    currentAngle = M_PI / 2;

    setZValue(1);

    bulletPeaMovie = new QMovie(":/res/bullet/pea.gif");
    if(!bulletPeaMovie -> isValid())
        qDebug() << ":/res/bullet/pea.gif is not valid";
    bulletPeaMovie -> start();

    bulletPeaExplodeMovie = new QMovie(":/res/bullet/BulletPeaExplode.gif");
    if(!bulletPeaExplodeMovie -> isValid())
        qDebug() << ":/res/bullet/BulletPeaExplode.gif is not valid";
    bulletPeaExplodeMovie -> start();
}

void bulletPea::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // if(!collidingType)
        painter -> drawImage(boundingRect(), bulletPeaMovie -> currentImage());
    // else
        // painter -> drawImage(boundingRect(), bulletPeaExplodeMovie -> currentImage());
}

QRectF bulletPea::boundingRect() const
{
    return QRectF(0, 0, 40, 24);
}

bool bulletPea::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    // 获取边界
    QPainterPath otherShape = other->shape();

    // 相交检测
    if (shape().intersects(otherShape.translated(other->pos() - pos())))
        return true;
    else
        return false;
}

void bulletPea::advance(int phase)
{
    if(phase){
        return;
    }
    QList <QGraphicsItem*> collideItems = collidingItems();
    for (QGraphicsItem* item : collideItems) {
        if(item -> type() == 1 && item != originPlant){
            // qDebug() << "pea collide with peaShooter";
            PeaShooter* peashooter = qgraphicsitem_cast<PeaShooter*>(item);
            peashooter -> shot();
            emit deletebullet();
            this -> deleteLater();
        }
        else if(item -> type() == 2 && item != originPlant){
            // qDebug() << "Pea collide with Star!";
            Star *star = qgraphicsitem_cast<Star*>(item);
            star -> shot();
            this -> deleteLater();
        }
        else if(item -> type() == 3 && item != originPlant){
            // qDebug() << "Pea collide with TwinPeaShooter!";
            TwinPeaShooter *twps = qgraphicsitem_cast<TwinPeaShooter*>(item);
            twps -> shot();
            emit deletebullet();
            this -> deleteLater();
        }
        else if(item -> type() == 4 && item != originPlant){
            // qDebug() << "Pea collide with DoublePeaShooter!";
            DoublePeaShooter *dps = qgraphicsitem_cast<DoublePeaShooter*>(item);
            dps -> shot();
            emit deletebullet();
            this -> deleteLater();
        }
        else if(item -> type() == 5 && item != originPlant){
            // qDebug() << "Pea collide with ReDoublePeaShooter!";
            ReDoublePeaShooter *rdps = qgraphicsitem_cast<ReDoublePeaShooter*>(item);
            rdps -> shot();
            emit deletebullet();
            this -> deleteLater();
        }
        else if(item -> type() == 6 && item != originPlant){
            // qDebug() << "Pea collide with TriblePeaShooter!";
            TriblePeaShooter *tps = qgraphicsitem_cast<TriblePeaShooter*>(item);
            tps -> shot();
            emit deletebullet();
            this -> deleteLater();
        }
        else if(item -> type() == 8){
            if(IsDeflection){
                // qDebug() << "deflection！";
                center = this -> pos() + QPointF(0, 120);
                IsDeflection = false;
                IsV = true;
            }
            if(currentAngle > 0){
                currentAngle -= angle;
                qreal dx = R * std::cos(currentAngle);
                qreal dy = R * std::sin(currentAngle);
                this -> setPos(center + QPointF(dx, -dy));
                // update();
                return;
            }
        }
        else if (item -> type() == 99) {
            qDebug() << "pea collide with zombie";
            Zombie* zombie = qgraphicsitem_cast<Zombie*>(item);
            zombie -> HP -= ATK;
            emit deletebullet();
            this -> deleteLater();
        }
    }
    update();
    if(IsV == false){
        this -> moveBy(5, 0);
        if(pos().x() < 0 || pos().x() > 1000 || pos().y() < 0 || pos().y() > 600){
            emit deletebullet();
            this -> deleteLater();
            // qDebug() << "delete a pea!";
        }
    }
    else{
        this -> moveBy(0, 5);
        if(pos().x() < 0 || pos().x() > 1000 || pos().y() < 0 || pos().y() > 600){
            emit deletebullet();
            this -> deleteLater();
            // qDebug() << "delete a pea!";
        }
    }
}
int bulletPea::type() const
{
    return 11;
}

bulletPea::~bulletPea()
{
    delete bulletPeaMovie;
    delete bulletPeaExplodeMovie;
}
