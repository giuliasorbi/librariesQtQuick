#include <QMap>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QImage>
#include <QStandardPaths>
#include "datamodel.h"
#include "datamanager.h"

DataModel::DataModel(QObject* parent)
    : QAbstractListModel(parent)
{}


QVariant DataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }
    if (index.row() >= books.size()) {
        return QVariant();
    }

    auto i = books.begin() + index.row();

    if (role == TitleRole) {
        return i.value()->name();
    } else if (role == DescRole) {
        return i.value()->description();
    } else if (role == CategoryRole) {
        return i.value()->category();
    } else if (role == ImgRole) {
        return i.value()->image();
    }

    return QVariant();
}

int DataModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0) {
        return 0;
    }
    return books.size();
}

bool DataModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (row >= books.size()) {
        return false;
    }
    beginRemoveRows(parent, row, row + count - 1);
//    auto i = books.begin() + row;
    books.remove(getBookId(row));
    endRemoveRows();

    emit countChanged();
    return true;
}

void DataModel::fetchMore(const QModelIndex &parent)
{
    Q_UNUSED(parent)
    beginInsertRows(QModelIndex(), books.size(), books.size() + 2);
    QString descr = "The C++11 standard allows programmers to express ideas more clearly, simply, and directly, and to write faster, more efficient code. Bjarne Stroustrup, the designer and original implementer of C++, thoroughly covers the details of this language and its use in his definitive reference,The C++ Programming Language, Fourth Edition.";
    books.insert(books.size(), new Book(books.size(), "A Tour of C++", descr, "Bjarne Stroustrup", "tour.jpg", 1));
    descr = "Coming to grips with C++11 and C++14 is more than a matter of familiarizing yourself with the features they introduce (e.g., auto type declarations, move semantics, lambda expressions, and concurrency support). The challenge is learning to use those features effectively -- so that your software is correct, efficient, maintainable, and portable.";
    books.insert(books.size(), new Book(books.size(), "Effective Modern C++", descr, "Scott Meyers", "effectiveModernC++.jpg", 1));
    books.insert(books.size(), new Book(books.size(), "Title Book Example", "Description Example", "Author Example", "", 2));

    endInsertRows();

    emit countChanged();
}


bool DataModel::canFetchMore(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    bool ret =  books.size() < 2 && m_canFetch;

    return ret;
}

QHash<int, QByteArray> DataModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "title";
    roles[DescRole] = "desc";
    roles[ImgRole] = "img";
    roles[CategoryRole] = "category";
    return roles;
}

int DataModel::addBook(const QString& name, const QString& description, const QString& author, const QString& image, const int& category)
{
    auto newId = 0;
    if ( !books.empty() ) {
        newId = books.keys().last();
        newId++;
    }
    beginInsertRows(QModelIndex(), books.size(), books.size());
    books.insert(newId, new Book(newId, name, description, author, image, category));
    endInsertRows();

    emit countChanged();
    return newId;
}

bool DataModel::updateBook(const int& row, const QString& name, const QString& description, const QString& author, const QString& image, const int& category)
{
    bool updateCategory = false;
    auto i = books.begin() + row;

    if (i.value()->name() != name) {
        i.value()->setName(name);
    }
    if (i.value()->description() != description) {
        i.value()->setDescription(description);
    }
    if (i.value()->author() != author) {
        i.value()->setAuthor(author);
    }
    if (i.value()->image() != image) {
        i.value()->setImage(image);
    }
    if (i.value()->category() != category) {
        i.value()->setCategory(category);
        updateCategory = true;
    }

    QModelIndex ind = index(row, 0);
    emit (dataChanged(ind, ind));
    return updateCategory;
}

void DataModel::updateCategoryInfo(const int& catId, const bool& catRemovedFlag)
{
    auto row = 0;
    for (auto& b : books) {
        if (b->category() == catId) {
            if (catRemovedFlag) { // catId removed
                b->setCategory(0);
            } else {
                b->setCategory(catId);
            }
            QModelIndex ind = index(row, 0);
            emit (dataChanged(ind, ind));
        }
        row++;
    }
}

void DataModel::deleteBook(const int& row)
{
    QModelIndex i = index(row, 0, QModelIndex());
    removeRows(row, 1, i.parent());
    if (m_canFetch) {
        m_canFetch = false;
    }
}

Book* DataModel::get(const int& row) const
{
    auto i = books.begin() + row;
    qDebug() << "get book" << i.value()->name() << " (" << i.value()->id() << ") of index " << row;
    return i.value();
}

void DataModel::saveImage(const QString& url)
{
    QImage* imageObject = new QImage();
    imageObject->load(QUrl(url).toLocalFile());
    QString name = url.right(url.size()-url.lastIndexOf("/")-1);
    imageObject->save(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/" + name );
}
