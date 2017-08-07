#ifndef MODEL_H
#define MODEL_H

#include <QMap>
#include <QAbstractItemModel>
//#include "category.h"
#include "book.h"

class DataModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)

public:
    enum BookRoles {
        TitleRole = Qt::UserRole + 1,
        DescRole,
        ImgRole,
        CategoryRole
    };
    DataModel(QObject *parent = nullptr);
    QVariant data(const QModelIndex &index, int role) const override;
    int rowCount(const QModelIndex &parent) const override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    void fetchMore(const QModelIndex &parent  = QModelIndex()) override;
    bool canFetchMore(const QModelIndex &parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;

    int addBook(const QString& name, const QString& description, const QString& author, const QString& image, const int& category);
    bool updateBook(const int& row, const QString& name, const QString& description, const QString& author, const QString& image, const int& category);
    void updateCategoryInfo(const int& catId, const bool& catRemovedFlag);
    void deleteBook(const int& row);
    int getBookId(const int& row) const { return (books.begin() + row).value()->id(); }
    int getBookCategory(const int& id) { return books.value(id)->category(); }
    int count() const { return books.size(); }
    QString getBookName(const int& id) const { return books.value(id)->name(); }

    Q_INVOKABLE Book* get(const int& row) const;
    Q_INVOKABLE void saveImage(const QString& url);

signals:
    void countChanged();

private:
    QMap<int, Book*> books;
    bool m_canFetch = true;

};

#endif // MODEL_H
