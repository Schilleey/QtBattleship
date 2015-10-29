import QtQuick 2.5
import QtQuick.Controls 1.2
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

import com.hsa.qtbattleship 1.0


ApplicationWindow {
    visible: true
    width: 600
    height: 400
    title: qsTr("QtBattleship")

    MainMenu {
        id: mainMenu
        visible: true
        anchors.fill: parent
    }

    NewGame {
        id: newGame
        visible: false
        anchors.fill: parent
    }

    JoinGame {
        id: joinGame
        visible: false
        anchors.fill: parent
    }

}

