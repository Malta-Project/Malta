QT       += core gui
QT += widgets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    about.cpp \
    integration.cpp \
    main.cpp \
    mainwindow.cpp \
    ../../src/malta.cpp \
    ../../src/math.cpp

HEADERS += \
    about.h \
    integration.h \
    mainwindow.h

FORMS += \
    about.ui \
    integration.ui \
    mainwindow.ui

TRANSLATIONS += \
    Malta2_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../../../../Downloads/splash.png \
    splash.png

QMAKE_CXXFLAGS += -O3
QMAKE_CFLAGS += -O3