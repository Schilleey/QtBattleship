import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.2

Rectangle {
    id: newGameContainer
    Column {
        spacing: 10
        anchors.horizontalCenter: parent.horizontalCenter
        Text {
            id: newGameText
            text: qsTr("Create new game")
            anchors.horizontalCenter: parent.horizontalCenter

        }

        RowLayout {
           id: gameTypeRowLayout

           anchors.horizontalCenter: parent.horizontalCenter
           ExclusiveGroup { id: gameType }
           RadioButton {
               text: qsTr("Singleplayer")
               checked: true
               exclusiveGroup: gameType
           }
           RadioButton {
               text: qsTr("Multiplayer")
               exclusiveGroup: gameType
           }
       }

       CheckBox {
           id: classicCheckbox
           anchors.horizontalCenter: parent.horizontalCenter
           text: qsTr("Classic")
       }

       RowLayout {
           id: fieldSizeRowLayout
           anchors.horizontalCenter: parent.horizontalCenter
           Text {
            text: qsTr("Battlefield size")
           }
           TextEdit {
               width: 30
               text: "25" //TODO: set with c++
           }
       }

       RowLayout {
           id: shipPointsRowLayout
           anchors.horizontalCenter: parent.horizontalCenter
           Text {
            text: qsTr("Shippoints")
           }
           TextEdit {
               width: 30
               text: "25" //TODO: set with c++
           }
       }

       Button {
           id: advancedOptionsButton
           anchors.horizontalCenter: parent.horizontalCenter
           text: qsTr("Advanced options")
       }

       RowLayout {
           anchors.horizontalCenter: parent.horizontalCenter
           Button {
               id: createNewGameButton
               text: qsTr("Create game")
           }
           Button {
               id: cancelNewGameButton
               text: qsTr("Cancel")
               onClicked: {
                   newGame.visible = false;
                   mainMenu.visible = true;
               }
           }
       }
    }
}

