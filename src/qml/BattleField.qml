import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.2

import QtBattleship 1.0


Rectangle {
    property int fieldSize: Settings.fieldSize = parseInt(mainWindow.height * 0.055)
    property int paddingBoard: Settings.numFields + 1
    property variant colNames: ["A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"]
    property variant rowNames: ["1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26"]

    id: canvas
    x: 0
    y: 0
    width: (Settings.numFields + 1) * fieldSize + paddingBoard
    height: (Settings.numFields + 1) * fieldSize + paddingBoard

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
                model: engine.battlefield
                delegate: Rectangle {
                    width: canvas.fieldSize
                    height: canvas.fieldSize

                    FieldView {
                        anchors.fill: parent
                        data: display
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

            Rectangle {
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

            Rectangle {
                width: canvas.fieldSize
                height: canvas.fieldSize

                Text {
                    anchors.centerIn: parent
                    text: canvas.rowNames[index]
                }
            }
        }
    }

    Button {
        id: testButton
        anchors.left: boardfields.right
        anchors.bottom: boardfields.top
        text: qsTr("Test Signal")
        onClicked: {
            engine.battlefield.setField(0, 0, 0);
        }
    }
}

