#include "bulletstar.h"


bulletStar::bulletStar(Plant *plant, QGraphicsObject *parent)
    : QGraphicsObject {parent}, originPlant {plant}
{
    ATK = 15;

    IsDeflection = true;

    angle = M_PI / 100;
    R = 150;

    IsH = false;

    currentAngle = 0;

    setZValue(1);

    bulletMovie = new QMovie(":/res/bullet/bulletStar.gif");
    if(!bulletMovie -> isValid())
        qDebug() << ":/res/bullet/bulletStar.gif is not valid";
    bulletMovie -> start();

    // bulletPeaExplodeMovie = new QMovie(":/res/bullet/BulletPeaExplode.gif");
    // if(!bulletPeaExplodeMovie -> isValid())
    //     qDebug() << ":/res/bullet/BulletPeaExplode.gif is not valid";
    // bulletPeaExplodeMovie -> start();
}

void bulletStar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter -> drawImage(boundingRect(), bulletMovie -> currentImage());
}

QRectF bulletStar::boundingRect() const
{
    return QRect(0, 0, 29, 30);
}

bool bulletStar::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    // 获取边界
    QPainterPath otherShape = other->shape();

    // 相交检测
    if (shape().intersects(otherShape.translated(other->pos() - pos())))
        return true;
    else
        return false;
}

void bulletStar::advance(int phase)
{
    if(phase){
        return;
    }

    QList <QGraphicsItem*> collideItems = collidingItems();
    for (QGraphicsItem* item : collideItems) {
        if(item -> type() == 1){
            PeaShooter* peashooter = qgraphicsitem_cast<PeaShooter*>(item);
            peashooter -> shot();
            emit deletebullet();
            this -> deleteLater();
        }        
        else if(item -> type() == 2 && item != originPlant){
            Star* star = qgraphicsitem_cast<Star*>(item);
            star -> shot();
            this -> deleteLater();
        }
        else if(item -> type() == 3){
            // qDebug() << "Pea collide with TwinPeaShooter!";
            TwinPeaShooter *twps = qgraphicsitem_cast<TwinPeaShooter*>(item);
            twps -> shot();
            emit deletebullet();
            this -> deleteLater();
        }
        else if(item -> type() == 4){
            // qDebug() << "Pea collide with DoublePeaShooter!";
            DoublePeaShooter *dps = qgraphicsitem_cast<DoublePeaShooter*>(item);
            dps -> shot();
            emit deletebullet();
            this -> deleteLater();
        }
        else if(item -> type() == 5){
            // qDebug() << "Pea collide with ReDoublePeaShooter!";
            ReDoublePeaShooter *rdps = qgraphicsitem_cast<ReDoublePeaShooter*>(item);
            rdps -> shot();
            emit deletebullet();
            this -> deleteLater();
        }
        else if(item -> type() == 6){
            // qDebug() << "Pea collide with TriblePeaShooter!";
            TriblePeaShooter *tps = qgraphicsitem_cast<TriblePeaShooter*>(item);
            tps -> shot();
            emit deletebullet();
            this -> deleteLater();
        }
        else if(item -> type() == 8){
            if(IsDeflection){
                center = this -> pos() + QPointF(-150, 0);
                IsDeflection = false;
                IsH = true;
            }
            if(currentAngle < M_PI / 2){
                currentAngle += angle;
                qreal dx = R * std::cos(currentAngle);
                qreal dy = R * std::sin(currentAngle);
                this -> setPos(center + QPointF(dx, -dy));
                // update();
                return;
            }
        }
        else if (item -> type() == 99) {
            Zombie* zombie = qgraphicsitem_cast<Zombie*>(item);
            zombie -> HP -= ATK;
            emit deletebullet();
            this -> deleteLater();
        }
    }
    update();

    if(IsH == false){
        this -> moveBy(0, -5);
        if(pos().x() < 0 || pos().x() > 1000 || pos().y() < 0 || pos().y() > 600){
            emit deletebullet();
            this -> deleteLater();
            qDebug() << "delete a star_bullet!";
        }
    }
    else{
        this -> moveBy(-5, 0);
        if(pos().x() < 0 || pos().x() > 1000 || pos().y() < 0 || pos().y() > 600){
            emit deletebullet();
            this -> deleteLater();
            // qDebug() << "delete a star_bullet!";
        }
    }
}

int bulletStar::type() const
{
    return 12;
}


bulletStar::~bulletStar()
{
    delete bulletMovie;
}
