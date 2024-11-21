#include "grassgroundscence.h"

bool grassGroundScence::IsPressCard = false;
int grassGroundScence::nowChooseNum = 0;

grassGroundScence::grassGroundScence(QWidget *parent)
    : QWidget{parent}
{
    zombieNum = 0;
    bulletnum = 0;
    IsCreatBullet = true;

    //  初始化植物顺序表
    // CardMap = {{1,1} ,{2,2} ,{3,1} ,{4,1} ,{5,2} ,
    //            {6,1} ,{7,4} ,{8,1} ,{9,2} ,{10,1},
    //            {11,1},{12,4},{13,2},{14,1},{15,4},
    //            {16,1},{17,2},{18,1},{19,1},{20,2},
    //            {21,1},{22,1},{23,2},{24,1},{25,5},
    //            {26,1},{27,2},{28,1},{29,1},{30,2},
    //            {31,1},{32,1},{33,2},{34,1},{35,1},
    //            {36,2},{37,1},{38,1},{39,2},{40,1},
    //            {41,1},{42,2},{43,1},{44,1},{45,2},
    //            {46,1},{47,1},{48,4},{49,2},{50,1},
    //            {51,1},{52,2},{53,1},{54,4},{55,1},
    //            {56,2},{57,1},{58,1},{59,2},{60,6},
    //            {61,1},{62,1},{63,7},{64,2},{65,1},
    //            {66,1},{67,2},{68,1},{69,1},{70,2},
    //            {71,1},{72,2}};

    CardMap = {{1,2} ,{2,4} ,{3,6} ,{4,4} ,{5,7} ,
               {6,2} ,{7,1} ,{8,6} ,{9,3} ,{10,4},
               {11,2},{12,1},{13,2},{14,3},{15,4},
               {16,1},{17,3},{18,1},{19,1},{20,2},
               {21,1},{22,1},{23,2},{24,1},{25,2},
               {26,1},{27,2},{28,1},{29,1},{30,2},
               {31,1},{32,1},{33,2},{34,1},{35,1},
               {36,2},{37,1},{38,1},{39,2},{40,1},
               {41,1},{42,2},{43,1},{44,1},{45,2},
               {46,1},{47,1},{48,4},{49,2},{50,1},
               {51,1},{52,2},{53,1},{54,4},{55,1},
               {56,2},{57,1},{58,1},{59,2},{60,6},
               {61,1},{62,1},{63,3},{64,2},{65,1},
               {66,1},{67,2},{68,1},{69,1},{70,2},
               {71,1},{72,2}};

    //  初始化僵尸表
    for(int i = 0; i < 100; i++){
        zombieMap[i].first = 2;     //  出现行数
        zombieMap[i].second = 0;    //  僵尸种类
    }

    //  初始化草坪站位表
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 5; j++){
            std::pair<int, int> temp{i, j};
            posMap[temp].first = 0;
            posMap[temp].second = nullptr;
        }
    }

    // for(int i = 0; i < 45; i++){
    //     Map[mapPos[i]] = 0;
    // }

    //  设定 cardZ 值
    cardZ = 2;
    cardNum = 0;

    //  临时卡牌指针赋空指针
    tempCard = nullptr;

    //  初始化窗口图标
    setWindowIcon(QIcon(":/res/brain.png"));

    //  初始化窗口标题
    setWindowTitle("Plants vs Zombies");

    //  初始化窗口大小
    setFixedSize(900, 600);

    //  初始化背景图
    grassScene = new QGraphicsScene(this);

    QPixmap grassBG(":/res/grass.png"); //  1400 * 600
    QGraphicsPixmapItem *grassBGItem = new QGraphicsPixmapItem;
    grassBGItem -> setPixmap(grassBG);
    grassBGItem -> setZValue(0);

    grassScene -> addItem(grassBGItem);
    grassScene -> setSceneRect(0, 0, 1400, 600);

    grassView = new QGraphicsView(grassScene);
    grassView -> setParent(this);
    grassView -> setGeometry(0, 0, 900, 600);
    grassView -> setFixedSize(900, 600);

    //  关闭滑动条
    grassView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    grassView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //  初始化选项菜单
    optMenu = new QLabel(this);
    optMenu -> setPixmap(QPixmap(":/res/OptionsMenuback32.png"));
    optMenu -> move(250,50);

    //  初始化选项菜单不可见
    optMenu -> hide();
    optMenuVisible = false;

    //  播放开场动画
    opening_Animation();

    //  当前卡牌是否被删除
    IsCardDeleted = false;

    //  收到 OPEnd() 信号后，执行 gamestart() 函数
    connect(this, &grassGroundScence::OPEnd, this, &grassGroundScence::gamestart);
    connect(tempCard, &CardItme::thisHasDeleted,[=](){
        // IsCardDeleted = true;
        // tempCard = nullptr;
        qDebug() << "tempCard has been deleted!";
    });

    ScaredMushroom *sm = new ScaredMushroom;
    sm -> setPos(265 + 1 * 82, 95 + 3 * 99);
    grassScene -> addItem(sm);
}

