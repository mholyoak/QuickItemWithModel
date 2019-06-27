import QtQuick 2.0

FocusScope {
    id: focusText
    property alias text: textId.text

    width: 170
    height: 50

    Rectangle {
        id: rectId
        color: "transparent"
        anchors.fill: focusText
        border.color: {
            return rectId.activeFocus ? "lightsteelblue" : rectId.focus ? "ghostwhite" : "transparent"

            /*
            if (focusText.parent.focus && focusText.focus) {
                return "lightsteelblue"
            }
            if (focusText.parent.focus) {
                return "ghostwhite"
            }
            if (focusText.focus) {
                return "ghostwhite"
            }
            return "transparent"
            */
        }
        focus: true
        border.width: 4

        Text {
            id: textId
            anchors.centerIn: rectId
            text: "FocusText"
        }
    }
}
