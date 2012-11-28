######################################################################
# Automatically generated by qmake (2.01a) Wed Nov 28 00:32:45 2012
######################################################################

QT += xml
TEMPLATE = app
TARGET = 
DEPENDPATH += . \
              headers/Controler \
              headers/Model \
              headers/Parser \
              headers/Publicator \
              headers/View \
              src/Controler \
              src/Model \
              src/Parser \
              src/Publicator \
              src/View
INCLUDEPATH += . headers/Model headers/Controler headers/View headers/Parser

# Input
HEADERS += headers/Controler/Config.hpp \
           headers/Controler/Controler.hpp \
           headers/Model/common.h \
           headers/Model/Model.hpp \
           headers/Model/Slot.hpp \
           headers/Model/Time.hpp \
           headers/Parser/common.h \
           headers/Parser/Parser.hpp \
           headers/Parser/ParserCELCAT.hpp \
           headers/Parser/ParserCELCATFactory.hpp \
           headers/Parser/ParserFactory.hpp \
           headers/Parser/ParserGCalFactory.hpp \
           headers/Publicator/Publicator.hpp \
           headers/Publicator/PublicatorFactory.hpp \
           headers/Publicator/PublicatorGCal.hpp \
           headers/Publicator/PublicatorGCalFactory.hpp \
           headers/View/DateDialog.hpp \
           headers/View/SlotDialog.hpp \
           headers/View/View.hpp
SOURCES += main.cpp \
           src/Controler/Config.cpp \
           src/Controler/Controler.cpp \
           src/Model/common.cpp \
           src/Model/Model.cpp \
           src/Model/Slot.cpp \
           src/Model/Time.cpp \
           src/Parser/Parser.cpp \
           src/Parser/ParserCELCAT.cpp \
           src/Parser/ParserCELCATFactory.cpp \
           src/Parser/ParserFactory.cpp \
           src/Parser/ParserGCalFactory.cpp \
           src/Publicator/Publicator.cpp \
           src/Publicator/PublicatorFactory.cpp \
           src/Publicator/PublicatorGCal.cpp \
           src/Publicator/PublicatorGCalFactory.cpp \
           src/View/DateDialog.cpp \
           src/View/SlotDialog.cpp \
           src/View/View.cpp