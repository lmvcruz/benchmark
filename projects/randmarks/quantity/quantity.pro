TEMPLATE = app
CONFIG += c++11
CONFIG -= app_bundle
#CONFIG -= qt

TARGET = quantity

ROOT_FOLDER = $$PWD/../../..
BUILD_FOLDER = $$ROOT_FOLDER/../build

OBJECTS_DIR = $$BUILD_FOLDER/$$TARGET
MOC_DIR = $$BUILD_FOLDER/$$TARGET
DESTDIR = $$BUILD_FOLDER/$$TARGET

SOURCES += \
        main.cpp

## Libraries
INCLUDEPATH += $$ROOT_FOLDER $$ROOT_FOLDER/.. $$ROOT_FOLDER/../ctk
DEPENDPATH += $$ROOT_FOLDER $$ROOT_FOLDER/.. $$ROOT_FOLDER/../ctk

LIBS += -L$$BUILD_FOLDER/libs -lctk
PRE_TARGETDEPS += $$BUILD_FOLDER/libs/libctk.a

LIBS += -L$$BUILD_FOLDER/libs -lfilesys
PRE_TARGETDEPS += $$BUILD_FOLDER/libs/libfilesys.a

INCLUDEPATH += $$PWD/../randmarks
DEPENDPATH += $$PWD/../randmarks
LIBS += -L$$BUILD_FOLDER/libs -lrandmarks
PRE_TARGETDEPS += $$BUILD_FOLDER/libs/librandmarks.a
