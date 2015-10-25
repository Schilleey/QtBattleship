import QtQuick 2.5
import QtQuick.Controls 1.3

Rectangle {
    id: mainContainer
    width: 500
    height: 500
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
        /*
        anchors.right: mainContainer.right
        anchors.bottom: mainContainer.bottom
        anchors.left: mainContainer.left*/
        anchors.horizontalCenter: parent.horizontalCenter

        width: newGameButton.width
        height: 3 * newGameButton.height + 4 * buttonsMargin

        Button {
            id: newGameButton
            text:"New Game"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: buttonsMargin
        }
        Button {
            id: joinGameButton
            text:"Join Game"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: newGameButton.bottom
            anchors.topMargin: buttonsMargin
        }
        Button {
            id: optionsButton
            text:"Options"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: joinGameButton.bottom
            anchors.topMargin: buttonsMargin
        }

    }

   // property alias mouseArea: mouseArea


/*
    MouseArea {
        id: mouseArea
        anchors.fill: parent
    }*/
}

