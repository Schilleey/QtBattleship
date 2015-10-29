TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += src/main.cpp \
    src/settings.cpp

HEADERS += \
    src/settings.h

RESOURCES += qml.qrc

OTHER_FILES += \
    src/qml/main.qml \
    src/qml/MainMenu.qml \
    src/qml/NewGame.qml \
    src/qml/JoinGame.qml \
    src/qml/components/GuiControls/NumberInput.qml

# Additional import path used to resolve QML modules in Qt Creator's code model
QML2_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

# Project settings
include(projectSettings.pri)

