#-------------------------------------------------
#
# Project created by QtCreator 2020-09-07T11:12:12
#
#-------------------------------------------------

QT       += core gui network
QT       +=multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Six-Stone-Master-serve
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    gamemodel.cpp \
    server.cpp \
    selectform.cpp \
    chessboard.cpp \
    ai.cpp \
    gplayer.cpp

HEADERS += \
        mainwindow.h \
    gamemodel.h \
    server.h \
    selectform.h \
    database.hpp \
    chessboard.h \
    ai.h \
    gplayer.h

FORMS += \
        mainwindow.ui \
    selectform.ui \
    chessboard.ui

RESOURCES += \
    reso.qrc
