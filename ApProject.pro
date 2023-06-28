QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chatclient.cpp \
    confirmlogout.cpp \
    homepage.cpp \
    info.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    signupdialog.cpp

HEADERS += \
    chatclient.h \
    confirmlogout.h \
    homepage.h \
    info.h \
    logindialog.h \
    mainwindow.h \
    overload.h \
    signupdialog.h

FORMS += \
    confirmlogout.ui \
    homepage.ui \
    logindialog.ui \
    mainwindow.ui \
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
