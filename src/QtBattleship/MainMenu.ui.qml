import QtQuick 2.5
import QtQuick.Controls 1.3

Rectangle {
    id: mainMenuContainer
    property int buttonsMargin: 10


    //TODO: SIZES!

    Text {
        id: gameName
        text: "QtBattleship"
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Rectangle{
        border.color: "black";
        anchors.top: gameName.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        width: newGameButton.width + 10
        height: 3 * newGameButton.height + 4 * buttonsMargin

        Button {
            id: newGameButton
            text: qsTr("New Game")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: buttonsMargin
        }
        Button {
            id: joinGameButton
            text: qsTr("Join Game")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: newGameButton.bottom
            anchors.topMargin: buttonsMargin
        }
        Button {
            id: optionsButton
            text: qsTr("Options")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: joinGameButton.bottom
            anchors.topMargin: buttonsMargin
        }

    }
}

