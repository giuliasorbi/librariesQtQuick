#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick>
#include <QDir>
#include "datamanager.h"
#include "datamodel.h"
#include "catmodel.h"
#include "book.h"
#include "category.h"
#include "datastorage.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    qmlRegisterType<DataStorage>("storage", 1, 0, "DataStorage");
    qmlRegisterType<DataManager>("manager", 1, 0, "DataManager");
    qmlRegisterType<Book>("book", 1, 0, "Book");
    qmlRegisterType<Category>("category", 1, 0, "Category");
    qmlRegisterType<DataModel>("model", 1, 0, "DataModel");
    qmlRegisterType<CatModel>("catmodel", 1, 0, "CatModel");
    if (!QDir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)).exists()) {
        QDir().mkdir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    }
    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
