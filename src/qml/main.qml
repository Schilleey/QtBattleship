/**
 * main.qml
 *
 * \brief Qml main file
 *
 * This is the main Qml file.
 *
 */

import QtQuick 2.5
import QtQuick.Controls 1.2
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

import QtBattleship 1.0


ApplicationWindow {
    id: mainWindow
    visible: true
    width: 600
    height: 400
    title: qsTr("QtBattleship")

    onClosing: {
        Settings.save();
    }

    MainMenu {
        id: mainMenu
        visible: true
        anchors.fill: parent
    }

    NewGame {
        id: newGame
        visible: false
        anchors.fill: parent
    }

    JoinGame {
        id: joinGame
        visible: false
        anchors.fill: parent
    }

    Options {
        id: options
        visible: false
        anchors.fill: parent
    }

}

