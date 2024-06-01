QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    TimeManage.cpp \
    login.cpp \
    mainwindowadmin.cpp \
    menu.cpp \
    regi.cpp \
    sqlite3.c \
    AccessDB.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    TimeManage.h \
    login.h \
    mainwindowadmin.h \
    menu.h \
    regi.h \
    sqlite3.h \
    AccessDB.h \
    mainwindow.h

FORMS += \
    login.ui \
    mainwindow.ui \
    mainwindowadmin.ui \
    menu.ui \
    regi.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
