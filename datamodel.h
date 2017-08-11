#ifndef MODEL_H
#define MODEL_H

#include <QMap>
#include <QAbstractItemModel>
//#include "category.h"
#include "book.h"
#include "datastorage.h"

class DataModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(DataStorage* dataStorage READ dataStorage WRITE setDataStorage NOTIFY dataStorageChanged)
    Q_PROPERTY(int sortRole READ sortRole NOTIFY sortRoleChanged)

public:
    enum BookRoles {
        IdRole = Qt::UserRole + 1,
        TitleRole,
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
    int sortRole() const { return roleNames().key("title"); }
    int addBook(const QString& name, const QString& description, const QString& author, const QString& image, const int& category);
    bool updateBook(const int& row, const QString& name, const QString& description, const QString& author, const QString& image, const int& category);
    void updateCategoryInfo(const int& catId, const bool& catRemovedFlag);
    void deleteBook(const int& row);
    int getBookId(const int& row) const { return (books.begin() + row).value()->id(); }
    int getBookCategory(const int& id) { return books.value(id)->category(); }
    int count() const { return m_dataStorage->countBooks(); }

    Q_INVOKABLE Book* get(const int& row) const;
    Q_INVOKABLE void saveImage(const QString& url);
    Q_INVOKABLE void setDataStorage(DataStorage* s) { m_dataStorage = s; }

    DataStorage* dataStorage() const { return m_dataStorage; }
    QStringList getBooksTitles(const QVector<int> books) const;

signals:
    void countChanged();
    void dataStorageChanged();
    void sortRoleChanged();

private:
    QMap<int, Book*> books;
    int m_offset = 0;
    const int m_size = 6;
    DataStorage* m_dataStorage;
};

#endif // MODEL_H
