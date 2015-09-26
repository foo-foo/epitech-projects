#-------------------------------------------------
#
# Project created by QtCreator 2015-05-18T09:23:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bomberman
TEMPLATE = app


SOURCES += \
    Menu/home.cpp \
    Menu/launcher.cpp \
    Menu/main.cpp \
    Menu/mainwindow.cpp \
    Menu/options.cpp \
    Core/Srcs/ABonus.cpp \
    Core/Srcs/AObject.cpp \
    Core/Srcs/APlayer.cpp \
    Core/Srcs/Block.cpp \
    Core/Srcs/Bomb.cpp \
    Core/Srcs/BombEngine.cpp \
    Core/Srcs/BonusBomb.cpp \
    Core/Srcs/BonusPower.cpp \
    Core/Srcs/BonusSpeed.cpp \
    Core/Srcs/Bot.cpp \
    Core/Srcs/Box.cpp \
    Core/Srcs/Character.cpp \
    Core/Srcs/Decode.cpp \
    Core/Srcs/Field.cpp \
    Core/Srcs/Flame.cpp \
    Core/Srcs/GameEngine.cpp \
    Core/Srcs/Ground.cpp \
    Core/Srcs/Human.cpp \
    Core/Srcs/Legend.cpp \
    Core/Srcs/Monster.cpp \
    Core/Srcs/Recruit.cpp \
    Core/Srcs/Soldier.cpp \
    Core/Srcs/Teub.cpp \
    Core/Srcs/Undecided.cpp \
    Core/Srcs/Wall.cpp \
    Core/Srcs/Warrior.cpp \
    Menu/mapeditor.cpp \
    Menu/scores.cpp \
    Menu/Opt.cpp

HEADERS  += \
    Menu/home.hpp \
    Menu/launcher.hpp \
    Menu/mainwindow.hpp \
    Menu/options.hpp \
    Core/Headers/ABonus.hpp \
    Core/Headers/AObject.hpp \
    Core/Headers/APlayer.hpp \
    Core/Headers/Block.hpp \
    Core/Headers/Bomb.hpp \
    Core/Headers/BombEngine.hpp \
    Core/Headers/BonusBomb.hpp \
    Core/Headers/BonusPower.hpp \
    Core/Headers/BonusSpeed.hpp \
    Core/Headers/Bot.hpp \
    Core/Headers/Box.hpp \
    Core/Headers/Character.hpp \
    Core/Headers/Decode.hpp \
    Core/Headers/Field.hpp \
    Core/Headers/Flame.hpp \
    Core/Headers/GameEngine.hpp \
    Core/Headers/Ground.hpp \
    Core/Headers/Human.hpp \
    Core/Headers/IThread.hpp \
    Core/Headers/Legend.hpp \
    Core/Headers/Monster.hpp \
    Core/Headers/Recruit.hpp \
    Core/Headers/Soldier.hpp \
    Core/Headers/Teub.hpp \
    Core/Headers/Thread.hpp \
    Core/Headers/Undecided.hpp \
    Core/Headers/Wall.hpp \
    Core/Headers/Warrior.hpp \
    ui_home.h \
    ui_launcher.h \
    ui_mainwindow.h \
    ui_options.h \
    Menu/mapeditor.hpp \
    Menu/scores.hpp \
    Menu/Opt.hpp

FORMS    += Menu/home.ui \
    Menu/launcher.ui \
    Menu/mainwindow.ui \
    Menu/options.ui \
    Menu/mapeditor.ui \
    Menu/scores.ui

RESOURCES += Menu/bomberressources.qrc

INCLUDEPATH += -I ./LibBomberman_linux_x64/includes/

LIBS += -L ./LibBomberman_linux_x64/libs/ -lgdl_gl -lGL -lGLEW -lfbxsdk -lSDL2 -lm -ldl -lrt -lpthread -W -Wall -Wextra -g3 -lsfml-audio


INCLUDEPATH += ./Menu/ ./Core/Headers/

QMAKE_CXXFLAGS += -std=c++11
