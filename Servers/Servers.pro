TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -pthread


HEADERS += activeserver.h \
           pasiveserver.h \
           server.h \

SOURCES += main.cpp \
           activeserver.cpp \
           pasiveserver.cpp \
           server.cpp \


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../rmlib/release/ -lrmlib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../rmlib/debug/ -lrmlib
else:unix: LIBS += -L$$OUT_PWD/../rmlib/ -lrmlib

INCLUDEPATH += $$PWD/../rmlib
DEPENDPATH += $$PWD/../rmlib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../rmlib/release/librmlib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../rmlib/debug/librmlib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../rmlib/release/rmlib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../rmlib/debug/rmlib.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../rmlib/librmlib.a
