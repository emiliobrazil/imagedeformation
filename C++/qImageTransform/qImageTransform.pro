TEMPLATE = app
TARGET = qImageTransform
QT += core \
    gui \
    opengl
HEADERS += maskImage_qt.h \
    qMyLine.h \
    qimageshow.h \
    qimagetransform.h \
    controlpainel_qt.h \
    pixelManipulation_qt.h
SOURCES += maskImage_qt.cpp \
    qMyLine.cpp \
    qimageshow.cpp \
    main.cpp \
    qimagetransform.cpp \
    controlpainel_qt.cpp
FORMS += controlpainel_qt.ui
INCPATH += /home/emilio/Documents/IMPA_projetos/Tese_doutorado/implementacao/bibliotecas/eVector/
LIBS += -L/home/emilio/Documents/IMPA_projetos/Tese_doutorado/implementacao/bibliotecas/eVector/ \
    -leVector
