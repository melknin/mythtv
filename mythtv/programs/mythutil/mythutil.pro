include ( ../../settings.pro )
include ( ../../version.pro )
include ( ../programs-libs.pro )

QT += network sql

TEMPLATE = app
CONFIG += thread
TARGET = mythutil
target.path = $${PREFIX}/bin
INSTALLS = target

LIBS += $$EXTRA_LIBS 
INCLUDEPATH += ../../libs/libmythbase

QMAKE_CLEAN += $(TARGET)

# Input
HEADERS += mythutil.h commandlineparser.h
HEADERS += backendutils.h fileutils.h jobutils.h markuputils.h
HEADERS += messageutils.h
SOURCES += main.cpp mythutil.cpp commandlineparser.cpp
SOURCES += backendutils.cpp fileutils.cpp jobutils.cpp markuputils.cpp
SOURCES += messageutils.cpp

mingw: LIBS += -lwinmm -lws2_32
