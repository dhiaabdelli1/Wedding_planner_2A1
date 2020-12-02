QT       += core gui sql network multimedia multimediawidgets charts printsupport
QT       += core gui sql
    quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    client.cpp \
    connection.cpp \
    main.cpp \
    mainwindow.cpp \
    reservation.cpp \
    smtp.cpp \
    stat_combo.cpp

HEADERS += \
    client.h \
    connection.h \
    mainwindow.h \
    reservation.h \
    smtp.h \
    stat_combo.h

FORMS += \
    mainwindow.ui \
    stat_combo.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
