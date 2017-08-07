import QtQuick.Window 2.0
import QtQuick 2.6
import QtQuick.Controls 2.2
import Qt.labs.platform 1.0
import QtQuick.Layouts 1.3
import book 1.0
import model 1.0
import catmodel 1.0
import category 1.0
import manager 1.0

Page {
    id: root
    objectName: "categoriesPage"
    property CatModel catModel: null
    property DataManager manager: null

    ToolBar {
        id: header
        width: parent.width
        ToolButton {
            hoverEnabled: true
            padding: 4
            ToolTip.visible: hovered
            ToolTip.text: qsTr("Back")
            Image {
                id: iconBack
                y: parent.padding
                source: "qrc:/images/back.png"
                height: header.height - parent.padding * 2
                width: height
            }
            onClicked: {
                root.StackView.view.pop();
//                root.StackView.view.get(root.StackView.view.currentItem.StackView.index).setListFocus();
            }
        }
        ToolButton {
            hoverEnabled: true
            padding: 4
            ToolTip.visible: hovered
            ToolTip.text: qsTr("Add Category")
            anchors.right: parent.right
            Image {
                id: iconPlus
                y: parent.padding
                source: "qrc:/images/plus.png"
                height: header.height - parent.padding * 2
                width: height
            }

            onClicked: root.StackView.view.push(Qt.resolvedUrl("qrc:/EditCategory.qml"), {"categoryRowIndex": -1, "categoryName": "", "categoryDescription": "" });
        }
    }

    CategoryList {
        objectName: "catList"
        id: catList
        y: header.height
        width: root.width / 3
        height: root.height - header.height
        visible: true
        model: catModel
        focus: true
        clip: true
    }

    CategoryDetail {
        objectName: "catDetail"
        id: catDetail
        property DataManager manager : root.manager
        category: catList.currentIndex != -1  ? catList.model.get(catList.currentIndex) : null
        anchors.fill: parent
        anchors.topMargin: header.height
        anchors.leftMargin: catList.width
        onEditClicked: root.StackView.view.push(Qt.resolvedUrl("qrc:/EditCategory.qml"), {"categoryRowIndex": catList.currentIndex, "categoryName": category.cname, "categoryDescription": category.desc });
        onDeleteClicked: root.StackView.view.deleteCategory(catList.currentIndex);
        onDefaultCategoryFocus: catList.currentIndex = 0

    } // end CategoryDetail

    Keys.onReturnPressed: {
        if (catList.currentIndex != -1) {
            catDetail.editClicked();
        }
    }

   StackView.onActivated: catList.forceActiveFocus();

}


