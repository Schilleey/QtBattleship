import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.2

Rectangle {
    id: newGameContainer
    Column {
        spacing: 10
        anchors.horizontalCenter: parent.horizontalCenter
        Text {
            id: joinGameText
            text: qsTr("Join game")
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            text: qsTr("Enter IP")
            anchors.horizontalCenter: parent.horizontalCenter

        }
       TextEdit {
           id: ipToConnectTo

           anchors.horizontalCenter: parent.horizontalCenter
           text: "192.168.0.128" //TODO: set by User!
       }


       RowLayout {
           anchors.horizontalCenter: parent.horizontalCenter
           Button {
               id: createJoinGameButton
               text: qsTr("Join")
           }
           Button {
               id: cancelJoinGameButton
               text: qsTr("Cancel")
               onClicked: {
                   joinGame.visible = false;
                   mainMenu.visible = true;
               }
           }
       }
    }
}

