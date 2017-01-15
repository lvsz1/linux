TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    my_process.cpp

INCLUDEPATH += /usr/local/mysql/include
LIBS += -L/usr/local/mysql/lib -lmysqlclient

HEADERS += \
    my_process.h

