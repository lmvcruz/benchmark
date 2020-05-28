#CONFIG -= qt

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET = benchlib

ROOT_FOLDER = $$PWD/../
BUILD_FOLDER = $$ROOT_FOLDER/../build

OBJECTS_DIR = $$BUILD_FOLDER/$$TARGET
MOC_DIR = $$BUILD_FOLDER/$$TARGET
DESTDIR = $$BUILD_FOLDER/libs

SOURCES += \
    benchmarkengine.cpp \
    benchmarkevaluation.cpp \
    benchmarkprogram.cpp

HEADERS += \
    benchmarkengine.h \
    benchmarkevaluation.h \
    benchmarkprogram.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target


## Dependecies
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

unix:!macx {
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
}
macx: {
    QT_CONFIG -= no-pkg-config
    CONFIG += link_pkgconfig
    PKG_CONFIG = /usr/local/bin/pkg-config
    PKGCONFIG += opencv4
    PKGCONFIG += tesseract
    PKGCONFIG += zbar ilmbase
}


## Libraries
INCLUDEPATH += $$ROOT_FOLDER $$ROOT_FOLDER/.. $$ROOT_FOLDER/../ctk
DEPENDPATH += $$ROOT_FOLDER $$ROOT_FOLDER/.. $$ROOT_FOLDER/../ctk

LIBS += -L$$BUILD_FOLDER/libs -lctk
PRE_TARGETDEPS += $$BUILD_FOLDER/libs/libctk.a

LIBS += -L$$BUILD_FOLDER/libs -lfilesys
PRE_TARGETDEPS += $$BUILD_FOLDER/libs/libfilesys.a
