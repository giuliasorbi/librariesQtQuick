import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtQml.Models 2.2
import QtQuick.Layouts 1.0
import model 1.0


Item {
    id: itemDelegate
    width: parent.width; height: 70

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
                source: img == "" ? "images/book.png" : "images/" + img
                sourceSize.width: parent.width
                sourceSize.height: parent.height - 20
            }
        }

        Column {
            id: textColumn
            width: parent.width - imgColumn.width
            leftPadding: 10
            Label {
                width: parent.width - 20
                text: title; font.bold: true
                elide: Label.ElideRight
            }

            Label {
                width: parent.width - 30
                wrapMode: Text.NoWrap
                text: desc
                elide: Label.ElideRight
            }

            Label {
                width: parent.width - 20
                wrapMode: Text.NoWrap
                topPadding: 1
                text: category
                font.italic: true
                font.pointSize: 10
                elide: Label.ElideRight
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            itemDelegate.ListView.view.currentIndex = index
            console.log("clicked: row --> ", index, ", title --> ", title)
        }
    }
}
