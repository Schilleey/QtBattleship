import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.2
import QtQuick.Dialogs 1.2

import QtBattleship 1.0

import "UILogic.js" as UILogic


Rectangle {
    property int paddingBoard: Settings.numFields + 1
    property int fieldSize: Settings.fieldSize = UILogic.calculateFieldSize(parent.width, paddingBoard, Screen.width, Screen.height)
    property variant colNames: ["A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"]
    property variant rowNames: ["1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26"]
    property bool isPlayer
    property variant battlefield: isPlayer ? engine.playerField : engine.opponentField

    id: canvas
    width: fieldSize * paddingBoard + paddingBoard
    height: width

    Rectangle {
        id: boardfields
        anchors.right: canvas.right
        anchors.bottom: canvas.bottom
        width: canvas.width - canvas.fieldSize
        height: canvas.height - canvas.fieldSize
        color: "black"

        Grid {
            rows: Settings.numFields
            columns: Settings.numFields
            anchors.centerIn: parent
            spacing: 1

            Repeater {
                id: repeater
                model: canvas.battlefield
                delegate: Rectangle {
                    width: canvas.fieldSize
                    height: canvas.fieldSize

                    FieldView {
                        anchors.fill: parent
                        data: display
                    }

                    MouseArea {
                        id: mouseSquareArea
                        anchors.fill: parent
                        hoverEnabled: true
                        acceptedButtons: Qt.LeftButton
                        enabled: !canvas.isPlayer

                        onClicked: {
                            if(!engine.isRunning)
                                return;

                            if(!engine.isPlayersTurn)
                                return;

                            var ok = engine.processTurn(index);

                            if(!ok)
                                tryAgainDialog.open();
                        }
                    }
                }
            }
        }
    }

    RowLayout {
        id: colInformation
        anchors.horizontalCenter: boardfields.horizontalCenter
        width: boardfields.width - 2
        spacing: 1

        Repeater {
            model: Settings.numFields
            delegate: Rectangle {
                width: canvas.fieldSize
                height: canvas.fieldSize

                Text {
                    anchors.centerIn: parent
                    text: canvas.colNames[index]
                }
            }
        }
    }

    ColumnLayout {
        id: rowInformation
        anchors.verticalCenter: boardfields.verticalCenter
        height: boardfields.height - 2
        spacing: 1

        Repeater {
            model: Settings.numFields
            delegate: Rectangle {
                width: canvas.fieldSize
                height: canvas.fieldSize

                Text {
                    anchors.centerIn: parent
                    text: canvas.rowNames[index]
                }
            }
        }
    }

    RowLayout {
        id: fieldButtons
        anchors.left: canvas.left
        anchors.top: canvas.bottom
        anchors.topMargin: 5
        spacing: 5

        Button {
            id: randomButton
            text: qsTr("Place ships")
            visible: canvas.isPlayer
            enabled: !engine.isRunning
            onClicked: {
                engine.placeShipsRandom(engine.playerFieldName());
            }
        }

        Button {
            id: startButton
            text: qsTr("Start game")
            visible: canvas.isPlayer
            enabled: !engine.isRunning
            onClicked: {
                engine.start();
            }
        }
    }

    ColumnLayout {
        id: gameInformations
        visible: canvas.isPlayer
        anchors.left: canvas.left
        anchors.top: fieldButtons.bottom
        anchors.topMargin: 5
        spacing: 5

        Label {
            font.pixelSize: 12
            color: "steelblue"
            text: "Ships left: Player " + engine.playerField.numberOfShips
                        + ", Opponent " + engine.opponentField.numberOfShips
        }

        Label {
            font.pixelSize: 14
            color: "steelblue"
            text: engine.gameInformation
        }
    }

    MessageDialog {
        id: tryAgainDialog
        title: "Warning"
        text: "This position has been tried already! Your turn again!"
        icon: StandardIcon.Warning
        standardButtons: StandardButton.Ok
        onAccepted: {
            tryAgainDialog.close();
        }

        Component.onCompleted: visible = false
    }
}

