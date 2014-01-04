#-------------------------------------------------
#
# Project created by QtCreator 2014-01-01T18:24:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BootloaderGui
TEMPLATE = app
CONFIG += console

INCLUDEPATH += inc

SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/transferthread.cpp \
    src/bootloader.cpp

HEADERS  += inc/mainwindow.h \
    inc/transferthread.h \
    inc/libusbwrapper.h \
    inc/compat.h \
    inc/bootloader.h

win32 {
    message(Building with WinUSB support.)
    DEFINES += QWINUSB
    SOURCES  += src/qwinusb.cpp
    HEADERS  += inc/qwinusb.h
    RC_FILE = res/rc.rc
}
else {
    message(Building with LibUsb support.)
    SOURCES  += src/LibUsb.cpp
    HEADERS  += inc/LibUsb.h
    LIBS += -L"$$_PRO_FILE_PWD_/libs/" -llibusb
    INCLUDEPATH += $$_PRO_FILE_PWD_/libs
}

FORMS    += mainwindow.ui

RESOURCES += \
    res/ressources.qrc
