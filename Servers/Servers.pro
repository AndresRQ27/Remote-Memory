TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += activeserver.h \
           pasiveserver.h \
           server.h \

SOURCES += main.cpp \
           activeserver.cpp \
           pasiveserver.cpp \
           server.cpp \

