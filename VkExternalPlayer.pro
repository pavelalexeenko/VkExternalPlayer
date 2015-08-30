#-------------------------------------------------
#
# Project created by QtCreator 2015-08-12T11:15:54
#
#-------------------------------------------------
TARGET = VkExternalPlayer
TEMPLATE = app

QT       += core gui widgets multimedia webkitwidgets

SOURCES += main.cpp\
        mainwindow.cpp \
    musicplayerwidget.cpp \
    vk/objects/audioitem.cpp \
    vk/instancefactory.cpp \
    vk/services/audioservice.cpp \
    vk/vklogindialog.cpp \
    vk/services/loginservice.cpp

HEADERS  += mainwindow.h \
    musicplayerwidget.h \
    vk/objects/audioitem.h \
    vk/instancefactory.h \
    vk/services/audioservice.h \
    vk/vklogindialog.h \
    vk/services/loginservice.h
