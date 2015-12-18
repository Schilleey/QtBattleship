/*
 *  GUI related JavaScript functions
 */

function createBattleField(boardId, containerId, isPlayer)
{
    var component = Qt.createComponent("BattleField.qml");
    if (component.status == Component.Ready)
    {
        component.createObject(containerId, {"id": boardId,
                                             "isPlayer": isPlayer,
                                             "visible": true,
                                             "anchors.top": containerId.top});

        console.log(boardId + ": BattleField created!");
    }
}

function calculateFieldSize(parentSize, numFields, screenWidth, screenHeight)
{
    var size = Math.floor((parentSize - numFields) / numFields);

    if(size < 20)
        size = 20
    else if(size > 25)
        size = 25;

    mainWindow.width = 2.0 * (size * numFields + numFields) * 1.05;
    mainWindow.height = mainWindow.width * 0.5 + 60;
    mainWindow.x = screenWidth / 2 - mainWindow.width / 2;
    mainWindow.y = screenHeight / 2 - mainWindow.height / 2;

    return size;
}

