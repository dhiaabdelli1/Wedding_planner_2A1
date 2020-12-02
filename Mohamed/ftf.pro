QT       += core gui sql serialport printsupport network
QT       += core gui sql



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG += c++11
CONFIG +=console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    collaborateur.cpp \
    connection.cpp \
    dialog.cpp \
    main.cpp \
    mainwindow.cpp \
    service.cpp \
    smtp.cpp

HEADERS += \
    collaborateur.h \
    connection.h \
    dialog.h \
    mainwindow.h \
    service.h \
    smtp.h

FORMS += \
    dialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
