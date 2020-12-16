QT       += core gui sql serialport printsupport network charts multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    client.cpp \
    connexion.cpp \
    dialog.cpp \
    invite.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    reservation.cpp \
    smtp.cpp \
    stats.cpp \
    table.cpp

HEADERS += \
    arduino.h \
    client.h \
    connexion.h \
    dialog.h \
    invite.h \
    login.h \
    mainwindow.h \
    reservation.h \
    smtp.h \
    stats.h \
    table.h

FORMS += \
    dialog.ui \
    mainwindow.ui \
    stats.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
