TEMPLATE = app

QT += core qml quick widgets network

SOURCES += main.cpp \
    commander.cpp
#SOURCES += main.qml

RESOURCES += qml.qrc
    #config.ini

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    commander.h
TRANSLATIONS += translate.ts
