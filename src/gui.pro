#
#  @file       gui.pro
#  @authors    Andrej Nano (xnanoa00), Stanislav Mechl (xmechl00)
#  @date       2018-05-05
#  @version    1.0
# 
#  @brief ICP 2018, Project - Block Editor. GUI Qt project.

QT       += core gui widgets

CONFIG += c++14 strict_c++

# for mac-os-x, forbid creation of app subdirectories
CONFIG -= app_bundle

TARGET = ../blockeditor
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
        blocks.cc \
        blockview.cc \
        loader.cc \
        main-gui.cc \
        mainwindow.cc \
        port.cc \
        scheduler.cc \
        scheme.cc \
        utilities.cc \
        wireview.cc \
        portview.cc


HEADERS += \
        blocks.h \
        blockview.h \
        loader.h \
        mainwindow.h \
        port.h \
        scheduler.h \
        scheme.h \
        utilities.h \
        wireview.h \
        portview.h

FORMS += \
        mainwindow.ui
