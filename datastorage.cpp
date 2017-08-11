#include "datastorage.h"
#include <QtSql>
#include <QDebug>
#include <QString>
#include <QStandardPaths>
DataStorage::DataStorage(QObject* parent)
    : QObject(parent)
{
    initDb();
}

bool DataStorage::initDb()
{
    QString dbName = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/library.sqlite3";
//    qDebug() << "dbName " << dbName;

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);

    if (!db.open()) {
        qDebug() << "cannot open database: " << db.lastError().text();  // Returns information about the last error that occurred on the database.
        return false;
    } else {
        qDebug() << "database opened";
    }

    QStringList tables = db.tables();

    if (!tables.contains("books", Qt::CaseInsensitive) && !tables.contains("categories", Qt::CaseInsensitive)) {
        QSqlQuery q;
        if (!q.exec("CREATE TABLE books(id integer primary key, title text, description varchar, author varchar, image varchar, category integer)")) {
            qDebug() << "create table book error: " << q.lastError().text();
            return false;
        }
        if (!q.exec("CREATE TABLE categories(id integer primary key, name text, description text)")) {
            qDebug() << "create table categories error: " << q.lastError().text();
            return false;
        }

        // -------------------------- init categories --------------------------

        if (addCategory(0, "uncategorized books", "uncategorized books").type() != QSqlError::NoError) {
            return false;
        }
        if (addCategory(1, "computer science", "computer science category").type() != QSqlError::NoError) {
            return false;
        }
        if (addCategory(2, "action", "action category").type() != QSqlError::NoError) {
            return false;
        }

        for (auto i = 3; i < 10; i++) {
            if (addCategory(i, "CategoryName" +  QString::number(i), "Description").type() != QSqlError::NoError) {
                return false;
            }
        }

        // -------------------------- init books --------------------------

        QString descr = "The C++11 standard allows programmers to express ideas more clearly, simply, and directly, and to write faster, more efficient code. Bjarne Stroustrup, the designer and original implementer of C++, thoroughly covers the details of this language and its use in his definitive reference,The C++ Programming Language, Fourth Edition.";
        if (addBook(0, "A Tour of C++", descr, "Bjarne Stroustrup", "tour.jpg", 1).type() != QSqlError::NoError) {
            return false;
        }

        descr = "Coming to grips with C++11 and C++14 is more than a matter of familiarizing yourself with the features they introduce (e.g., auto type declarations, move semantics, lambda expressions, and concurrency support). The challenge is learning to use those features effectively -- so that your software is correct, efficient, maintainable, and portable.";
        if (addBook(1, "Effective Modern C++", descr, "Scott Meyers", "effective.jpg", 1).type() != QSqlError::NoError) {
            return false;
        }
        if (addBook(2, "Title Book Example", "Description Example", "Author Example", "", 2).type() != QSqlError::NoError) {
            return false;
        }

        for (auto i = 3; i < 40; i++) {
            if (addBook(i, "TitleBook" +  QString::number(i), "Description", "author", "", 0).type() != QSqlError::NoError) {
                return false;
            }
        }
        QStringList tables = db.tables();
        qDebug() << "new tables: #tables =" << tables.size();

    } else {
        QStringList tables = db.tables();
        qDebug() << "tables ok: #tables =" << tables.size();
    }

    return true;
}


QSqlError DataStorage::addBook(const int& id, const QString& title, const QString& description, const QString& author, const QString& image, const int& category)
{
    QSqlQuery q;
    if (!q.exec(QString("INSERT INTO books(id, title, description, author, image, category) "
                        "VALUES (%1, '%2', '%3', '%4', '%5', %6)").arg(id).arg(title).arg(description).arg(author).arg(image).arg(category))) {
        qDebug() << "addBook error " << id << " " << title << ":" << q.lastError().text();
        return q.lastError();
    }

    return QSqlError();
}

QSqlError DataStorage::addCategory(const int& id, const QString& name, const QString& description)
{
    QSqlQuery q;
    if (!q.exec(QString("INSERT INTO categories(id, name, description)"
                        "VALUES( %1, '%2', '%3')").arg(id).arg(name).arg(description))) {
        qDebug() << "addCategory error " << id << " " << name << ":" << q.lastError().text();
        return q.lastError();
    }
    return QSqlError();
}

QList<QList<QVariant>> DataStorage::selectBook(const int& offset, const int& limit) const //offset: start index record, limit: #of record to retrieve
{

    QList<QList<QVariant>> bookParam;
    QSqlQuery q;

    if(!q.exec(QString("SELECT id, title, description, author, image, category FROM books LIMIT %1, %2").arg(offset).arg(limit))) {
        qDebug() << "selectBook error " << q.lastError().text();
    }

    while (q.next()) {
        QList<QVariant> b;
        b.append(q.value(0).toInt()); // id
        b.append(q.value(1).toString()); // title
        b.append(q.value(2).toString()); //description
        b.append(q.value(3).toString()); //author
        b.append(q.value(4).toString()); //image
        b.append(q.value(5).toInt()); //category
        bookParam.append(b);
       }
    return bookParam;
}