void grassGroundScence::keyPressEvent(QKeyEvent *event)
{   //  捕捉按下 esc 按键暂停游戏显示选项菜单
    qDebug() << event -> key();

    if(event -> key() == Qt::Key_Escape){
        qDebug() << "Pressed 'Esc'";
        if(optMenuVisible){
            optMenu -> hide();
            continueGame();
            optMenuVisible = false;
        }
        else{
            suspendGame();
            optMenu -> show();
            optMenuVisible = true;
        }
    }
}

void grassGroundScence::opening_Animation()
{

    qDebug() << "Load opening animation!";

    QScrollBar *horizontalScrollBar = grassView->horizontalScrollBar();

    //  定义向右滑动的动画
    QPropertyAnimation *rAnimation = new QPropertyAnimation(horizontalScrollBar, "value");

    // 设置动画持续时间
    rAnimation->setDuration(2000);

    // 设置动画开始时的滚动条位置
    rAnimation->setStartValue(0);

    // 设置动画结束时的滚动条位置
    rAnimation->setEndValue(500);

    // 设置动画曲线
    rAnimation->setEasingCurve(QEasingCurve::InOutQuad);

    // 启动动画，并在动画停止时删除动画对象
    rAnimation->start(QPropertyAnimation::DeleteWhenStopped);

    QTimer::singleShot(3200,[=](){
    //  定义向左滑动动画
        QPropertyAnimation *lAnimation = new QPropertyAnimation(horizontalScrollBar, "value");

        lAnimation -> setDuration(2000);

        lAnimation -> setStartValue(500);

        lAnimation -> setEndValue(150);

        lAnimation -> setEasingCurve(QEasingCurve::InOutQuad);

        lAnimation -> start(QPropertyAnimation::DeleteWhenStopped);
    });

    QTimer::singleShot(6300,[=](){
        readyToSetPlant_Animation();
    });
}

void grassGroundScence::readyToSetPlant_Animation()
{   //  用 QLabel 、singleShot 实现 3 帧的开场小动画
    QLabel *ready = new QLabel(this);
    QLabel *set = new QLabel(this);
    QLabel *plants = new QLabel(this);

    ready -> move(310,220);
    set -> move(310,220);
    plants -> move(310,220);

    ready -> setPixmap(QPixmap(":/res/ready.png"));
    set -> setPixmap(QPixmap(":/res/set.png"));
    plants -> setPixmap(QPixmap(":/res/plants!!.png"));

    ready->show();
    set->hide();
    plants->hide();

    QTimer::singleShot(800, [=](){
        ready->hide();
        set->show();
    });

    QTimer::singleShot(1600, [=](){
        set->hide();
        plants->show();
    });

    QTimer::singleShot(2400, [=](){
        plants->hide();

        //  在执行完开场动画后发送信号 OPEnd()
        emit OPEnd();
    });
}

