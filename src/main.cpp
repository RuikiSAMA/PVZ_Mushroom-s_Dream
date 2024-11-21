#include "mainscence.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainScience game;
    game.show();
    return a.exec();
}
