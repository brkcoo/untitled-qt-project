TEMPLATE = app
TARGET = untitled

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    gamewindow.cpp \
    main.cpp \
    minigame.cpp \
    pet.cpp

RESOURCES += \
    images.qrc

HEADERS += \
    gamewindow.h \
    minigame.h \
    pet.h \
    petlabel.h