void grassGroundScence::suspendGame()
{
    advanceTimeLine -> stop();
    cardTimeLine -> stop();
    zombieTimeLine -> stop();
    qDebug() << "suspend game!";
}

void grassGroundScence::continueGame()
{
    qDebug() << "continue game!";
    advanceTimeLine -> start(30);
    cardTimeLine -> start(5000);
    zombieTimeLine -> start(10000);
}

void grassGroundScence::mousePressEvent(QMouseEvent *event)
{
    if(event -> button() == Qt::LeftButton && IsPressCard){
        //  当前为点击状态时，再次点击调用 grassClick 函数，发送当前光标位置
        grassClick(event -> pos());

        //  维护卡牌点击状态
        IsPressCard = false;
    }

    if(event -> button() == Qt::LeftButton && IsPressShovel){
        //  当前为点击状态时，再次点击调用 shovelClick 函数，发送当前光标位置
        shovelClick(event -> pos());

        //  维护铲子点击状态
        IsPressShovel = false;
    }
}

void grassGroundScence::shovelClick(QPoint pos)
{
    qDebug() << pos;

    //  计算草坪位置
    int kSetPlantX = 0, kSetPlantY = 0;
    kSetPlantX = (pos.x() - 105) / 82;
    kSetPlantY = (pos.y() - 85) / 99;
    qDebug() << kSetPlantX << " " << kSetPlantY;

    if (pos.x() < 105 || pos.x() > 840 || pos.y() < 85 || pos.y() > 580
        || posMap[std::pair<int, int> (kSetPlantX, kSetPlantY)].first == 0){
        //  若所选位置无植物
        qDebug() << "this stock have no plant!";

        //  重置光标
        QApplication::restoreOverrideCursor();

        //  显示铲子
        pShovel -> show();
        return;
    }
    if(posMap[std::pair<int, int> (kSetPlantX, kSetPlantY)].first == 1){
        //  若所选位置有植物
        qDebug() << "shovel a plant!";

        //  删除该植物
        posMap[std::pair<int, int> (kSetPlantX, kSetPlantY)].second -> deleteLater();

        //  维护表
        posMap[std::pair<int, int> (kSetPlantX, kSetPlantY)].second = nullptr;
        posMap[std::pair<int, int> (kSetPlantX, kSetPlantY)].first = 0;

        //  重置光标
        QApplication::restoreOverrideCursor();

        //  显示铲子
        pShovel -> show();
        return;
    }
}

void grassGroundScence::returnCursor()
{
    //  重新显示卡牌
    if(!IsCardDeleted){
        tempCard -> showCard();
        tempCard -> setIsCardClicked();
    }
    else
        IsCardDeleted = false;

    //  重置光标
    QApplication::restoreOverrideCursor();
}

void grassGroundScence::grassClick(QPoint pos)
{
    if(pos.x() < 105 || pos.x() > 840 || pos.y() < 85 || pos.y() > 580){
        qDebug() << "Grass Outside Clicked";
        returnCursor();
    }
    else{
        qDebug() << pos;

        //  计算草坪位置
        int kSetPlantX = 0, kSetPlantY = 0;
        kSetPlantX = (pos.x() - 105) / 82;
        kSetPlantY = (pos.y() - 85) / 99;
        qDebug() << kSetPlantX << " " << kSetPlantY;

        if(posMap[std::pair<int, int> (kSetPlantX, kSetPlantY)].first == 1){
            //  若所选位置已经有植物了
            qDebug() << "this stock has been planted a plant!";
            returnCursor();
            return;
        }

        //  回收 tempCard 内存空间
        if(!IsCardDeleted){
            delete tempCard;
            tempCard = nullptr;
            IsCardDeleted = false;
        }

        //  恢复光标
        QApplication::restoreOverrideCursor();

        //  在点击位置创建新植物
        creatPlant(kSetPlantX, kSetPlantY);
    }
}

