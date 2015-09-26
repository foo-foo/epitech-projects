#-------------------------------------------------
#
# Project created by QtCreator 2015-04-26T07:30:05
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cpp_plazza
TEMPLATE = app


SOURCES +=\
        mainwindow.cpp \
    glwidget.cpp \
    srcs/ScopedLock.cpp \
    srcs/Resources.cpp \
    srcs/Reception.cpp \
    srcs/Parser.cpp \
    srcs/Order.cpp \
    srcs/NamedPipe.cpp \
    srcs/Mutex.cpp \
    srcs/main.cpp \
    srcs/Kitchen.cpp \
    srcs/Cook.cpp \
    srcs/Command.cpp \
    main_ui.cpp \
    srcs/exceptions/RuntimeError.cpp \
    srcs/exceptions/PlazzaError.cpp \
    srcs/exceptions/BadCommandError.cpp \
    srcs/exceptions/ArgError.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    includes/ScopedLock.hpp \
    includes/SafeQueue.hpp \
    includes/RuntimeError.hpp \
    includes/Resources.hpp \
    includes/Reception.hpp \
    includes/PlazzaError.hpp \
    includes/Parser.hpp \
    includes/Order.hpp \
    includes/NamedPipe.hpp \
    includes/Mutex.hpp \
    includes/Kitchen.hpp \
    includes/IThread.hpp \
    includes/ISafeQueue.hpp \
    includes/IMutex.hpp \
    includes/Cook.hpp \
    includes/Command.hpp \
    includes/BadCommandError.hpp \
    includes/ArgError.hpp

FORMS    += \
    mainwindow.ui

LIBS += -lGL -lGLU -pthread
