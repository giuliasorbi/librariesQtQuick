#ifndef CATMODEL_H
#define CATMODEL_H

#include <QMap>
#include <QAbstractItemModel>
#include "category.h"
//#include "book.h"

class CatModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(QStringList categories READ getCategories NOTIFY categoriesChanged)

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

    int count() const { return categories.size(); }

    void deleteCategory(const int& row);
    bool updateCategory(const int& row, const QString& name, const QString& description);
    void addCategory(const QString& name, const QString& description);

    void updateBook(const int& bookId, const int& newCategory, const int& flag);
    void deleteBook(const int& bookId, const int& category);

    int getCategoryId(const int& row) const;
    QStringList getCategories() const;

    Q_INVOKABLE void init();
    Q_INVOKABLE Category* get(const int& row) const;
    Q_INVOKABLE QString getCategoryName(const int& id) const { return categories.value(id)->name(); }

signals:
    void countChanged();
    void categoriesChanged();

private:
    QMap<int, Category*> categories;
    bool m_canFetch = true;

};

#endif // CATMODEL_H