void grassGroundScence::creatPlant(int kX, int kY)
{
    //  维护草坪站位表
    posMap[std::pair<int, int> (kX, kY)].first = 1;

    //  新建植物项并添加到 grassScene 中
    switch(nowChooseNum){
        case 1:{
            PeaShooter *peaShooter = new PeaShooter(1);
            peaShooter -> setPos(265 + kX * 82, 99 + kY * 99);
            grassScene -> addItem(peaShooter);
            connect(peaShooter, &PeaShooter::shotBullet, this, &grassGroundScence::creatBulletPea);
            connect(peaShooter, &PeaShooter::plantDie, this, &grassGroundScence::updateMap);
            posMap[std::pair<int, int> (kX, kY)].second = peaShooter;
            break;
        }
        case 2:{
            Star *star = new Star(2);
            star -> setPos(260 + kX * 82, 99 + kY * 99);
            grassScene -> addItem(star);
            connect(star, &Star::shotBullet, this, &grassGroundScence::creatBulletstar);
            connect(star, &Star::plantDie, this, &grassGroundScence::updateMap);
            posMap[std::pair<int, int> (kX, kY)].second = star;
            break;
        }
        case 3:{
            TwinPeaShooter *twps = new TwinPeaShooter(3);
            twps -> setPos(250 + kX * 82, 99 + kY * 99);
            grassScene -> addItem(twps);
            connect(twps, &TwinPeaShooter::shotBullet, this, &grassGroundScence::creat_TwoSide_BulletPea);
            connect(twps, &TwinPeaShooter::plantDie, this, &grassGroundScence::updateMap);
            posMap[std::pair<int, int> (kX, kY)].second = twps;
            break;
        }
        case 4:{
            DoublePeaShooter *dps = new DoublePeaShooter(4);
            dps -> setPos(250 + kX * 82, 99 + kY * 99);
            grassScene -> addItem(dps);
            connect(dps, &DoublePeaShooter::shotBullet, this, &grassGroundScence::creat_Double_BulletPea);
            connect(dps, &DoublePeaShooter::plantDie, this, &grassGroundScence::updateMap);
            posMap[std::pair<int, int> (kX, kY)].second = dps;
            break;
        }
        case 5:{
            ReDoublePeaShooter *rdps = new ReDoublePeaShooter(5);
            rdps -> setPos(260 + kX * 82, 99 + kY * 99);
            grassScene -> addItem(rdps);
            connect(rdps, &ReDoublePeaShooter::shotBullet, this, &grassGroundScence::creat_ReDouble_BulletPea);
            connect(rdps, &ReDoublePeaShooter::plantDie, this, &grassGroundScence::updateMap);
            posMap[std::pair<int, int> (kX, kY)].second = rdps;
            break;
        }
        case 6:{
            TriblePeaShooter *tps = new TriblePeaShooter(6);
            tps -> setPos(260 + kX * 82, 99 + kY * 99);
            grassScene -> addItem(tps);
            connect(tps, &TriblePeaShooter::shotBullet, this, &grassGroundScence::creat_Trible_BulletPea);
            connect(tps, &TriblePeaShooter::plantDie, this, &grassGroundScence::updateMap);
            posMap[std::pair<int, int> (kX, kY)].second = tps;
            break;
        }
        case 7:{
            Clover *clover = new Clover(7);
            clover -> setPos(265 + kX * 82, 99 + kY * 99);
            grassScene -> addItem(clover);
            posMap[std::pair<int, int> (kX, kY)].second = clover;
            connect(clover, &Clover::plantDie, this, &grassGroundScence::updateMap);
            break;
        }
    }

    //  重置当前选中植物编号
    nowChooseNum = 0;
}

