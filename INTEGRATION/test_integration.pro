QT       += core gui sql serialport printsupport network charts multimedia
QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    client.cpp \
    collaborateur.cpp \
    connexion.cpp \
    departement.cpp \
    dialog.cpp \
    excel.cpp \
    fournisseurs.cpp \
    historique.cpp \
    invite.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    personnel.cpp \
    produits.cpp \
    reservation.cpp \
    service.cpp \
    smtp.cpp \
    stat.cpp \
    stats.cpp \
    table.cpp

HEADERS += \
    arduino.h \
    client.h \
    collaborateur.h \
    connexion.h \
    departement.h \
    dialog.h \
    excel.h \
    fournisseurs.h \
    historique.h \
    invite.h \
    login.h \
    mainwindow.h \
    personnel.h \
    produits.h \
    reservation.h \
    service.h \
    smtp.h \
    stat.h \
    stats.h \
    table.h

FORMS += \
    dialog.ui \
    mainwindow.ui \
    stat.ui \
    stats.ui
     RC_ICONS = myappico.ico
    QMAKE_CXXFLAGS += -std=gnu++14
    QMAKE_CXXFLAGS += -std=gnu++11

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    histo.txt

RESOURCES += \
    res.qrc \
    son.qrc