int DataStorage::countBooks() const
{
    QSqlQuery q;
    if (!q.exec("select count (*) from books")) {
        qDebug() << "countBook error: " << q.lastError().text();
    }
    while(q.next()) {
        return q.value(0).toInt();
    }
    return 0;
}

QList<QList<QVariant>> DataStorage::selectCategory(const int& offset, const int& limit) const
{
    QList<QList<QVariant>> categoryParam;
    QSqlQuery q;

    if(!q.exec(QString("SELECT id, name, description FROM categories LIMIT %1, %2").arg(offset).arg(limit))) {
        qDebug() << "selectCategory error: " << q.lastError().text();
    }

    while (q.next()) {
        QList<QVariant> c;
        c.append(q.value(0).toInt()); // id
        c.append(q.value(1).toString()); // name
        c.append(q.value(2).toString()); //description
        categoryParam.append(c);
    }
    return categoryParam;
}

int DataStorage::countCategories() const
{
    QSqlQuery q;
    if (!q.exec("select count (*) from categories")) {
        qDebug() << "countCategories error: " << q.lastError().text();
    }
    while(q.next()) {
        return q.value(0).toInt();
    }
    return 0;
}

QVector<int> DataStorage::selectCategoryBooks(const int& catId) const
{
    QVector<int> bookList;
    QSqlQuery q;
    q.prepare("select id from books where category = :catId");
    if (!q.exec(QString("select id from books where category = %1").arg(catId))) {
        qDebug() << "selectCategoryBooks error: " << q.lastError().text();
    }
    while(q.next()) {
        bookList.append(q.value(0).toInt());
    }
    return bookList;
}

bool DataStorage::deleteBook(const int& id)
{
    QSqlQuery q;
    return q.exec(QString("delete from books where id = %1").arg(id));
}

bool DataStorage::deleteCategory(const int& id)
{
    QSqlQuery q;
    return q.exec(QString("delete from categories where id = %1").arg(id));
}

bool DataStorage::updateCategory(const int& id, const QString& name, const QString& description)
{
    QSqlQuery q;
    return q.exec(QString("update categories set name = '%1', description = '%2' where id = %3 ").arg(name).arg(description).arg(id));
}

bool DataStorage::updateBook(const int& id, const QString& title, const QString& description, const QString& author, const QString& image, const int& category)
{
    QSqlQuery q;
    return q.exec(QString("update books set title = '%1', description = '%2', author = '%3', image = '%4', category = %5 "
                          "where id = %6").arg(title).arg(description).arg(author).arg(image).arg(category).arg(id));
}

bool DataStorage::updateBookField(const int& id, const QString& column, const QVariant& newValue)
{
    QSqlQuery q;
    q.prepare(QString("UPDATE books SET %1 = :value WHERE id = :id ").arg(column));
    q.bindValue(":value", newValue);
    q.bindValue(":id", id);
    if(!q.exec()) {
        qDebug() << "updateBookField error: " << q.lastError().text();
        return false;
    }
    return true;
}

int DataStorage::selectLastBookId() const
{
    QSqlQuery q;
    q.exec("select max(id) from books");
    while (q.next()) {
        return q.value(0).toInt();
    }
    return -1;
}

int DataStorage::selectLastCatId() const
{
    QSqlQuery q;
    q.exec("select max(id) from categories");
    while (q.next()) {
        return q.value(0).toInt();
    }
    return -1;
}

QString DataStorage::selectCategoryName(const int & id) const
{
    QSqlQuery q;
    if (q.exec(QString("select name from categories where id = %1").arg(id))) {
        while (q.next()) {
            return q.value(0).toString();
        }
    }
    qDebug() << "selectCategoryName error: " << q.lastError().text();
    return QString("");
}

QStringList DataStorage::getBooksTitles(const QVector<int> bookIds) const
{
    QStringList booksName;
    QSqlQuery q;
    for (const auto& id : bookIds) {
        if (q.exec(QString("select title from books where id = %1").arg(id))) {
            while (q.next()) {
                booksName.append(q.value(0).toString());
            }
        }
    }
    return booksName;
}

QStringList DataStorage::selectCategories() const
{
    QStringList names;
    QSqlQuery q;
    if (q.exec("select name from categories")) {
        while(q.next() ) {
            names.append(q.value(0).toString());
        }
    }
    return names;
}

int DataStorage::selectCategoryId(const int& row)
{
    QSqlQuery q;
    auto id = 0;
    if(!q.exec(QString("SELECT id FROM categories LIMIT %1, 1").arg(row))) {
        qDebug() << "selectCategoryId error: " << q.lastError().text();
    }
    while (q.next()) {
        id = q.value(0).toInt();
    }
    return id;
}
