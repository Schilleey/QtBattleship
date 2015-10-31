import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.1
import QtQuick.Layouts 1.2

import QtBattleship 1.0
import GuiControls 1.0

import "UILogic.js" as UILogic


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
//           TextInput {
//               width: 30
//               validator: IntValidator {bottom: 8; top: 26;}
//               text: "16" //TODO: set with c++
//           }

           NumberInput {
               property string text: "16"

               id: numberInputBFSize
               width: 40
               height: 22

               minValue: 8
               maxValue: 26
               defaultIncrement: 1

               textInput.text: text

               // Must use this signal to unbreak text link
               onQuickUpdate: text = quickValue

               onEditingFinished: {
                   //User pressed enter or input focus was lost
                   text = textInput.text
               }
           }

       }

       RowLayout {
           id: shipPointsRowLayout
           anchors.horizontalCenter: parent.horizontalCenter

           Text {
            text: qsTr("Shippoints")
           }

//           TextInput {
//               width: 30
//               validator: IntValidator {bottom: 16; top: 52;}
//               text: "32" //TODO: set with c++
//           }

           NumberInput {
               property string text: "32"

               id: numberInputPoints
               width: 40
               height: 22

               minValue: 16
               maxValue: 52
               defaultIncrement: 1

               textInput.text: text

               // Must use this signal to unbreak text link
               onQuickUpdate: text = quickValue

               onEditingFinished: {
                   //User pressed enter or input focus was lost
                   text = textInput.text
               }
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
               onClicked: {
                   Settings.numFields = numberInputBFSize.text;
                   Settings.shipPoints = numberInputPoints.text;

                   newGame.visible = false

                   engine.battlefield.initialize();
                   UILogic.createBattleField("playerboard");
               }
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

