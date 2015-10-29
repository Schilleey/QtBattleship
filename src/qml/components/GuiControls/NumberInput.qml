import QtQuick 2.2
import QtQuick.Layouts 1.1

/*
* Modified version of:
* https://github.com/buttleofx/QuickMamba/blob/master/qml/QuickMamba/QuickEditableNumberInput.qml
*/


Rectangle {
    id: root

    property int minValue: Number.NEGATIVE_INFINITY
    property int maxValue: Number.POSITIVE_INFINITY
    property int defaultIncrement: 1

    property alias textInput: textInput

    property string upArrow: "qrc:/images/resources/arrow2.png"
    property string upArrowHover: "qrc:/images/resources/arrow2_hover.png"
    property string downArrow: "qrc:/images/resources/arrow.png"
    property string downArrowHover: "qrc:/images/resources/arrow_hover.png"
    property color cursorColor : "#00B2A1"

    // Default style
    color: "white"
    border.width: 1
    border.color: "#333"
    radius: 1

    signal quickUpdate(var quickValue)
    signal editingFinished

    QtObject {
        id: m
        property int step: 1
    }

    // stepSign is the factor of step (eg: 1 will increment, -1 will decrement)
    function updateValue(stepSign) {
        stepSign = typeof stepSign !== 'undefined' ? stepSign : 1

        // Remember cursor position to stay in same place after text update (because we lose it when property text changes)
        var oldCursorPos = textInput.cursorPosition

        var oldValueStr = textInput.text
        var oldValueInt = parseInt(oldValueStr)

        var increment = root.defaultIncrement

        var newValue = oldValueInt + stepSign * increment
        // Adjust cursor position when the old number is negative and the new one is positive
        if (newValue >= 0 && oldValueInt < 0)
            oldCursorPos--

        root.quickUpdate(root.clamp(newValue, root.minValue, root.maxValue))
        textInput.cursorPosition = oldCursorPos
    }

    MouseArea {
        anchors.fill: parent

        onWheel: {
            if (wheel.angleDelta.y >= 0)
                root.updateValue(1)
            else
                root.updateValue(-1)
        }
    }

    RowLayout {
        anchors.fill: parent
        anchors.margins: root.border.width + 1
        TextInput {
            id: textInput
            selectByMouse: true

            Layout.fillWidth: true

            // Text Input is dynamically aligned with arrows
            horizontalAlignment: TextInput.AlignHCenter
            verticalAlignment: TextInput.AlignVCenter
            clip: true

            validator: IntValidator {
                top: root.maxValue
                bottom: root.minValue
            }

            // Default style
            color: "black"
            selectionColor: Qt.rgba(1, 1, 1, 0.2)

            Keys.onPressed: {
                switch (event.key) {
                case Qt.Key_Up:
                    root.updateValue(1)
                    event.accepted = true
                    break
                case Qt.Key_Down:
                    root.updateValue(-1)
                    event.accepted = true
                    break
                }
            }

            onEditingFinished: root.editingFinished()
        }

        ColumnLayout {
            id: arrows

            // Width of column must be equal to the biggest image width
            Layout.preferredWidth: upArrow.width > downArrow.width ? upArrow.width : downArrow.width
            Layout.fillHeight: true
            spacing: 3

            Image {
                id: upArrow
                source: root.upArrow

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true

                    onEntered: upArrow.source = root.upArrowHover
                    onExited: upArrow.source = root.upArrow

                    onClicked: root.updateValue(1)
                }
            }

            Image {
                id: downArrow
                source: root.downArrow

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true

                    onEntered: downArrow.source = root.downArrowHover
                    onExited: downArrow.source = root.downArrow

                    onClicked: root.updateValue(-1)
                }
            }
        }
    }

    function clamp(x, min, max)
    {
        return Math.max(min, Math.min(x, max));
    }

}
