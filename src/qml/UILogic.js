/*
 *  GUI related JavaScript functions
 */

function createBattleField(boardId)
{
    var component = Qt.createComponent("BattleField.qml");
    if (component.status == Component.Ready)
    {
        component.createObject(mainWindow, {"id": boardId, "visible": true, "anchors.fill": mainWindow});

        console.log("BattleField created!");
    }
}

