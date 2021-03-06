#-------------------------------------------------
#
# Project created by QtCreator 2019-05-24T10:21:32
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++0x

RC_ICONS = images/list.ico

TARGET = AgatImitator
TEMPLATE = app

win32 {
        RC_FILE += file.rc
        OTHER_FILES += file.rc
}

SOURCES += main.cpp\
        mainwindow.cpp \
    sg_comport.cpp \
    avrorasensor.cpp \
    sensorsettings.cpp

HEADERS  += mainwindow.h \
    sg_comport.h \
    avrorasensor.h \
    sensorsettings.h

FORMS    += mainwindow.ui

RESOURCES += \
    icons.qrc

#DISTFILES += file.rc
