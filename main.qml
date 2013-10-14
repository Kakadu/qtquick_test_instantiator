import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    width: 800
    height: 600

    toolBar: ToolBar {
        RowLayout {
            Menu {
                id: backContextMenu
                Instantiator {
                    model: backModel
                    MenuItem { text: model.text }
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
            // forward stuff
            Menu {
                id: forwardContextMenu
                Instantiator {
                    model: forwardModel
                    MenuItem { text: model.text }
                    onObjectAdded: {
                        console.log("QML: object added: " + object.text + ", index= " + index);
                        forwardContextMenu.insertItem(index,object)
                        goForwardAction.enabled = true;
                    }
                    onObjectRemoved: {
                        forwardContextMenu.removeItem(object)
                        console.log("QML: object removed: " + object.text);
                        if (forwardContextMenu.items.count == 0) goForwardAction.enabled = false
                    }
                }
            }
            Action {
                id: goForwardAction
                enabled: false
            }
            ToolButton {
                action: goForwardAction
                text: "->"
                onClicked: if (forwardContextMenu.items.length>0) forwardContextMenu.popup()
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
        backModel.add("dddddddddddd");
        backModel.add("ccccccccc");
        backModel.add("bbbbbb");
        backModel.add("aaa");
    }
}
