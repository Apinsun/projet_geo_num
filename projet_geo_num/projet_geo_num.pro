TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    face.cpp \
    halfedge.cpp \
    main.cpp \
    mesh.cpp \
    vec3.cpp \
    vertex.cpp

HEADERS += \
    face.h \
    halfedge.h \
    mesh.h \
    vec3.h \
    vertex.h
