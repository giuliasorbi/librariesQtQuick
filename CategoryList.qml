import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQml.Models 2.2
import QtQuick.Layouts 1.0
import book 1.0
import model 1.0
import catmodel 1.0
import category 1.0

ListView {
    id: list
    visible: true

    delegate: Item {
        height: 40
        width: parent.width
        Label {
            height: parent.height
            width: parent.width
            text: cname ? cname : ""
            elide: Label.ElideRight
            padding: 10

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.log("clicked: category row --> "+ index + ", name --> ", cname);
                    list.currentIndex = index;
                }
            }
        }
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
            text: qsTr("Categories List")
        }
        MenuSeparator {
            parent: header
            width: parent.width
            anchors.verticalCenter: parent.bottom
            visible: !list.atYBeginning
        }
    }
    highlight: Rectangle {
            radius: 5
            color: "#E0E0E0"
//            Behavior on y { SpringAnimation { spring: 5; damping: 0.3 } }
    }

    footer: Item {
        id: footer
        Text {
            id: footerText
            text: qsTr("You have " + model.count + " categories")
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
        topPadding: list.headerItem.height
    }
} // end list view
