import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    width: 800
    height: 600
    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }
    toolBar: ToolBar {
        RowLayout {
            Menu {
                id: backContextMenu
                Instantiator {
                    model: backModel
                    MenuItem {
                        text: model.text
                        onTriggered: {
                            console.log("triggered: " + model.text)
                            //controller.backTo(model.text,-1);
                        }
                    }
                    onObjectAdded: {
                        console.log("QML: object added: " + object.text + ", index= " + index);
                        backContextMenu.insertItem(index,object)
                        goBackAction.enabled = true;
                    }
                    onObjectRemoved: {
                        backContextMenu.removeItem(object)
                        console.log("QML: object removed: " + object.text);
                        if (backContextMenu.items.count == 0) goBackAction.enabled = false
                    }
                }
            }
            Action {
                id: goBackAction
                enabled: false
            }
            ToolButton {
                action: goBackAction
                text: "<-"
                onClicked: if (backContextMenu.items.length>0) backContextMenu.popup()
            }
        }
    }
    Rectangle {
        SpinBox {
            id: spin1
            value: 2
        }
        Button {
            anchors.top: spin1.bottom
            text: "drop"
            onClicked: {
                backModel.drop(spin1.value)
            }
        }
    }
    Component.onCompleted: {
        backModel.add("d");
        backModel.add("c");
        backModel.add("b");
        backModel.add("a");
    }
}
