QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QT += quick
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chatclient.cpp \
    confirmlogout.cpp \
    createchannelname.cpp \
    creategroupname.cpp \
    homepage.cpp \
    info.cpp \
    joinchannelname.cpp \
    joingroupname.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    newchatusername.cpp \
    signupdialog.cpp \
    tokenuser.cpp

HEADERS += \
    chatclient.h \
    confirmlogout.h \
    createchannelname.h \
    creategroupname.h \
    homepage.h \
    info.h \
    joinchannelname.h \
    joingroupname.h \
    logindialog.h \
    mainwindow.h \
    newchatusername.h \
    overload.h \
    signupdialog.h \
    tokenuser.h

FORMS += \
    confirmlogout.ui \
    createchannelname.ui \
    creategroupname.ui \
    homepage.ui \
    joinchannelname.ui \
    joingroupname.ui \
    logindialog.ui \
    mainwindow.ui \
    newchatusername.ui \
    signupdialog.ui

QT += network

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    confirm.qrc \
    image.qrc
