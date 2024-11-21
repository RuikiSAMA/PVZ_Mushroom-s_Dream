QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bulletpea.cpp \
    bulletrepea.cpp \
    bulletstar.cpp \
    carditem.cpp \
    clover.cpp \
    doublepeashooter.cpp \
    grassgroundscence.cpp \
    main.cpp \
    mainscence.cpp \
    mypushbutton.cpp \
    peashooter.cpp \
    plant.cpp \
    redoublepeashooter.cpp \
    scaredmushroom.cpp \
    shovel.cpp \
    star.cpp \
    triblepeashooter.cpp \
    twinpeashooter.cpp \
    venom.cpp \
    zombie.cpp

HEADERS += \
    bulletpea.h \
    bulletrepea.h \
    bulletstar.h \
    carditem.h \
    clover.h \
    doublepeashooter.h \
    grassgroundscence.h \
    mainscence.h \
    mypushbutton.h \
    peashooter.h \
    plant.h \
    redoublepeashooter.h \
    scaredmushroom.h \
    shovel.h \
    star.h \
    triblepeashooter.h \
    twinpeashooter.h \
    venom.h \
    zombie.h

FORMS += \
    mainscence.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES +=
