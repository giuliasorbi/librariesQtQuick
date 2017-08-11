#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <QObject>
#include <QtSql>
#include <QString>

class DataStorage : public QObject
{
    Q_OBJECT    
public:
    DataStorage(QObject *parent = nullptr);
    bool initDb();
    QSqlError addBook(const int& id, const QString& title, const QString& description, const QString& author, const QString& image, const int& category);
    QSqlError addCategory(const int& id, const QString& name, const QString& description);

    QList<QList<QVariant>> selectBook(const int& offset, const int& limit) const;
    QList<QList<QVariant>> selectCategory(const int& offset, const int& limit) const;

    int countBooks() const;
    int countCategories() const;
    QVector<int> selectCategoryBooks(const int& catId) const;

    bool deleteBook(const int& id);
    bool deleteCategory(const int& id);
    bool updateCategory(const int& id, const QString& name, const QString& description);
    bool updateBook(const int& id, const QString& title, const QString& description, const QString& author, const QString& image, const int& category);
    bool updateBookField(const int& id, const QString& column, const QVariant& newValue);
    int selectLastBookId() const;
    int selectLastCatId() const;

    QString selectCategoryName(const int & id) const;

    int selectCategoryId(const int& row);

    QStringList selectCategories() const;

    QStringList getBooksTitles(const QVector<int> bookIds) const;

};

#endif // DATASTORAGE_H
