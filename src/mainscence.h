#ifndef MAINSCENCE_H
#define MAINSCENCE_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class mainScience;
}
QT_END_NAMESPACE

class mainScience : public QWidget
{
    Q_OBJECT

public:
    mainScience(QWidget *parent = nullptr);
    ~mainScience();

    void paintEvent(QPaintEvent *) override;

signals:
    void rotateScence();    //  切换至游戏场景信号

private:
    QPoint cursorPos;

    Ui::mainScience *ui;
};
#endif // MAINSCENCE_H
