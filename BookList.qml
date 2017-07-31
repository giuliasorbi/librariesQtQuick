import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtQml.Models 2.2
import QtQuick.Layouts 1.0
import model 1.0

ListView {
    visible: true
    id: listView   
    delegate: BookListDelegate {
    }

    headerPositioning: ListView.OverlayHeader
    header: Pane {
        id: header
        z:2
        width: parent.width

        contentHeight: listHeader.height
        Label {
            width: parent.width
            id: listHeader
            text: qsTr("Books List")
        }

        MenuSeparator {
            parent: header
            width: parent.width
            anchors.verticalCenter: parent.bottom
            visible: !listView.atYBeginning
        }

    }

    highlight: Rectangle {
            radius: 5
            color: "#E0E0E0"
//            Behavior on y { SpringAnimation { spring: 5; damping: 0.3 } }
    }


    footer: Item {
        id: footer
        Text { text: qsTr("You have " + model.rowCount(listView.currentIndex) + " books"); font.pointSize: 10 ; padding: 8; anchors.centerIn: parent }
        width: parent.width
        height: 20

        MenuSeparator {
            parent: footer
            width: parent.width
            anchors.verticalCenter: parent.top
        }
    }


    ScrollIndicator.vertical: ScrollIndicator {}
}
