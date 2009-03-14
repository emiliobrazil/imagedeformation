# -------------------------------------------------
# Project created by QtCreator 2009-03-08T19:55:01
# -------------------------------------------------
QT -= core \
    gui
TARGET = eVector
TEMPLATE = lib
CONFIG += staticlib

DEFINES += EVECTOR_LIBRARY
SOURCES += Vector3D.cpp \
    Vector2D.cpp
HEADERS += Vector3D.h \
    Vector2D.h \
    primitive_types.h \
    primitive_const.h
