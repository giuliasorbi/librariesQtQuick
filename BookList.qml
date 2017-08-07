import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQml.Models 2.2
import QtQuick.Layouts 1.0
import model 1.0
import manager 1.0

ListView {
    id: listView

    delegate: BookListDelegate {

        width: parent.width
        height: 70
    }

    headerPositioning: ListView.OverlayHeader
    header: Pane {
        objectName: "hesder"
        id: headerPane
        z:2
        width: parent.width

        contentHeight: listHeader.height
        Label {
            width: parent.width
            id: listHeader
            text: qsTr("Books List")
        }

        MenuSeparator {
            parent: headerPane
            width: parent.width
            anchors.verticalCenter: parent.bottom
            visible: !listView.atYBeginning
        }

    }

    highlight: Rectangle {
            radius: 5
            color: "#E0E0E0"
    }


    footer: Item {
        id: footer
        Text {
            id: footerText
            text: qsTr("You have " + model.count + " books")
            font.pointSize: 10
            padding: 8
            anchors.centerIn: parent
        }

        width: parent.width
        height: 20

        MenuSeparator {
            parent: footer
            width: parent.width
            anchors.verticalCenter: parent.top
        }

    }

    ScrollIndicator.vertical: ScrollIndicator {
        topPadding: listView.headerItem.height
    }
}
