#-------------------------------------------------
#
# Project created by QtCreator 2016-06-02T17:54:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = two_gl_widgets_half_fps_testcase
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    GL_QGraphicsView.cpp \
    FPSCounter.cpp \
    logo.cpp \
    LogoGLWidget.cpp

HEADERS  += MainWindow.h \
    GL_QGraphicsView.h \
    FPSCounter.h \
    logo.h \
    LogoGLWidget.h

DISTFILES += \
    README.md
