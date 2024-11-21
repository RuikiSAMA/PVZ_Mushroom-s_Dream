#ifndef GRASSGROUNDSCENCE_H
#define GRASSGROUNDSCENCE_H
#include "carditem.h"
#include <QLabel>
#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QPropertyAnimation>
#include <QTimer>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QScrollBar>
#include <QGraphicsPixmapItem>
#include <QApplication>
#include <map>
#include <vector>
#include <utility>
#include <QRandomGenerator>
#include "peashooter.h"
#include "scaredmushroom.h"
#include "peashooter.h"
#include "bulletpea.h"
#include "star.h"
#include "bulletstar.h"
#include "twinpeashooter.h"
#include "doublepeashooter.h"
#include "triblepeashooter.h"
#include "redoublepeashooter.h"
#include "bulletrepea.h"
#include "clover.h"
#include "shovel.h"
#include "zombie.h"

const int kW = 82;
const int kH = 99;
// 草坪坐标： (105, 85)(843, 580)

class grassGroundScence : public QWidget
{
    Q_OBJECT
public:
    explicit grassGroundScence(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *event) override;
    void opening_Animation();
    void readyToSetPlant_Animation();
    void suspendGame();
    void continueGame();
    void grassClick(QPoint pos);
    void shovelClick(QPoint pos);
    void mousePressEvent(QMouseEvent *event) override;
    void returnCursor();
    void creatPlant(int, int);
    ~grassGroundScence();

signals:
    void OPEnd();
    void returnMainScene();

public slots:
    void gamestart();
    void creatCard();
    void changeCursor(int n, CardItme * card);
    void changeShovelCursor();
    void creatBulletPea(PeaShooter *);
    void creatBulletstar(Star *);
    void creat_TwoSide_BulletPea(TwinPeaShooter *);
    void creat_Double_BulletPea(DoublePeaShooter *);
    void creat_ReDouble_BulletPea(ReDoublePeaShooter *);
    void creat_Trible_BulletPea(TriblePeaShooter *);
    void creatZombie();
    void updateMap(QPointF);
    void reduceBulletNum();
    void gameover();

private:
    QLabel *optMenu;
    QTimer *advanceTimeLine;
    QTimer *cardTimeLine;
    QTimer *zombieTimeLine;
    QTimer *harderzombieTimeLine;
    QTimer *hardestzombieTimeLine;
    QVBoxLayout *grassLayout;
    QGraphicsView *grassView;
    QGraphicsScene *grassScene;
    CardItme *tempCard;
    shovel *pShovel;
    std::map<int, int> CardMap;   //  植物产出顺序表
    std::map<std::pair<int, int>, std::pair<int, Plant*>> posMap;   //  草坪站位表
    std::map<int, std::pair<int, int>> zombieMap;   //  僵尸产出顺序表
    static bool IsPressCard;
    static int nowChooseNum;
    bool IsCardDeleted;
    bool IsPressShovel;
    bool optMenuVisible;
    int cardZ;
    int cardNum;
    int i;
    int iZ;
    int bulletnum;
    int zombieNum;
    bool IsCreatBullet;
};

#endif // GRASSGROUNDSCENCE_H
