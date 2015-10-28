#Building directories configuration
#----------------------------------

unix                          { BUILD_PREFIX = linux32Gcc }
win32                         { BUILD_PREFIX = win32Gcc }
CONFIG(debug, debug|release)  { BUILD_SUFFIX = Debug }
                        else  { BUILD_SUFFIX =  }
BUILD_DIR = $$BUILD_PREFIX$$BUILD_SUFFIX

#---------------------------------------

DESTDIR = ./bin/$$BUILD_DIR
OBJECTS_DIR = ./obj/$$BUILD_DIR
MOC_DIR = ./obj/$$BUILD_DIR
RCC_DIR = ./obj/$$BUILD_DIR
UI_DIR = ./obj/$$BUILD_DIR

QMAKE_CXXFLAGS += -std=c++11

message($$TARGET: Building $$BUILD_DIR version.)
