import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.2

import QtBattleship 1.0


Rectangle {
    id: optionsContainer
    anchors.fill: parent

    Image {
        anchors.fill: parent
        source: "qrc:/images/resources/GameBackground.jpg"
    }

    Column {
        spacing: 10
        anchors.horizontalCenter: parent.horizontalCenter

        Text {
            id: optionsText
            font.pixelSize: 14
            text: qsTr("Options")
            anchors.horizontalCenter: parent.horizontalCenter
        }

        RowLayout {
            anchors.horizontalCenter: parent.horizontalCenter

            Text {
                text: qsTr("Battlefield color:")
            }

            ComboBox {
                id: battlefieldColor

                model: ["white", "black", "yellow", "cyan"]
                Component.onCompleted: {
                    currentIndex = battlefieldColor.find(Settings.boardColor);
                }
            }
        }

        RowLayout {
            anchors.horizontalCenter: parent.horizontalCenter
            Button {
                id: saveOptionsButton
                text: qsTr("Save")
                onClicked: {
                    Settings.boardColor = battlefieldColor.currentText;

                    options.visible = false;
                    mainMenu.visible = true;
                }
            }
            Button {
                id: cancelOptionsButton
                text: qsTr("Cancel")
                onClicked: {
                    options.visible = false;
                    mainMenu.visible = true;
                }
            }
        }
    }
}