void grassGroundScence::creatBulletPea(PeaShooter *peashooter)
{
    // qDebug() << "creat a pea!";
    if(IsCreatBullet){
        bulletPea *pea = new bulletPea(peashooter);
        pea -> setPos(peashooter -> pos() + QPoint(31, 5));
        grassScene -> addItem(pea);

        bulletnum++;

        connect(pea, &bulletPea::deletebullet, this, &grassGroundScence::reduceBulletNum);

        if(bulletnum >= 500)
            IsCreatBullet = false;

        // qDebug() << bulletnum;
    }
}

void grassGroundScence::creatBulletstar(Star* s)
{
    // qDebug() << "Creat a star bullet!";
    if(IsCreatBullet){
        bulletStar *star = new bulletStar(s);
        star -> setPos(s -> pos() + QPoint(31, 5));
        grassScene -> addItem(star);
        bulletnum++;

        connect(star, &bulletStar::deletebullet, this, &grassGroundScence::reduceBulletNum);
        if(bulletnum >= 500)
            IsCreatBullet = false;

        // qDebug() << bulletnum;
    }
}

void grassGroundScence::creat_TwoSide_BulletPea(TwinPeaShooter *twps)
{
    // qDebug() << "Creat two_side_bulletPea!";
    if(IsCreatBullet){
        bulletPea *aheadPea = new bulletPea(twps);
        aheadPea -> setPos(twps -> pos() + QPoint(45, 6));
        grassScene -> addItem(aheadPea);

        bulletRePea *behindPea1 = new bulletRePea(twps);
        behindPea1 -> setPos(twps -> pos() + QPoint(-30, 5));
        grassScene -> addItem(behindPea1);

        connect(aheadPea, &bulletPea::deletebullet, this, &grassGroundScence::reduceBulletNum);

        connect(behindPea1, &bulletRePea::deletebullet, this, &grassGroundScence::reduceBulletNum);

        QTimer::singleShot(200, [=](){
            bulletRePea *behindPea2 = new bulletRePea(twps);
            behindPea2 -> setPos(twps -> pos() + QPoint(-30, 5));
            grassScene -> addItem(behindPea2);

            connect(behindPea2, &bulletRePea::deletebullet, this, &grassGroundScence::reduceBulletNum);
        });

        bulletnum += 3;
        if(bulletnum >= 500)
            IsCreatBullet = false;

        // qDebug() << bulletnum;
    }
}

void grassGroundScence::creat_Double_BulletPea(DoublePeaShooter *dps)
{
    if(IsCreatBullet){
        bulletPea *Pea1 = new bulletPea(dps);
        Pea1 -> setPos(dps -> pos() + QPoint(31, 5));
        grassScene -> addItem(Pea1);

        QTimer::singleShot(200, [=](){
            bulletPea *Pea2 = new bulletPea(dps);
            Pea2 -> setPos(dps -> pos() + QPoint(31, 5));
            grassScene -> addItem(Pea2);

            connect(Pea2, &bulletPea::deletebullet, this, &grassGroundScence::reduceBulletNum);
        });

        connect(Pea1, &bulletPea::deletebullet, this, &grassGroundScence::reduceBulletNum);


        bulletnum += 2;

        if(bulletnum >= 500)
            IsCreatBullet = false;

        // qDebug() << bulletnum;
    }
}

void grassGroundScence::creat_ReDouble_BulletPea(ReDoublePeaShooter *rdps)
{
    if(IsCreatBullet){
        bulletRePea *behindPea1 = new bulletRePea(rdps);
        behindPea1 -> setPos(rdps -> pos() + QPoint(-30, 5));
        grassScene -> addItem(behindPea1);

        QTimer::singleShot(200, [=](){
            bulletRePea *behindPea2 = new bulletRePea(rdps);
            behindPea2 -> setPos(rdps -> pos() + QPoint(-30, 5));
            grassScene -> addItem(behindPea2);

            connect(behindPea2, &bulletRePea::deletebullet, this, &grassGroundScence::reduceBulletNum);
        });

        connect(behindPea1, &bulletRePea::deletebullet, this, &grassGroundScence::reduceBulletNum);

        bulletnum += 2;

        if(bulletnum >= 500)
            IsCreatBullet = false;

        // qDebug() << bulletnum;
    }
}

