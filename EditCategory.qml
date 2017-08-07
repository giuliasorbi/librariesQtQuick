import QtQuick.Window 2.0
import QtQuick 2.6
import QtQuick.Controls 2.2
import Qt.labs.platform 1.0
import book 1.0
import model 1.0
import category 1.0


Item {
    id: root
    objectName: "editCategory"
    property int categoryRowIndex : null
    property string categoryName : null
    property string categoryDescription : null

    ToolBar {
        id: toolBar
        width: parent.width
        ToolButton {
            padding: 4
            Image {
                id: icon
                y: parent.padding
                x: y
                source: "qrc:/images/back.png"
                height: toolBar.height - parent.padding * 2
                width: height
            }
            onClicked: {
                root.StackView.view.pop();
            }
        }
    }

    Row {
        id: nameRow
        width: parent.width
        y: toolBar.height
        Column {
            padding: 20
            topPadding: 25
            width: parent.width / 3

            Text {
                verticalAlignment: Qt.AlignCenter
                text: qsTr("Name: ")
            }
        }
        Column {
            topPadding: 20
            width: parent.width / 3 * 2
            TextField {
                id: nameTextField
                rightPadding: 20
                width: parent.width - rightPadding
                text: categoryName
                focus: true
             }
        } // end title row
    }

    Row {
        id: descRow
        anchors.top: nameRow.bottom
        width: parent.width
        Column {
            padding: 20
            topPadding: 25
            width: parent.width / 3
            Text {
                verticalAlignment: Qt.AlignCenter
                text: qsTr("Description: ")
            }
        }
        Column {
            topPadding: 20
            width: parent.width / 3 * 2
            TextField {
                id: descriptionTextEdit
                rightPadding: 20
                width: parent.width - rightPadding
                wrapMode: Text.WordWrap
                text: categoryDescription
             }
        }
    } // end desc row

    Row {
        id: buttonRow
        anchors.topMargin: 20
        anchors.top: descRow.bottom
        anchors.horizontalCenter: descRow.horizontalCenter

        Button {
            id: saveButton
            text: qsTr("Save")
            focus: true
            background: Rectangle {
               implicitWidth: 80
               implicitHeight: 30
               color: saveButton.down ? "#A0A0A0" : "#f6f6f6"
               border.color: "#26282a"
               border.width: 1
               radius: 4
            }
            onClicked: {
                if (nameTextField.text != "" ) {
                    root.StackView.view.saveCategory(categoryRowIndex, nameTextField.text, descriptionTextEdit.text);
                    root.StackView.view.pop();
//                    root.StackView.view.get(root.StackView.view.currentItem.StackView.index).setListFocus();

                } else {
                    errorMessage.visible = true;
                    nameTextField.focus = true;
                }
             }

            Component.onCompleted: {
                saveButton.forceActiveFocus();
            }

        } // end save button

    }
    Row {
        anchors.topMargin: 2
        anchors.top: buttonRow.bottom
        anchors.horizontalCenter: buttonRow.horizontalCenter
        Label {
            id: errorMessage
            text : "Missing category name!"
            color: "#FF0000"
            visible: false
        }
    }
    Keys.onReturnPressed: {
//        console.log( 'Key Return was pressed');
        saveButton.clicked();
    }

}
