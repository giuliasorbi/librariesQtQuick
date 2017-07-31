#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick>
#include "datamodel.h"
#include "book.h"
#include "category.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    qmlRegisterType<Book>("book", 1, 0, "Book");
    qmlRegisterType<Category>("category", 1, 0, "Category");
    qmlRegisterType<DataModel>("model", 1, 0, "DataModel");

    QQmlApplicationEngine engine;
//    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
//    if (engine.rootObjects().isEmpty())
//        return -1;
    QQmlComponent component(&engine, QUrl("qrc:/main.qml"));
    QObject *object = component.create();
    QObject *stackview = object ->findChild<QObject*>("stackView");
    QObject *model = object->findChild<QObject*>("stackView")->findChild<QObject*>("bookList")->findChild<QObject*>("model");

    QObject::connect(stackview, SIGNAL(saveBook(const int&, const QString&, const QString&, const QString&, const QString&, const int&)), model, SLOT(onSaveBook(const int&, const QString&, const QString&, const QString&, const QString&, const int&)));
    QObject::connect(stackview, SIGNAL(saveImage(const QString&)), model, SLOT(onSaveImage(const QString&)));
    QObject::connect(stackview, SIGNAL(deleteBook(const int&)), model, SLOT(onDeleteBook(const int&)));


    return app.exec();
}
