#-------------------------------------------------
#
# Project created by QtCreator 2017-06-05T15:04:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PictureEditor
TEMPLATE = app


SOURCES += main.cpp\
        pemainwindow.cpp \
    pegraphicsscene.cpp \
    pegraphicsview.cpp \
    ctrlscenedialog.cpp \
    ctrlviewdialog.cpp

HEADERS  += pemainwindow.h \
    pegraphicsscene.h \
    pegraphicsview.h \
    ctrlscenedialog.h \
    ctrlviewdialog.h

FORMS    += pemainwindow.ui \
    ctrlscenedialog.ui \
    ctrlviewdialog.ui
