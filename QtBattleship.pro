TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += src/main.cpp \
    src/settings.cpp \
    src/battlefield.cpp \
    src/gameapplication.cpp \
    src/gameengine.cpp \
    src/fielddata.cpp \
    src/fieldview.cpp

HEADERS += \
    src/settings.h \
    src/battlefield.h \
    src/gameapplication.h \
    src/gameengine.h \
    src/fielddata.h \
    src/fieldview.h

RESOURCES += qml.qrc

OTHER_FILES += \
    src/qml/main.qml \
    src/qml/MainMenu.qml \
    src/qml/NewGame.qml \
    src/qml/JoinGame.qml \
    src/qml/BattleField.qml \
    src/qml/UILogic.js \
    src/qml/components/GuiControls/NumberInput.qml

# Additional import path used to resolve QML modules in Qt Creator's code model
QML2_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

# Project settings
include(projectSettings.pri)

