#ifndef MODEL_H
#define MODEL_H

#include <QMap>
#include <QAbstractItemModel>
#include "category.h"
#include "book.h"

class DataModel : public QAbstractListModel
{
Q_OBJECT
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
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Q_INVOKABLE bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
//    QString getCategoryName(const int& id);
//    bool addBook(QList<QVariant> bookParam);
    bool canFetchMore(const QModelIndex &parent) const override;
    void fetchMore(const QModelIndex &parent) override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE Book* get(const int& row) const;
    Q_INVOKABLE Category* getCategory(const int& categoryId) const;
    Q_INVOKABLE QStringList  getCategories();

    Q_INVOKABLE QString bookCategory(const int& row) const { return m_categories.value(m_books.value(row)->category())->name(); }
private:
    QMap<int, Book*> m_books;
    QMap<int, Category*> m_categories;
signals:
    void updateBookInfo(const QModelIndex&);

public slots:
    void onSaveBook(const int& row, const QString& name, const QString& description, const QString& author, const QString& image, const int& category);
    void onSaveImage(const QString& url);
    void onDeleteBook(const int& row);

};

#endif // MODEL_H
