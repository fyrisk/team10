QT       += core gui\
network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    boardwidget.cpp \
    gamewidget.cpp \
    gomokuai.cpp \
    network/networkdata.cpp \
    network/networkserver.cpp \
    network/networksocket.cpp \
    main.cpp \
    readydialog.cpp \
    settingswindow.cpp

HEADERS += \
    boardwidget.h \
    gomokuai.h \
    network/networkdata.h \
    network/networkserver.h \
    network/networksocket.h \
    gamewidget.h \
    readydialog.h \
    settingswindow.h

FORMS += \
    boardwidget.ui \
    gamewidget.ui \
    settingswindow.ui
TRANSLATIONS += \
    team10_nogo_test03_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
