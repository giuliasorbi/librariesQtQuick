#ifndef CATMODEL_H
#define CATMODEL_H

#include <QMap>
#include <QAbstractItemModel>
#include "category.h"
#include "datastorage.h"
//#include "book.h"

class CatModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(QStringList categories READ getCategories NOTIFY categoriesChanged)
    Q_PROPERTY(DataStorage* dataStorage READ dataStorage WRITE setDataStorage NOTIFY dataStorageChanged)


public:
    enum CategoryRoles {
        NameRole = Qt::UserRole + 1,
        DescRole
    };
    CatModel(QObject *parent = nullptr);
    QVariant data(const QModelIndex &index, int role) const override;
    int rowCount(const QModelIndex &parent) const override;
    bool removeRows(int row, int count, const QModelIndex &parent) override;
    QHash<int, QByteArray> roleNames() const override;

    int count() const { return m_dataStorage->countCategories(); }

    void deleteCategory(const int& row);
    bool updateCategory(const int& row, const QString& name, const QString& description);
    void addCategory(const QString& name, const QString& description);

    void updateBook(const int& bookId, const int& newCategory, const int& flag);
    void deleteBook(const int& bookId, const int& category);

    int getCategoryId(const int& row) const;
    QStringList getCategories() const;

    Q_INVOKABLE void fetchMore(const QModelIndex &parent  = QModelIndex()) override;
    bool canFetchMore(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE Category* get(const int& row) const;

    Q_INVOKABLE void setDataStorage(DataStorage* s) { m_dataStorage = s; }

    DataStorage* dataStorage() const { return m_dataStorage; }
    QString getCategoryName(const int& catId) const;

signals:
    void countChanged();
    void categoriesChanged();
    void dataStorageChanged();

private:
    QMap<int, Category*> categories;

    const int m_size = 6;
    int m_offset = 0;
    DataStorage* m_dataStorage;

};

#endif // CATMODEL_H
