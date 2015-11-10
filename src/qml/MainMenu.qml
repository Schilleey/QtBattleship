import QtQuick 2.5
import QtQuick.Controls 1.3

import QtBattleship 1.0

Rectangle {
    id: mainMenuContainer
    property int buttonsMargin: 10
    property int buttonsHeight: 23
    property real buttonsWidthPercentage: 0.5

    Text {
        id: gameName
        text: "QtBattleship"
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Rectangle {
        border.color: "black";
        anchors.top: gameName.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        width: newGameButton.width + 15
        height: 3 * buttonsHeight + 4 * buttonsMargin

        Button {
            id: newGameButton
            text: qsTr("New Game")
            width: mainMenuContainer.width * buttonsWidthPercentage
            height: buttonsHeight
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: buttonsMargin
            onClicked: {
                mainMenu.visible = false;
                newGame.visible = true;
            }
        }
        Button {
            id: joinGameButton
            text: qsTr("Join Game")
            width: mainMenuContainer.width * buttonsWidthPercentage
            height: buttonsHeight
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: newGameButton.bottom
            anchors.topMargin: buttonsMargin
            onClicked: {
                mainMenu.visible = false;
                joinGame.visible = true;
            }
        }
        Button {
            id: optionsButton
            text: qsTr("Options")
            width: mainMenuContainer.width * buttonsWidthPercentage
            height: buttonsHeight
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: joinGameButton.bottom
            anchors.topMargin: buttonsMargin
            onClicked: {
                mainMenu.visible = false;
                options.visible = true;
            }
        }

    }
}

