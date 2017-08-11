import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQml.Models 2.2
import QtQuick.Layouts 1.0
import Qt.labs.platform 1.0

import model 1.0



Item {
    id: root
    objectName: "delegate"

    Row {

        width: parent.width
        height: parent.height
        padding: 10

        Column {
            id: imgColumn
            width: parent.width / 6
            height: parent.height
            Image {
                id: cover
                source: !img || img == "" ? "qrc:/images/book.png" : img=="tour.jpg" ? "qrc:/images/tour.jpg" : img=="effective.jpg" ? "qrc:/images/effective.jpg" :StandardPaths.writableLocation(StandardPaths.AppDataLocation) + "/" + img;
                sourceSize.width: parent.width
                sourceSize.height: parent.height - 20
            }
        }

        Column {
            id: textColumn
            width: parent.width - imgColumn.width
            leftPadding: 10
            Label {
                id: text
                width: parent.width - parent.leftPadding * 2
                text: title ? title: ""
                font.bold: true

                elide: Label.ElideRight
            }
            Label {
                width: parent.width - 30
                text: desc ? desc : ""
                elide: Label.ElideRight
            }
            Label {
                width: parent.width - 20
                topPadding: 1
                text: root.ListView.view.manager ? root.ListView.view.manager.getCategoryName(category)  : "" //.manager.
                font.italic: true
                font.pointSize: 10
                elide: Label.ElideRight
            }
        }

    } // end row

    MouseArea {
        anchors.fill: parent
        onClicked: {
            console.log("clicked: row --> "+ index + ", title --> ", title);
            root.ListView.view.currentIndex = index;
        }
    }
}
