import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
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
    property Book book: null
    property var categories
    signal editClicked()

    Label {
        id: title
        Layout.alignment: Qt.AlignCenter
        font.pixelSize: 22
        font.bold: true
        width: parent.width
        elide: Label.ElideRight
        horizontalAlignment: Qt.AlignHCenter
        text: book == null ? "" : book.name;
    }

    Row {
        anchors.top: title.bottom
        width: parent.width


        Column {
            id: columnInfo
            width: parent.width / 3 * 2
            Text {
                width: parent.width - parent.padding
                padding: 20
                wrapMode: Text.WordWrap
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignJustify
                text: book == null ? "" : book.description;
            }

            Label {
                width: parent.width
                leftPadding: 20
                rightPadding: 20
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignJustify
                text: book == null ? "" : book.author + "\n";

            }

            Label {
                width: parent.width
                leftPadding: 20
                rightPadding: 20
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignJustify
                font.italic: true
                text: book == null ? "" : bookList.model.bookCategory(bookList.currentIndex);

            }

        } // end columnInfo

        Column {
            id: columnImg
            width: parent.width / 3
            topPadding: 20
            padding: 10

//                padding: 20

            Image {
                id: cover
                horizontalAlignment: Image.AlignHCenter
                source: book  == null  || book.image == "" ? "qrc:/images/book.png" : StandardPaths.writableLocation(StandardPaths.AppDataLocation) + "/" + book.image
                sourceSize.width: parent.width - columnImg.padding * 2
                sourceSize.height: parent.height
            }

            Button {
                id: button
                text: qsTr("Edit")

                anchors.topMargin: 30
                anchors.horizontalCenter: columnImg.horizontalCenter

                background: Rectangle {
                   anchors.margins: 10
                   implicitWidth: 80
                   implicitHeight: 30
                   color: button.down ? "#A0A0A0" : "#f6f6f6"
                   border.color: "#26282a"
                   border.width: 1
                   radius: 4
                }

                onClicked: root.editClicked()
            }

        } // end column

    } // end row

//    ScrollIndicator.vertical: ScrollIndicator {}
}
