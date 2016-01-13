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
    property bool dragEnabled: true
    property bool backToMainMenu: false
    property variant battlefield: isPlayer ? engine.playerField : engine.opponentField
    property variant self

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
                    id: fieldRect
                    width: canvas.fieldSize
                    height: canvas.fieldSize

                    FieldView {
                        id: fieldView
                        anchors.fill: parent
                        data: fielddata
                    }

                    DropArea {
                        id: dropRect
                        anchors.fill: parent

                        property real col: canvas.battlefield.indexToColumn(index)
                        property real row: canvas.battlefield.indexToRow(index)

                        onDropped: {
                            var ok = canvas.battlefield.moveShip(drop.source.fieldIndex, index);
                        }

                        onPositionChanged: {
                            drag.source.x = boardfields.x + col * canvas.fieldSize + col;
                            drag.source.y = boardfields.y + row * canvas.fieldSize + row;
                        }
                    }

                    MouseArea {
                        id: mouseSquareArea
                        anchors.fill: parent
                        hoverEnabled: true
                        acceptedButtons: Qt.LeftButton | Qt.RightButton

                        property real col: canvas.battlefield.indexToColumn(index)
                        property real row: canvas.battlefield.indexToRow(index)

                        drag.target: (canvas.dragEnabled && canvas.isPlayer) ? dragRect : null
                        drag.minimumX: boardfields.x
                        drag.minimumY: boardfields.y
                        drag.maximumX: boardfields.x + boardfields.width - canvas.fieldSize - 2
                        drag.maximumY: boardfields.y + boardfields.height - canvas.fieldSize - 2

                        Rectangle {
                            id: dragRect
                            width: (orientation == 0) ? canvas.fieldSize * size + size : canvas.fieldSize + 2
                            height: (orientation == 0) ? canvas.fieldSize + 2 : canvas.fieldSize * size + size
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            color: "transparent"
                            border.color: "red"
                            visible: false

                            property bool dragActive: mouseSquareArea.drag.active
                            property int fieldIndex: index
                            property int size: shipSize
                            property int orientation: shipOrientation
                            property real spotSize: (canvas.fieldSize + 2)/2

                            onDragActiveChanged: {
                                if(canvas.battlefield.fieldIsEmpty(index) ||
                                   (mouseSquareArea.pressedButtons & Qt.RightButton))
                                {
                                    Drag.cancel();
                                    return;
                                }

                                if(dragActive) {
                                    dragRect.visible = true;
                                    Drag.start();
                                } else {
                                    dragRect.visible = false;
                                    Drag.drop();
                                }
                            }

                            Drag.hotSpot.x: spotSize
                            Drag.hotSpot.y: spotSize
                            states: [
                                State {
                                    when: mouseSquareArea.drag.active
                                    ParentChange { target: dragRect; parent: canvas }
                                    AnchorChanges { target: dragRect; anchors.verticalCenter: undefined; anchors.horizontalCenter: undefined }
                                }
                            ]
                        }

                        onClicked: {
                            if((mouse.button & Qt.RightButton) && canvas.isPlayer && canvas.dragEnabled)
                            {
                                canvas.battlefield.changeShipOrientation(index);
                                return;
                            }

                            if(canvas.isPlayer)
                                return;

                            if(!engine.isRunning)
                                return;

                            if(!engine.isPlayersTurn)
                                return;

                            if(tried)
                            {
                                tryAgainDialog.open();
                                return;
                            }

                            var ok = engine.processTurn(index);
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
                canvas.dragEnabled = false;
            }
        }

        Button {
            id: stopButton
            text: qsTr("Stop game")
            visible: canvas.isPlayer && engine.isRunning
            onClicked: {
                engine.stop(true);
                engine.reset();
                engine.placeShipsRandom(engine.playerFieldName());
                canvas.dragEnabled = true;
            }
        }

        Button {
            id: backButton
            text: qsTr("Main menu")
            visible: canvas.isPlayer
            enabled: !engine.isRunning
            onClicked: {
                boardLayout.visible = false;
                UILogic.destroyOpponentBattleField();
                mainMenu.visible = true;
                shipAnimationImage.x = -shipAnimationImage.width;
                shipAnimationImage.mirror = false;
                backToMainMenu = true;
                UILogic.destroyPlayerBattleField();
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

    Component.onDestruction: {
        if(isPlayer && backToMainMenu)
        {
            UILogic.resetMainWindowSize(Screen.width, Screen.height);
            shipAnimationImage.visible = true;
            shipAnimation.running = true;
            panim1.to = mainWindow.width; // PropertyAnimation needs this to update the "to" parameter
            shipAnimation.restart();
        }
    }
}

