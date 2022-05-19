QT += qml quick

CONFIG += qmltypes
QML_IMPORT_NAME = FractalModule
QML_IMPORT_MAJOR_VERSION = 1

HEADERS += \
    fractal.h \
    fractalParams.h \
    renderer.h
SOURCES += main.cpp \
    fractal.cpp \
    renderer.cpp
RESOURCES += \
    resources.qrc