void grassGroundScence::creat_Trible_BulletPea(TriblePeaShooter *tps)
{
    if(IsCreatBullet){
        bulletPea *Pea1 = new bulletPea(tps);
        Pea1 -> setPos(tps -> pos() + QPoint(31, 5 - 99));
        grassScene -> addItem(Pea1);

        bulletPea *Pea2 = new bulletPea(tps);
        Pea2 -> setPos(tps -> pos() + QPoint(31, 5));
        grassScene -> addItem(Pea2);

        bulletPea *Pea3 = new bulletPea(tps);
        Pea3 -> setPos(tps -> pos() + QPoint(31, 5 + 99));
        grassScene -> addItem(Pea3);

        connect(Pea1, &bulletPea::deletebullet, this, &grassGroundScence::reduceBulletNum);

        connect(Pea2, &bulletPea::deletebullet, this, &grassGroundScence::reduceBulletNum);

        connect(Pea3, &bulletPea::deletebullet, this, &grassGroundScence::reduceBulletNum);

        bulletnum += 3;

        if(bulletnum >= 500)
            IsCreatBullet = false;

        // qDebug() << bulletnum;
    }
}

void grassGroundScence::updateMap(QPointF pos)
{
    int kSetPlantX = 0, kSetPlantY = 0;
    kSetPlantX = (pos.x() - 105) / 82 - 1;
    kSetPlantY = (pos.y() - 85) / 99;
    qDebug() << kSetPlantX << " " << kSetPlantY << " plant die!";
    posMap[std::pair<int, int> (kSetPlantX, kSetPlantY)].first = 0;
    posMap[std::pair<int, int> (kSetPlantX, kSetPlantY)].second = nullptr;
}

void grassGroundScence::reduceBulletNum()
{
    // qDebug() << "bullet Num reduce :" << bulletnum;
    IsCreatBullet = true;
    bulletnum--;
}

void grassGroundScence::creatZombie()
{
    // qDebug() << "creat a zombie!";

    // 生成 0 到 2 的随机数
    int randomIndex = QRandomGenerator::global() -> bounded(3);

    Zombie *zombie = new Zombie(1/*zombieMap[iZ].Second*/);
    zombie -> setPos(1100, 55 + kH * randomIndex);
    grassScene -> addItem(zombie);
    connect(zombie, &Zombie::gameover, this, &grassGroundScence::gameover);
    iZ++;
    zombieNum++;
    if(zombieNum == 12){
        harderzombieTimeLine = new QTimer(this);
        harderzombieTimeLine -> start(8000);
        connect(harderzombieTimeLine, &QTimer::timeout, this, &grassGroundScence::creatZombie);
    }
    if(zombieNum == 64){
        hardestzombieTimeLine = new QTimer(this);
        hardestzombieTimeLine -> start(4000);
        connect(hardestzombieTimeLine, &QTimer::timeout, this, &grassGroundScence::creatZombie);
    }
}

