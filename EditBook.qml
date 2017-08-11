import QtQuick.Window 2.0
import QtQuick 2.6
import QtQuick.Controls 2.2
import Qt.labs.platform 1.0
import book 1.0
import model 1.0
import catmodel 1.0
import category 1.0


Item {
    id: root
    objectName: "editBook"
    property int bookIndexRow : null
    property string bookName : null
    property string bookDescription : null
    property string bookAuthor : null
    property string bookImage : null
    property int bookCategoryIndex : null
    property CatModel catModel : null

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
        id: titleRow
        width: parent.width
        y: toolBar.height
        Column {
            padding: 20
            topPadding: 25
            width: parent.width / 3
            Text {
                verticalAlignment: Qt.AlignCenter
                text: qsTr("Title: ")
            }
        }
        Column {
            topPadding: 20
            width: parent.width / 3 * 2
            TextField {
                id: nameTextField
                rightPadding: 20
                width: parent.width - rightPadding
                text: bookName
                focus: true
             }
        } // end title row
    }

    Row {
        id: descRow
        anchors.top: titleRow.bottom
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
                text: bookDescription
             }
        }
    } // end desc row

    Row {
        id: authorRow
        anchors.top: descRow.bottom
        width: parent.width
        Column {
            padding: 20
            topPadding: 25
            width: parent.width / 3
            Text {
//                    horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignCenter
                text: qsTr("Author: ")
            }
        }
        Column {
            topPadding: 20
            width: parent.width / 3 * 2
            TextField {
                id: autorTextField
                rightPadding: 20
                width: parent.width - rightPadding
                text: bookAuthor
             }
        }
    } // end author row

    Row {
        id: categoryRow
        anchors.top: authorRow.bottom
        width: parent.width
        Column {
            padding: 20
            topPadding: 25
            width: parent.width / 3
            Text {
                verticalAlignment: Qt.AlignCenter
                text: qsTr("Category: ")
            }
        }

        Column {
            topPadding: 20
            width: parent.width / 3 * 2
            ComboBox {
                id: categoryComboBox
                rightPadding: 20
                width: parent.width - rightPadding
                model: catModel.categories
                currentIndex: bookCategoryIndex
            }
        }
    } // end category row

    Row {
        id: imageRow
        anchors.top: categoryRow.bottom
        width: parent.width

        Column {
            padding: 20
            topPadding: 25
            width: parent.width / 3
            Text {
                verticalAlignment: Qt.AlignCenter
                text: qsTr("Image: ")
            }
        }
        Column {
            padding: 20
            topPadding: 25
            width: parent.width / 3
            Text {
                id: imageText
                verticalAlignment: Qt.AlignCenter
                text: bookImage
             }
        }
        Column {
            // load image
            padding: 20
            width: parent.width / 3
            Button {
                id: imageButton
                text: bookIndexRow == -1 ? qsTr("Load Image") : qsTr("Change Image")
                background: Rectangle {
                   implicitWidth: 80
                   implicitHeight: 30
                   color: imageButton.down ? "#A0A0A0" : "#f6f6f6"
                   border.color: "#26282a"
                   border.width: 1
                   radius: 4
                }
                onClicked: fileDialog.open()
            } // end image button
        }

        FileDialog {
             id: fileDialog
             nameFilters: ["(*.jpg *.jpeg *png)"]
             folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
             onAccepted: {
                var url = fileDialog.file.toString();
                var name = url.substring(url. lastIndexOf("/") + 1, url.length)
                imageText.text = name;
                StandardPaths.writableLocation(StandardPaths.AppDataLocation) + "/" + name;
                root.StackView.view.saveImage(url);
             }
         }
    } // end image row

    Row {
        id: buttonRow
        anchors.top: imageRow.bottom
        anchors.horizontalCenter: imageRow.horizontalCenter

        Button {
            id: saveButton
            text: qsTr("Save")
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
                    root.StackView.view.saveBook(bookIndexRow, nameTextField.text, descriptionTextEdit.text, autorTextField.text, imageText.text, categoryComboBox.currentIndex);
                    root.StackView.view.pop();
                } else {
                    errorMessage.visible = true;
                    nameTextField.focus = true;
                }
            }

        } // end save button

    }
    Row {
        anchors.topMargin: 2
        anchors.top: buttonRow.bottom
        anchors.horizontalCenter: buttonRow.horizontalCenter
        Label {
            id: errorMessage
            text : "Missing book title!"
            visible: false
            color: "#FF0000"
        }
    }

    Keys.onReturnPressed: {
        saveButton.clicked();
    }

    Component.onCompleted: {
        nameTextField.forceActiveFocus();
    }

}
