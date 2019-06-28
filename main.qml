import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    title: qsTr("Hello World")
    width: 640
    height: 480
    visible: true

    Item {
        id: mainWinId
        objectName: "MainWindow"
        width: 640
        height: 480

        signal itemSelectionChanged(string text)

        // this function is our QML slot
        function setNotificationText(text){
            console.log("setNotification: " + text)
            notifyTextId.text = text
        }

        FocusText {
            id: titleTextId
            anchors.top: mainWinId.top
            width: mainWinId.width
            height: 30
            focus: true
            KeyNavigation.down: nameListId

            text: "Title: " + quickItem.title
        }

        ListView {
            id: nameListId
            anchors.top: titleTextId.bottom
            //anchors.bottom: mainWinId
            width: mainWinId.width / 2
            height: 300
            //model: nameModelId
            model: quickItem.itemModel
            KeyNavigation.up: titleTextId

            delegate:  FocusText {
                text: "Name: " + model.name

                onFocusChanged: if (activeFocus) {
                                    console.log("Focus Changed " + model.name)
                                    mainWinId.itemSelectionChanged(model.name)
                                }
            }
        }

        Text {
            id: notifyTextId
            anchors.left: nameListId.right
            y: titleTextId.y + titleTextId.height * 2
            width: 300
            height: 100

            text: "Notify text"
        }
    }
}
