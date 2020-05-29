TEMPLATE = app
CONFIG += c++14
CONFIG -= app_bundle

TARGET = benchmark

ROOT_FOLDER = $$PWD/../
BUILD_FOLDER = $$ROOT_FOLDER/../build

OBJECTS_DIR = $$BUILD_FOLDER/$$TARGET
MOC_DIR = $$BUILD_FOLDER/$$TARGET
DESTDIR = $$BUILD_FOLDER/$$TARGET

SOURCES += \
        main.cpp

HEADERS += \


## Libraries
INCLUDEPATH += $$ROOT_FOLDER $$ROOT_FOLDER/.. $$ROOT_FOLDER/../ctk
DEPENDPATH += $$ROOT_FOLDER $$ROOT_FOLDER/../ctk

LIBS += -L$$BUILD_FOLDER/libs -lctk
PRE_TARGETDEPS += $$BUILD_FOLDER/libs/libctk.a

LIBS += -L$$BUILD_FOLDER/libs -lfilesys
PRE_TARGETDEPS += $$BUILD_FOLDER/libs/libfilesys.a


LIBS += -L$$BUILD_FOLDER/libs -lbenchlib
PRE_TARGETDEPS += $$BUILD_FOLDER/libs/libbenchlib.a

DISTFILES += \
    ../projects/primes/setup/bench1.json

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
