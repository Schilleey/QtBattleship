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

       CheckBox {
           id: classicCheckbox
           anchors.horizontalCenter: parent.horizontalCenter
           text: qsTr("Classic")
       }

       RowLayout {
           id: fieldSizeRowLayout
           anchors.horizontalCenter: parent.horizontalCenter
           visible: !classicCheckbox.checked

           Text {
               text: qsTr("Battlefield size")
           }

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
           anchors.horizontalCenter: parent.horizontalCenter
           Button {
               id: createNewGameButton
               text: qsTr("Create game")
               onClicked: {
                   if(classicCheckbox.checked)
                       Settings.numFields = 10;
                   else
                       Settings.numFields = numberInputBFSize.text;

                   newGame.visible = false;

                   engine.playerField.initialize();
                   engine.placeShipsRandom(engine.playerFieldName());
                   UILogic.createBattleField("playerboard", playerBoardRect, true);

                   engine.opponentField.initialize();
                   engine.placeShipsRandom(engine.opponentFieldName());
                   engine.opponentField.hideImages(true);
                   UILogic.createBattleField("opponentboard", opponentBoardRect, false);

                   boardLayout.visible = true;
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

