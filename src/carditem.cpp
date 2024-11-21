#include "carditem.h"

CardItme::CardItme(int n, int z, QGraphicsObject *parent)
{
    //  设置卡牌在最顶端出现的随机 x 坐标
    initCard(n, z);
    fallDownAnimation();
    // connect(cardTimer, &QTimer::timeout, this, &CardItme::fallDownAnimation);

    //  15s 后播放闪烁动画
    QTimer *flashTimer = new QTimer(this);
    flashTimer -> start(15000);
    connect(flashTimer ,&QTimer::timeout, this, &CardItme::startFlash);

    //  23s后自动删除
    QTimer *deleteTimer = new QTimer(this);
    deleteTimer -> start(23000);
    connect(deleteTimer ,&QTimer::timeout,[=](){
        emit thisHasDeleted();
        this -> deleteLater();
    });

    //  定时 10s 后产生闪烁动画  //  lambda函数、delete this可能导致崩溃，废弃
    // QTimer::singleShot(10000, [=](){
    //     QTimer *animationTimer = new QTimer(this);
    //     animationTimer -> start(1500);
    //     connect(animationTimer, &QTimer::timeout, this, &CardItme::soonDisappearAnimation);

    //     //  定时闪烁 6s 后删除卡牌
    //     QTimer::singleShot(6000, [=](){
    //         delete this; //  导致崩溃
    //     });
    // });
}

void CardItme::initCard(int n, int z)
{// 初始化卡牌
    //  设定卡牌序号
    Num = n;

    //  设定卡牌的 z 值
    setZValue(z);

    //  设定卡牌的随机 x 值
    randx = QRandomGenerator::global()->bounded(300, 900);

    //  设定当前可见性
    isVisible = true;

    //  设定卡牌初始 y 值为 0
    ypos = 0;
    bool ret = cardPixmap.load(QString(":/res/card%1.png").arg(Num));
    if(!ret)
        qDebug() << QString("faild to load :/res/card%1.png").arg(Num);
}

QRectF CardItme::boundingRect() const
{   //  设置绘制边框 (绘图会发生在边框内)
    qreal penwidth = 1;
    return QRectF(
        randx - penwidth / 2, ypos - penwidth / 2, cardPixmap.width(), cardPixmap.height());
}

void CardItme::advance(int phase)
{
    if(!phase)
        return;
    if(this -> pos().y() < 500){
        // qDebug() << "Item Move!";
        if(!cardClicked)
            this -> moveBy(0, 1);
    }
}

void CardItme::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{   //  重写绘制函数
    // qDebug() << "paint CardItem";
    // painter -> drawRect(boundingRect());
    painter -> drawPixmap(boundingRect().topLeft(), cardPixmap);
}

void CardItme::mousePressEvent(QGraphicsSceneMouseEvent *ev)
{   //  重写鼠标事件，左键单击卡牌发送信号 changeCursor()
    if(ev -> button() == Qt::LeftButton ){
//  .contains(QPointF) Returns true if the given point is inside or on the edge of the rectangle; otherwise returns false.
        cardClicked = true;
        IscardClicked = true;
        emit changeCursor(Num, this);
        qDebug() << "Clicked card";
    }
}

void CardItme::hideCard()
{   //  设置卡牌不可见
    this -> setVisible(false);
}

void CardItme::showCard()
{   //  设置卡牌可见
    this -> setVisible(true);
}

void CardItme::soonDisappearAnimation()
{   //  实现即将消失前的闪烁动画    //  废弃
    // this -> hideCard();
    // QTimer::singleShot(750,[=](){
    //     this -> showCard();
    // });

    // QTimer::singleShot(1500, [=](){
    //     delete SDATimer;
    // });
}

void CardItme::setInvisibel()
{
    isVisible = false;
}

void CardItme::setIsCardClicked()
{
    IscardClicked = false;
}

CardItme::~CardItme()
{
    qDebug() << QString("Delete a card '%1'").arg(Num);
}

void CardItme::fallDownAnimation()  //  废弃，更换策略：使用 advance() 实现动画
{   //  卡牌落下动画
    //  使用 QTimer 控制 update()重绘 实现动画,未知原因导致点击失效
    //  控制下落速度
    // if(ypos < 500)
    //     ypos ++;
    // update();

    //  使用 QPropertyAnimation 实现,无法实现收到信号暂停
    // QPropertyAnimation *fallDown = new QPropertyAnimation(this, "pos");
    // fallDown -> setDuration(7000);
    // fallDown -> setStartValue(pos());
    // fallDown -> setEndValue(QPointF(this -> pos().x(),this -> pos().y() + 500));
    // fallDown -> setEasingCurve(QEasingCurve::Linear);
    // fallDown -> start(QPropertyAnimation::DeleteWhenStopped);
}

void CardItme::startFlash()
{
    QTimer *periodTimer = new QTimer(this);
    periodTimer -> start(1000);
    connect(periodTimer, &QTimer::timeout, this, &CardItme::flashAnimation);
}

void CardItme::flashAnimation()
{
    if(isVisible && !IscardClicked)
        showCard();
    if(!isVisible && !IscardClicked)
        hideCard();
    isVisible = !isVisible;
}
