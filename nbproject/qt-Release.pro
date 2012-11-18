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
SOURCES += Parser/src/ParserCELCATFactory.cpp Parser/src/ParserFactory.cpp main/src/main.cpp Parser/src/ParserCELCAT.cpp Parser/src/Parser.cpp Parser/src/ParserGCalFactory.cpp Calendar.core/src/Time.cpp Calendar.core/src/Model.cpp
HEADERS += Parser/headers/ParserCELCATFactory.h Parser/headers/ParserGCalFactory.h Parser/headers/ParserCELCAT.h Calendar.core/headers/Time.h Parser/headers/Parser.h Parser/headers/ParserFactory.h main/headers/common.h Calendar.core/headers/Model.h
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
