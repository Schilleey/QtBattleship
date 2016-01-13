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
import QtQuick.Layouts 1.2
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

import QtBattleship 1.0


ApplicationWindow {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("QtBattleship")

    onClosing: {
        close.accepted = false;
        exitDialog.open();
    }

    MessageDialog {
        id: exitDialog
        title: "Exit"
        text: "Realy close the game?"
        icon: StandardIcon.Question
        standardButtons: StandardButton.Ok | StandardButton.Cancel
        onAccepted: {
            Settings.save();
            engine.stop();
            Qt.quit();
        }
        onRejected: {
            exitDialog.close();
        }

        Component.onCompleted: visible = false
    }

    RowLayout {
        id: boardLayout
        visible: false
        anchors.fill: parent

        Rectangle {
            id: playerBoardRect
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Rectangle {
            id: separator
            width: 3
            Layout.fillHeight: true
            color: "black"
        }

        Rectangle {
            id: opponentBoardRect
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
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

    Options {
        id: options
        visible: false
        anchors.fill: parent
    }

    Image {
        id: shipAnimationImage
        visible: true
        x: -width
        y: 0.665 * mainWindow.height - height
        source: "qrc:/images/resources/ShipAnim.svg"

        SequentialAnimation {
            id: shipAnimation
            running: true
            loops: Animation.Infinite
            PropertyAnimation {id: panim1; target: shipAnimationImage; property: "x"; to: mainWindow.width; duration: 12000}
            PropertyAnimation {id: panim2; target: shipAnimationImage; property: "mirror"; to: true; duration: 2000}
            PropertyAnimation {id: panim3; target: shipAnimationImage; property: "x"; to: -shipAnimationImage.width; duration: 12000}
            PropertyAnimation {id: panim4; target: shipAnimationImage; property: "mirror"; to: false; duration: 2000}
        }
    }

}

