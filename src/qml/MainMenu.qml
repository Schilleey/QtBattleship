import QtQuick 2.5
import QtQuick.Controls 1.3

import QtBattleship 1.0

Rectangle {
    id: mainMenuContainer
    anchors.fill: parent
    property int buttonsMargin: 10
    property int buttonsHeight: 23
    property real buttonsWidthPercentage: 0.5

    Image {
        anchors.fill: parent
        source: "qrc:/images/resources/GameBackground.jpg"
    }

    Column {
        spacing: 10
        anchors.horizontalCenter: parent.horizontalCenter

        Text {
            id: gameNameText
            font.pixelSize: 14
            text: qsTr("QtBattleship")
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: newGameButton
            text: qsTr("New Game")
            width: mainMenuContainer.width * buttonsWidthPercentage
            height: buttonsHeight
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                mainMenu.visible = false;
                newGame.visible = true;
            }
        }

        Button {
            id: optionsButton
            text: qsTr("Options")
            width: mainMenuContainer.width * buttonsWidthPercentage
            height: buttonsHeight
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                mainMenu.visible = false;
                options.visible = true;
            }
        }
    }
}