void grassGroundScence::gamestart()
{// 创建 卡牌 与 僵尸
    qDebug() << "game start!";

    //  初始化 advance 定时器， advance 定时器设置值为帧间隔
    advanceTimeLine = new QTimer(this);
    advanceTimeLine -> start(30);

    //  初始化生成卡牌定时器
    QTimer::singleShot(5000, this, &grassGroundScence::creatCard);
    cardTimeLine = new QTimer;
    cardTimeLine -> start(16000);
    // cardTimeLine -> start(5000);
    i = 1;

    //  初始化铲子槽
    QGraphicsPixmapItem *shovelSlotItem = new QGraphicsPixmapItem(QPixmap(":/res/shovelSlot.png"));
    shovelSlotItem -> setScale(1.5);
    shovelSlotItem -> setPos(650, 0);
    grassScene -> addItem(shovelSlotItem);

    //  初始化铲子
    shovel *sh = new shovel;
    sh -> setPos(660, 10);
    grassScene -> addItem(sh);
    pShovel = sh;

    //  初始化僵尸定时器
    zombieTimeLine = new QTimer(this);
    zombieTimeLine -> start(10000);
    iZ = 0;

    //  初始化铲子点击状态
    IsPressShovel = false;

    //  连接改变铲子函数
    connect(sh, &shovel::changeCursor, this, &grassGroundScence::changeShovelCursor);

    //  连接生成卡牌定时器与生成卡牌槽函数
    connect(cardTimeLine, &QTimer::timeout, this, &grassGroundScence::creatCard);

    //  连接 advance 定时器与 grassSecene 的 advance 函数
    connect(advanceTimeLine, &QTimer::timeout, grassScene, &QGraphicsScene::advance);

    //  连接僵尸定时器和生成僵尸槽函数
    connect(zombieTimeLine, &QTimer::timeout, this, &grassGroundScence::creatZombie);
}

void grassGroundScence::creatCard()
{// 创建一张新卡牌，并将其添加到场景中
    qDebug() << "creat a new card";
    CardItme *card = new CardItme(CardMap[i], cardZ);

    //  维护卡牌序号
    i++;

    //  维护新一张卡牌的 z value
    cardZ++;

    //  维护卡牌数量
    cardNum++;

    //  添加卡牌到 grassScene 中
    grassScene -> addItem(card);

    //  连接 点击卡牌后产生的改变光标信号 到 改变光标槽函数
    connect(card, &CardItme::changeCursor, this, &grassGroundScence::changeCursor);
}

void grassGroundScence::changeCursor(int n, CardItme * card)
{
    //  设置点击的植物编号为当前选择的植物编号
    nowChooseNum = n;

    //  隐藏卡牌
    card -> hideCard();

    //  存储当前选择卡牌的指针
    tempCard = card;

    // delete card;    //  点击卡牌后直接删除，意味着卡牌的安放不能失误

    //  设定目前为点击卡牌状态
    IsPressCard = true;

    //  加载指针Pixmap
    QPixmap cardPlantPix;
    bool ret = cardPlantPix.load(QString(":/res/cardplant%1.png").arg(n));
    if(ret)
        qDebug() << QString("load :/res/cardplant%1.png").arg(n);

    //  改变光标样式
    QCursor cursor(cardPlantPix);
    QApplication::setOverrideCursor(cursor);
}

void grassGroundScence::changeShovelCursor()
{
    //  设定为点击铲子状态
    IsPressShovel = true;

    //  隐藏铲子
    pShovel -> hide();

    //  加载指针Pixmap
    QPixmap shovelCursorPix;
    bool ret = shovelCursorPix.load(":/res/shovelCursor.png");
    if(ret)
        qDebug() << "load :/res/shovelCursor.png";

    //  改变光标样式
    QCursor cursor(shovelCursorPix);
    QApplication::setOverrideCursor(cursor);
}

void grassGroundScence::gameover()
{
    qDebug() << "gameover!";
    QGraphicsPixmapItem *gameoverItem = new QGraphicsPixmapItem(QPixmap(":/res/gameover.png"));
    // gameoverItem -> setScale(1.5);
    gameoverItem -> setPos(300, 100);
    grassScene -> addItem(gameoverItem);

    advanceTimeLine -> stop();
    cardTimeLine -> stop();
    zombieTimeLine -> stop();

    // emit returnMainScene();
}

grassGroundScence::~grassGroundScence()
{

}
