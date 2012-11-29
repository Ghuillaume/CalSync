######################################################################
# Automatically generated by qmake (2.01a) Thu Nov 29 21:30:04 2012
######################################################################

QT += xml network webkit

INCLUDEPATH += ../qjson/include

linux* {
    LIBS += ../qjson/build/lib/libqjson.so
}

win32-g++ {
    LIBS += ../qjson/build/lib/qjson0.dll
}

win32-msvc* {
    LIBS += ../qjson/build/lib/qjson0.lib
}

macx* {
LIBS += -F../qjson/build/lib -framework qjson
}

TEMPLATE = app
TARGET = 
DEPENDPATH += . \
              headers/Controler \
              headers/Model \
              headers/Parser \
              headers/View \
              src/Controler \
              src/Model \
              src/Parser \
              src/View
INCLUDEPATH += . headers/Model headers/Controler headers/View headers/Parser

# Input
HEADERS += headers/Controler/Config.hpp \
           headers/Controler/Controler.hpp \
           headers/Controler/md5.hpp \
           headers/Model/common.h \
           headers/Model/Model.hpp \
           headers/Model/Slot.hpp \
           headers/Model/Time.hpp \
           headers/Parser/common.h \
           headers/Parser/Parser.hpp \
           headers/Parser/ParserCELCAT.hpp \
           headers/Parser/ParserGCal.hpp \
           headers/View/DateDialog.hpp \
           headers/View/SlotDialog.hpp \
           headers/View/View.hpp \
    headers/View/GoogleAccessDialog.hpp \
    headers/Controler/OAuth.hpp
SOURCES += main.cpp \
           src/Controler/Config.cpp \
           src/Controler/Controler.cpp \
           src/Controler/md5.cpp \
           src/Model/common.cpp \
           src/Model/Model.cpp \
           src/Model/Slot.cpp \
           src/Model/Time.cpp \
           src/Parser/Parser.cpp \
           src/Parser/ParserCELCAT.cpp \
           src/Parser/ParserGCal.cpp \
           src/View/DateDialog.cpp \
           src/View/SlotDialog.cpp \
           src/View/View.cpp \
    src/View/GoogleAccessDialog.cpp \
    src/Controler/OAuth.cpp
