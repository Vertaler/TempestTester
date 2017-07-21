#-------------------------------------------------
#
# Project created by QtCreator 2017-07-11T19:16:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    testwindow.cpp \
    backgroundgenerator.cpp \
    bounded.cpp

HEADERS  += mainwindow.h \
    testwindow.h \
    testoptions.h \
    backgroundgenerator.h \
    bounded.h \
    utils.h

FORMS    += mainwindow.ui \
    testwindow.ui

