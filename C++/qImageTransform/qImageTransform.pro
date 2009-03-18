TEMPLATE = app

TARGET = qImageTransform

QT += core \
    gui \
    opengl

HEADERS += qMyLine.h \
    qimageshow.h \
    qimagetransform.h \
    controlpainel_qt.h \
    pixelManipulation_qt.h

SOURCES += qMyLine.cpp \
    qimageshow.cpp \
    main.cpp \
    qimagetransform.cpp \
    controlpainel_qt.cpp \
    pixelManipulation_qt.cpp

FORMS += controlpainel_qt.ui

INCPATH += ../../bibliotecas/eVector/ \
           ../../bibliotecas/vector_field/

LIBS += -L../../bibliotecas/eVector/ -L/usr/lib/atlas \
        -leVector -llapack -latlas
