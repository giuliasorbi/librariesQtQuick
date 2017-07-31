import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQml.Models 2.2
import model 1.0

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

        initialItem: Page {
            ToolBar {
                id: header
                width: parent.width
//                parent: window.overlay
                ToolButton {
                    text: qsTr("Add Book")

                    onClicked:  {
                        var categories = bookList.model.getCategories();
                        stackView.push(Qt.resolvedUrl("qrc:/EditBook.qml"), {"bookRowIndex": bookList.model.rowCount() + 1, "bookName": "", "bookDescription": "", "bookAuthor": "", "bookImage": "", "bookCategoryId": "", "categories": categories } );
                    }
                }
//                Label {
//                    id: label
//                    anchors.centerIn: parent
//                    text: "Main ToolBar"
//                }
            }

            BookList {
                objectName: "bookList"
                id: bookList
                y: header.height
                width: window.width / 3
                height: window.height - header.height
                visible: true
                model: DataModel {
                    objectName: "model"
                    id: dataModel
                }
            }

            BookDetail {
                book: bookList.currentIndex != -1  ? bookList.model.get(bookList.currentIndex) : null

                anchors.fill: parent
                anchors.topMargin: header.height
                anchors.leftMargin: bookList.width
                onEditClicked: {
                    var categories = bookList.model.getCategories();
//                    stackView.push("qrc:/EditBook.qml")
//                    console.log(book.name);
//                    console.log(book.image);
                    stackView.push(Qt.resolvedUrl("qrc:/EditBook.qml"), {"bookRowIndex": bookList.currentIndex, "bookName": book.name, "bookDescription": book.description, "bookAuthor": book.author, "bookImage": book.image, "bookCategoryId": book.category, "categories": categories } );
                }
                onDeleteClicked: {
                    stackView.deleteBook(bookList.currentIndex);
                    bookList.decrementCurrentIndex()
                }

            } // end BookDetail

        }
    }
}
