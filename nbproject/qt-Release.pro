# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Release/GNU-Linux-x86
TARGET = CalSync
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += release 
PKGCONFIG +=
QT = core gui
SOURCES += libs/ccard_r10/samples/ctest/test.c main/src/main.cpp libs/ccard_r10/cardparser.c libs/ccard_r10/samples/cpptest/test.cpp ICalcParser/src/ICalParser.cpp
HEADERS += ICalcParser/headers/ICalParser.h main/headers/common.h libs/ccard_r10/cardparser.h
FORMS +=
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Release/GNU-Linux-x86
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += 
LIBS += 
