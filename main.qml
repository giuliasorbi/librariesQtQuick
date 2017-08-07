import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQml.Models 2.2
import model 1.0
import catmodel 1.0
import manager 1.0

ApplicationWindow {
    id: window
    objectName: "window"
    visible: true
    width: 640
    height: 480
    title: qsTr("Libraries")

    StackView {
        id: stackView
        objectName: "stackView"
        anchors.fill: parent

        signal saveBook(int row, string name, string description, string author, string image, int category)
        signal saveImage(string url)
        signal deleteBook(int row)
        signal deleteCategory(int row)
        signal saveCategory(int row, string name, string description)

        onSaveBook: dataManager.saveBook(row, name, description, author, image, category);
        onDeleteBook: dataManager.deleteBook(row);
        onSaveImage: dataModel.saveImage(url);
        onDeleteCategory: dataManager.deleteCategory(row);
        onSaveCategory: dataManager.saveCategory(row, name, description);

        initialItem: Page {
            id: bookPage
            objectName: "bookPage"
            ToolBar {
                id: bar
                width: parent.width

                ToolButton {
                    hoverEnabled: true
                    padding: 4
                    ToolTip.visible: hovered
                    ToolTip.text: qsTr("Categories Management")
                    Image {
                        id: iconCat
                        source: "qrc:/images/category.png"
                        x: parent.padding
                        y: x
                        height: bar.height - parent.padding * 2
                        width: height
                    }
                    onClicked: stackView.push(Qt.resolvedUrl("qrc:/CategoriesWindow.qml"), { "catModel": categoryModel, "manager": dataManager } );
                }

                ToolButton {
                    hoverEnabled: true
                    padding: 4
                    ToolTip.visible: hovered
                    ToolTip.text: qsTr("Add Book")
                    anchors.right: parent.right
                    Image {
                        id: iconPlus
                        y: parent.padding
                        source: "qrc:/images/plus.png"
                        height: bar.height - parent.padding * 2
                        width: height
                    }
                    onClicked: stackView.push(Qt.resolvedUrl("qrc:/EditBook.qml"), {"bookIndexRow": -1, "bookName": "", "bookDescription": "", "bookAuthor": "", "bookImage": "", "bookCategoryId": "", "catModel": categoryModel});
                }
            } // end toolbar

            BookList {
                objectName: "bookList"
                property DataManager manager: null

                id: bookList
                y: bar.height
                width: window.width / 3
                height: window.height - bar.height
                visible: true
                focus: true
                model: dataModel;
                manager: dataManager;
                clip: true
            }

            BookDetail {
                id: bookDetail
                book: bookList.currentIndex != -1  ? bookList.model.get(bookList.currentIndex) : null
                cat: bookList.currentIndex != -1 ? categoryModel.getCategoryName(book.category) : ""
                anchors.fill: parent
                anchors.topMargin: bar.height
                anchors.leftMargin: bookList.width
                onEditClicked: stackView.push(Qt.resolvedUrl("qrc:/EditBook.qml"), {"bookIndexRow": bookList.currentIndex, "bookName": book.name, "bookDescription": book.description, "bookAuthor": book.author, "bookImage": book.image, "bookCategoryId": book.category, "catModel": categoryModel} );
                onDeleteClicked: stackView.deleteBook(bookList.currentIndex);

            } // end BookDetail

            Keys.onReturnPressed: {
                if (bookList.currentIndex != -1) {
                    bookDetail.editClicked();
                }
            }

            StackView.onActivated: bookList.forceActiveFocus();

        } // end page


    } // end stackview

    DataManager {
        id: dataManager
        Component.onCompleted: {
            dataManager.setBookModel(dataModel);
            dataManager.setCatModel(categoryModel);
        }
    }

    DataModel {
       id: dataModel
    }

    CatModel {
        id: categoryModel
        Component.onCompleted: categoryModel.init();
    }
}
