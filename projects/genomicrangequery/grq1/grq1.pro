TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
#CONFIG -= qt

TARGET = grq1

ROOT_FOLDER = $$PWD/../../..
BUILD_FOLDER = $$ROOT_FOLDER/build

OBJECTS_DIR = $$BUILD_FOLDER/$$TARGET
MOC_DIR = $$BUILD_FOLDER/$$TARGET
DESTDIR = $$BUILD_FOLDER/$$TARGET

SOURCES += \
        main.cpp

## Libraries
INCLUDEPATH += $$ROOT_FOLDER
DEPENDPATH += $$ROOT_FOLDER

LIBS += -L$$BUILD_FOLDER/libs -lstlaux
PRE_TARGETDEPS += $$BUILD_FOLDER/libs/libstlaux.a


LIBS += -L$$BUILD_FOLDER/libs -lbenchmarklib
PRE_TARGETDEPS += $$BUILD_FOLDER/libs/libbenchmarklib.a
