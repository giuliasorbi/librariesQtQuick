import QtQuick 2.6
import QtQuick.Controls 2.2
//import QtQuick.Controls.Material 2.2
import QtQml.Models 2.2
import QtQuick.Layouts 1.0
import Qt.labs.platform 1.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.0

import model 1.0
import book 1.0
import category 1.0

Pane {
    id: root
    objectName: "bookdetail"
    property int margin: 10
    property Book book: null
    signal editClicked()
    signal deleteClicked()


    GridLayout {
        id: gridLayout
//        anchors.fill: parent
        width: parent.width
        columns: 2
        rows: 4
        flow: GridLayout.TopToBottom

        Label {
            id: title
            width: parent.width
            Layout.row: 0
            font.pixelSize: 22
            font.bold: true
            elide: Label.ElideRight
            Layout.alignment: Qt.AlignCenter
            text: book == null ? "" : book.name;
            Layout.columnSpan: 2
        }


        Text {
            id: description
            Layout.margins: margin
            width: parent.width / 2
            maximumLineCount: 12

            Layout.column: 0
            Layout.row: 1
            Layout.alignment: Qt.AlignCenter | Qt.AlignTop

            text: book == null ? "" : book.description;
            elide: Text.ElideRight
            wrapMode: Text.WordWrap
            //            readOnly: true
            Layout.fillHeight: true

            Layout.fillWidth: true
        }

        Image {
            id: cover
            width: parent.width / 2
            Layout.margins: margin
            Layout.column: 1
            Layout.row: 1
            Layout.alignment: Qt.AlignCenter | Qt.AlignTop
            source: book  == null  || book.image == "" ? "qrc:/images/book.png" : StandardPaths.writableLocation(StandardPaths.AppDataLocation) + "/" + book.image
            sourceSize.height: description.height
//            Layout.rowSpan: 3

        }

        Label {
            id: author
            Layout.margins: margin
            Layout.column: 0
            Layout.row: 2

            Layout.alignment: Qt.AlignLeft
            text: book == null ? "" : book.author
            elide: Label.ElideRight

       }

        Label {
            id: category
            Layout.margins: margin
            Layout.column: 0
            Layout.row: 3

            Layout.alignment: Qt.AlignLeft
            text: book == null ? "" : bookList.model.bookCategory(bookList.currentIndex)
            elide: Label.ElideRight
            font.italic: true

       }

        Button {
            Layout.margins: margin
            Layout.column: 0
            Layout.row: 4

            id: editButton
            text: qsTr("Edit")

            background: Rectangle {
               anchors.margins: 10
               implicitWidth: 80
               implicitHeight: 30
               color: editButton.down ? "#A0A0A0" : "#f6f6f6"
//               border.color: "#26282a"
               border.width: 1
               radius: 4
            }

            onClicked: root.editClicked();
        }

        Button {
            Layout.margins: margin
            Layout.column: 1
            Layout.row: 4
            id: deleteButton
            text: qsTr("Delete")
            background: Rectangle {
               anchors.margins: 10
               implicitWidth: 80
               implicitHeight: 30
               color: deleteButton.down ? "#A0A0A0" : "#f6f6f6"
//               border.color: "#26282a"
               border.width: 1
               radius: 4
            }

            onClicked: {
//                    root.StackView.view.deleteClicked(bookList.currentIndex)
                root.deleteClicked()
            }
        }
    }
}
