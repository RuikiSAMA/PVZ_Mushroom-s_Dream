#include "zombie.h"

Zombie::Zombie(int N, QGraphicsObject *parent)
    : QGraphicsObject{parent}
{
    setZValue(2);

    Num = N;
    HP = 100;
    ATK = 10;
    IsLiving = true;
    IsEating = false;
    qDebug() << "creat a zombie!";

    // zombieMovie = new QMovie(QString(":/res/Zombies/ZombieWalking%1.gif").arg(Num));
    zombieMovie = new QMovie(":/res/Zombies/ZombieWalking1.gif");
    if(!zombieMovie -> isValid())
        qDebug() << QString("QMovie :/res/Zombies/ZombieWalking%1.gif is not valid").arg(Num);

    zombieEatingMovie = new QMovie(QString(":/res/Zombies/ZombieEating%1.gif").arg(Num));
    if(!zombieEatingMovie -> isValid())
        qDebug() << QString("QMovie :/res/Zombies/ZombieEating%1.gif is not valid").arg(Num);

    zombieDieMovie = new QMovie(QString(":/res/Zombies/ZombieDying%1.gif").arg(Num));
    if(!zombieDieMovie -> isValid())
        qDebug() << QString("QMovie :/res/Zombies/ZombieDying%1.gif is not valid").arg(Num);

    zombieMovie -> start();
    zombieEatingMovie -> start();
}

QRectF Zombie::boundingRect() const
{
    return QRect(0, 0, 110, 125);
}

void Zombie::advance(int phase)
{
    if(!phase)
        return;
    QList <QGraphicsItem*> collideItems = collidingItems();
    for (QGraphicsItem* item : collideItems) {
        if(item -> type() == 1){
            PeaShooter* peashooter = qgraphicsitem_cast<PeaShooter*>(item);
            // qDebug() << "zombie collide with plant";
            IsEating = true;
            peashooter -> beHiting();
            if(this -> HP < 0)
                IsLiving = false;
            update();
            connect(peashooter, &PeaShooter::plantDie, this, [=](){
                IsEating = false;
            });
            return;
        }
        else if(item -> type() == 2){
            Star *star = qgraphicsitem_cast<Star*>(item);
            // qDebug() << "zombie collide with plant";
            IsEating = true;
            star -> beHiting();
            if(this -> HP < 0)
                IsLiving = false;
            update();
            connect(star, &Star::plantDie, this, [=](){
                IsEating = false;
            });
            return;
        }
        else if(item -> type() == 3){
            TwinPeaShooter *twps = qgraphicsitem_cast<TwinPeaShooter*>(item);
            // qDebug() << "zombie collide with plant";
            IsEating = true;
            twps -> beHiting();
            if(this -> HP < 0)
                IsLiving = false;
            update();
            connect(twps, &TwinPeaShooter::plantDie, this, [=](){
                IsEating = false;
            });
            return;
        }
        else if(item -> type() == 4){
            DoublePeaShooter *dps = qgraphicsitem_cast<DoublePeaShooter*>(item);
            // qDebug() << "zombie collide with plant";
            IsEating = true;
            dps -> beHiting();
            if(this -> HP < 0)
                IsLiving = false;
            update();
            connect(dps, &DoublePeaShooter::plantDie, this, [=](){
                IsEating = false;
            });
            return;
        }
        else if(item -> type() == 5){
            ReDoublePeaShooter *rdps = qgraphicsitem_cast<ReDoublePeaShooter*>(item);
            // qDebug() << "zombie collide with plant";
            IsEating = true;
            rdps -> beHiting();
            if(this -> HP < 0)
                IsLiving = false;
            update();
            connect(rdps, &ReDoublePeaShooter::plantDie, this, [=](){
                IsEating = false;
            });
            return;
        }
        else if(item -> type() == 6){
            TriblePeaShooter *tps = qgraphicsitem_cast<TriblePeaShooter*>(item);
            // qDebug() << "zombie collide with plant";
            IsEating = true;
            tps -> beHiting();
            if(this -> HP < 0)
                IsLiving = false;
            update();
            connect(tps, &TriblePeaShooter::plantDie, this, [=](){
                IsEating = false;
            });
            return;
        }
        else if(item -> type() == 8){
            Clover *clover = qgraphicsitem_cast<Clover*>(item);
            // qDebug() << "zombie collide with plant";
            IsEating = true;
            clover -> beHiting();
            if(this -> HP < 0)
                IsLiving = false;
            update();
            connect(clover, &Clover::plantDie, this, [=](){
                IsEating = false;
            });
            return;
        }
    }
    update();

    if(IsLiving)
        this -> moveBy(-0.3, 0);

    if(this -> HP < 0)
        IsLiving = false;

    if(this -> pos().x() < 90)
        emit gameover();
}

QPainterPath Zombie::shape() const
{
    QPainterPath path;
    path.addRect(QRect(38, 31, 32, 89));
    return path;
}

void Zombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(!IsEating && IsLiving){
        // painter->setPen(QPen(Qt::black, 0, Qt::SolidLine));
        // painter->setBrush(Qt::NoBrush);
        // painter->drawRect(boundingRect() + QMarginsF(-50,0,0,0));
        painter -> drawImage(boundingRect(), zombieMovie -> currentImage());
    }
    else if(IsEating && IsLiving)
        painter -> drawImage(boundingRect(), zombieEatingMovie -> currentImage());
    else if(!IsLiving){
        zombieDieMovie -> start();
        painter -> drawImage(QRectF(boundingRect()), zombieDieMovie -> currentImage());
        connect(zombieDieMovie, &QMovie::finished, this, &Zombie::deleteLater);
    }
}

int Zombie::type() const
{
    return 99;
}

bool Zombie::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    // 获取边界矩形
    if(other -> type() == 8){
        QRectF zombieRect = boundingRect() + QMarginsF(-50,0,0,0);
        QRectF otherRect = other-> boundingRect() + QMarginsF(0,-100,-80,-30);

        // 将两个矩形的位置转换为相同的坐标系
        zombieRect.translate(pos());
        otherRect.translate(other->pos());

        return zombieRect.intersects(otherRect);
    }
    else{
        QRectF zombieRect = boundingRect() + QMarginsF(-50,0,0,0);
        QRectF otherRect = other->boundingRect() + QMarginsF(0,0,0,-50);

        zombieRect.translate(pos());
        otherRect.translate(other->pos());

        return zombieRect.intersects(otherRect);
    }
}
