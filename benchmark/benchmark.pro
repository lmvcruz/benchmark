TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

TARGET = benchmark

ROOT_FOLDER = $$PWD/../
BUILD_FOLDER = $$ROOT_FOLDER/../build

OBJECTS_DIR = $$BUILD_FOLDER/$$TARGET
MOC_DIR = $$BUILD_FOLDER/$$TARGET
DESTDIR = $$BUILD_FOLDER/$$TARGET

SOURCES += \
        benchmarkengine.cpp \
        main.cpp

HEADERS += \
    benchmarkengine.h

## Libraries
INCLUDEPATH += $$ROOT_FOLDER $$ROOT_FOLDER/..
DEPENDPATH += $$ROOT_FOLDER $$ROOT_FOLDER/..

LIBS += -L$$BUILD_FOLDER/libs -lfilesys
PRE_TARGETDEPS += $$BUILD_FOLDER/libs/libfilesys.a


#LIBS += -L$$BUILD_FOLDER/libs -lbenchmarklib
#PRE_TARGETDEPS += $$BUILD_FOLDER/libs/libbenchmarklib.a
