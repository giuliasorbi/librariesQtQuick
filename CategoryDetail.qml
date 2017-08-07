import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQml.Models 2.2
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.0

import model 1.0
import catmodel 1.0
import book 1.0
import category 1.0

Pane {
    id: root
    property int margin: 10
    property Category category: null

    onCategoryChanged: {
        list.model.updateModel(category);
    }

    signal editClicked()
    signal deleteClicked()
    signal defaultCategoryFocus()

    GridLayout {
        id: gridLayout
        width: parent.width
        anchors.fill: parent 
        columns: 2
        rows: 3
        flow: GridLayout.TopToBottom

        Label {
            id: name
            width: parent.width
            Layout.row: 0
            Layout.margins: margin
            font.pixelSize: 22
            font.bold: true
            Layout.alignment: Qt.AlignCenter
            text: category == null ? "" : category.cname;
            Layout.columnSpan: 2
            visible: category == null ? false : true
        }

        Text {
            id: description
            Layout.margins: margin
            Layout.leftMargin: margin * 2

            width: parent.width / 2
            maximumLineCount: 15
            Layout.column: 0
            Layout.row: 1
            Layout.alignment: Qt.AlignCenter | Qt.AlignTop
            text: category == null ? "" : category.desc
            elide: Text.ElideRight
            wrapMode: Text.WordWrap
            Layout.fillHeight: true
            Layout.fillWidth: true
            visible: category == null ? false : true
        }

        ListView {
            id: list
            Layout.leftMargin: margin
            width: parent.width / 2; height: parent.height / 2
            headerPositioning: ListView.OverlayHeader
            Layout.row: 1
            Layout.column: 1
            Layout.alignment: Qt.AlignCenter | Qt.AlignTop
            header: Pane {
                id: header
                z: 2
                width: parent.width
                contentHeight: listHeader.height
                Label {
                    width: parent.width
                    id: listHeader
                    text: qsTr("Books")
                }
            }
            model : ListModel {
                id: model
                function updateModel(category) {
                    model.clear();
                    if (category.books.length == 0) {
                        model.append({"title": "Empty BookList"});
                    } else {
                        for (var i = 0; i < category.books.length; i++ ) {
                            model.append( {"title": root.manager.getBookName(category.books[i])} )
                        }
                    }
                }
            }

            delegate: Label {
                text: title
                width: parent.width
                height: 25
                elide: Text.ElideRight
            }
             visible: category == null ? false : true
             clip: true
             ScrollIndicator.vertical: ScrollIndicator {
                topPadding: list.headerItem.height
             }
        } // end listview

        Button {
            id: editButton
            Layout.margins: margin
            Layout.column: 0
            Layout.row: 4
            text: qsTr("Edit")
            background: Rectangle {
               anchors.margins: 10
               implicitWidth: 80
               implicitHeight: 30
               color: editButton.down ? "#A0A0A0" : "#f6f6f6"
               border.width: 1
               radius: 4
            }
//            enabled: !category.defaultCategory
            visible: category == null ? false : true
            onClicked: root.editClicked();

        }

        Button {
            id: deleteButton
            Layout.margins: margin
            Layout.column: 1
            Layout.row: 4
            text: qsTr("Delete")
            background: Rectangle {
               anchors.margins: 10
               implicitWidth: 80
               implicitHeight: 30
               color: deleteButton.down ? "#A0A0A0" : "#f6f6f6"
               border.width: 1
               radius: 4
            }
            enabled: category != null ? !category.defaultCategory : false
            visible: category == null ? false : true
            onClicked: {
                root.deleteClicked();
                root.defaultCategoryFocus();
            }
        }
    }
}
