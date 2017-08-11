#include <QMap>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QImage>
#include <QStandardPaths>
#include "datamodel.h"
#include "datamanager.h"
#include "datastorage.h"

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
//    qDebug() << "rowCount " << books.size();
    return books.size();
}

bool DataModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (row >= books.size()) {
        return false;
    }
    beginRemoveRows(parent, row, row + count - 1);

    auto id = getBookId(row);
    books.remove(id);
    m_dataStorage->deleteBook(id); // handle return value
    endRemoveRows();
    m_offset--;
    emit countChanged();
    return true;
}

void DataModel::fetchMore(const QModelIndex& parent)
{
    Q_UNUSED(parent)
    qDebug() << "DataModel::fetchMore";
    auto toFetch = m_dataStorage->countBooks() - books.size();
    auto size = qMin(m_size, toFetch);
    QList<QList<QVariant>> bookParam = m_dataStorage->selectBook(m_offset, size);

    beginInsertRows(QModelIndex(), books.size(), books.size() + size - 1);
    for ( const auto& b : bookParam ) {
        books.insert(b.at(0).toInt(), new Book(b.at(0).toInt(), b.at(1).toString(), b.at(2).toString(), b.at(3).toString(), b.at(4).toString(), b.at(5).toInt()  ));
    }
    endInsertRows();
    m_offset += size;
    emit countChanged();
}

bool DataModel::canFetchMore(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    qDebug() << "books.size() " << books.size();
    bool ret =  books.size() <  m_dataStorage->countBooks();
    qDebug() << "---canFetchMore books " << ret;

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
    auto newId = m_dataStorage->selectLastBookId() + 1;
    beginInsertRows(QModelIndex(), books.size(), books.size());
    books.insert(newId, new Book(newId, name, description, author, image, category));

    m_dataStorage->addBook(newId, name, description, author, image, category);
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
    m_dataStorage->updateBook(i.value()->id(), name, description, author, image, category);
    return updateCategory;
}

void DataModel::updateCategoryInfo(const int& catId, const bool& catRemovedFlag)
{
    auto row = 0;
    for (auto& b : books) {
        if (b->category() == catId) {
            if (catRemovedFlag) { // catId removed
                b->setCategory(0);
                m_dataStorage->updateBookField(b->id(), "category", 0);
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

QStringList DataModel::getBooksTitles(const QVector<int> books) const
{
    return m_dataStorage->getBooksTitles(books);
}
