import QtQuick.Window 2.0
import QtQuick 2.6
import QtQuick.Controls 2.2
import book 1.0
import model 1.0
import category 1.0


Item {
    id: root
    objectName: "editBook"
    property string bookRowIndex : null
    property string bookName : null
    property string bookDescription : null
    property string bookAuthor : null
    property string bookCategoryId : null
    property var categories : null
//    signal saveBook(int row, string name)

    ToolBar {
        id: toolBar
        width: parent.width
        Label {
            id: label
            anchors.centerIn: parent
            text: "EditBook ToolBar"
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
//                text: book == null ? "" : book.name + "\n";
                text: bookName
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
            TextEdit {
                id: descriptionTextEdit
                rightPadding: 20
                width: parent.width - rightPadding
                wrapMode: Text.WordWrap
                text: bookDescription
//                text: book == null ? "" : book.description + "\n";
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
//                text: book == null ? "" : book.author + "\n";
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
                model: ListModel {
                    Component.onCompleted: {
                        for (var i = 0; i < categories.length; i++) {
                            append( { cat: categories[i] } )
                        }
                    }
                } // end model
                currentIndex: bookCategoryId
            }
        }

    } // end category row

    Row {
        anchors.topMargin: 20
        anchors.top: categoryRow.bottom
        anchors.horizontalCenter: categoryRow.horizontalCenter

        Button {
            id: exitButton
            text: qsTr("Back")
            background: Rectangle {
               implicitWidth: 80
               implicitHeight: 30
               color: exitButton.down ? "#A0A0A0" : "#f6f6f6"
               border.color: "#26282a"
               border.width: 1
               radius: 4
            }
            onClicked: {
//                root.parent.pop();
                root.StackView.view.pop();
            }

        } // end exit button

        Button {
            id: saveButton
            text: qsTr("Save")
            anchors.horizontalCenterOffset: 50
            background: Rectangle {
               implicitWidth: 80
               implicitHeight: 30
               color: saveButton.down ? "#A0A0A0" : "#f6f6f6"
               border.color: "#26282a"
               border.width: 1
               radius: 4
            }
            onClicked: {
//                console.log(root.parent.objectName)
//                root.parent.saveBook(bookRowIndex, nameTextField.text)
                console.log(root.parent.objectName)
                root.StackView.view.saveBook(bookRowIndex, nameTextField.text)

             }

        } // end save button
    }
}
