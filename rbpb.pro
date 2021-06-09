QT += core network
QT -= gui

CONFIG += c++11

TARGET = ./bin/rbpb
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app
INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib

SOURCES += main.cpp \
    Log.cpp \
    NtripArg.cpp \
    CasterRouter.cpp \
    SourceTable.cpp \
    UserTable.cpp \
    UserEntry.cpp \
    CasterEntry.cpp \
    SourceEntry.cpp \
    NetworkEntry.cpp \
    Args.cpp \
    Rbpb.cpp \
    ljephdata.cpp \
    ljrcvdatathread.cpp \
    ljlistenandcastthread.cpp \
    ljstatisticsendthread.cpp \
    ljauththread.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    stdafx.h \
    Common.h \
    Log.h \
    NtripArg.h \
    Queue.h \
    CasterRouter.h \
    SourceTable.h \
    UserTable.h \
    UserEntry.h \
    CasterEntry.h \
    SourceEntry.h \
    NetworkEntry.h \
    Args.h \
    Rbpb.h \
    ljephdata.h \
    ljrcvdatathread.h \
    ljlistenandcastthread.h \
    ljstatisticsendthread.h \
    ljauththread.h

DISTFILES += \
    new 1.txt

unix:!macx: LIBS += -L/usr/local/lib/ -levent_core

INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include

unix:!macx: PRE_TARGETDEPS += /usr/local/lib/libevent_core.a
