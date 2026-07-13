QT += testlib
QT += widgets

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_matrixtest.cpp \
            ../functions.cpp \
            ../mainwindow.cpp \

HEADERS += ../functions.h \
            ../mainwindow.h \

FORMS += ../mainwindow.ui
