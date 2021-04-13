TEMPLATE = app
CONFIG += console c++11 thread
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        cop.cpp \
        detective.cpp \
        disruptor.cpp \
        interrogation_room.cpp \
        lightswitch.cpp \
        main.cpp

HEADERS += \
    cop.h \
    detective.h \
    disruptor.h \
    interrogation_room.h \
    lightswitch.h \
    suspect.h \
    utils.h

