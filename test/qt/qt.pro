TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c \
    ../../tzbox.c \
    ../../lib/scunit-clang/scunit.c

INCLUDEPATH += ../../ \
    ../../lib/scunit-clang

HEADERS += \
    ../../tzbox.h \
    ../../lib/scunit-clang/scunit.h
