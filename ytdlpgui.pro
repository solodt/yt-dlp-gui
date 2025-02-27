QT       += core gui core5compat concurrent
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++17
QMAKE_LFLAGS += -static -static-libgcc
VERSION=1.2

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    options.cpp

HEADERS += \
    functions.h \
    mainwindow.h \
    options.h


FORMS += \
    mainwindow.ui \
    options.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin

RC_ICONS = icon.ico

DISTFILES +=

RESOURCES += \
    resources.qrc


