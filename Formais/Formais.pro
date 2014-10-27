#-------------------------------------------------
#
# Project created by QtCreator 2014-10-12T02:16:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Formais
TEMPLATE = app


SOURCES += main.cpp\
           visaoautomato.cpp \
           estado.cpp \
    automato.cpp

HEADERS  += visaoautomato.h \
            estado.h \
    automato.h

FORMS    += visaoautomato.ui

QMAKE_CXXFLAGS += -std=c++11
