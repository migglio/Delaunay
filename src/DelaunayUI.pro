#-------------------------------------------------
#
# Project created by QtCreator 2016-11-30T16:15:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DelaunayUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    delaunay.cpp \
    triangulo.cpp \
    vertice.cpp \
    halfedge.cpp \
    dialog.cpp \
    dialogvor.cpp

HEADERS  += mainwindow.h \
    delaunay.h \
    triangulo.h \
    vertice.h \
    halfedge.h \
    dialog.h \
    dialogvor.h

FORMS    += mainwindow.ui \
    dialog.ui \
    dialogvor.ui
