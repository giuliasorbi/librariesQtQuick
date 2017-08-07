#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick>
#include "datamanager.h"
#include "datamodel.h"
#include "catmodel.h"
#include "book.h"
#include "category.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    qmlRegisterType<DataManager>("manager", 1, 0, "DataManager");
    qmlRegisterType<Book>("book", 1, 0, "Book");
    qmlRegisterType<Category>("category", 1, 0, "Category");
    qmlRegisterType<DataModel>("model", 1, 0, "DataModel");
    qmlRegisterType<CatModel>("catmodel", 1, 0, "CatModel");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
