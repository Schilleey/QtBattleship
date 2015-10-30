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
       TextInput {
            id: ipToConnectTo

            anchors.horizontalCenter: parent.horizontalCenter
            validator: RegExpValidator {
                regExp:/^(([01]?[0-9]?[0-9]|2([0-4][0-9]|5[0-5]))\.){3}([01]?[0-9]?[0-9]|2([0-4][0-9]|5[0-5]))$/
            }
            inputMask: "000.000.000.000;0"
            text: "192.168.0.100"
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

