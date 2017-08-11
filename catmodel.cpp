#include <QMap>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QImage>
#include <QStandardPaths>
#include "category.h"
#include "catmodel.h"
#include "datamanager.h"

CatModel::CatModel(QObject* parent)
    : QAbstractListModel(parent)
{}

QVariant CatModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (index.row() >= categories.size()) {
        return QVariant();
    }
    auto i = categories.begin() + index.row();

    if (role == NameRole) {
        return i.value()->name();
    } else if (role == DescRole) {
        return i.value()->description();
    }

    return QVariant();
}


int CatModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0) {
        return 0;
    }
    return categories.size();
}

bool CatModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (row >= categories.size()) {
        return false;
    }

    beginRemoveRows(parent, row, row + count - 1);
    auto i = categories.begin() + row;
    for (const auto& b : i.value()->books()) {
        categories.value(0)->addBook(b);
    }
    categories.remove(i.value()->id());
    m_dataStorage->deleteCategory(i.value()->id());
    endRemoveRows();

    m_offset--;
    emit countChanged();
    emit categoriesChanged();
    return true;
}

QHash<int, QByteArray> CatModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "cname";
    roles[DescRole] = "desc";
    return roles;
}

void CatModel::deleteCategory(const int& row)
{
    QModelIndex ind = index(row, 0, QModelIndex());
    removeRows(row, 1, ind.parent());

}

bool CatModel::updateCategory(const int& row, const QString& name, const QString& description)
{
    bool updateBook = false;
    auto i = categories.begin() + row;

    if (i.value()->name() != name) {
        i.value()->setName(name);
//        emit categoriesChanged();
        updateBook = true;
    }

    if (i.value()->description() != description) {
        i.value()->setDescription(description);
    }

    QModelIndex ind = index(row, 0);
    emit (dataChanged(ind, ind));

    m_dataStorage->updateCategory(i.value()->id(), name, description);

    return updateBook;
}

void CatModel::addCategory(const QString& name, const QString& description)
{
//    auto newId = 0;
//    if ( !categories.empty() ) {
//        newId = categories.keys().last();
//        newId++;
//    }
    auto newId = m_dataStorage->selectLastCatId() + 1;

    beginInsertRows(QModelIndex(), categories.size(), categories.size());
    categories.insert(newId, new Category(newId, name, description));
    m_dataStorage->addCategory(newId, name, description);
    endInsertRows();

    emit countChanged();
//    emit categoriesChanged();
}

void CatModel::updateBook(const int& bookId, const int& newCategory, const int& flag)
{
    if (flag) { // edit book
        for ( auto& c : categories) {
           if ( c->books().contains(bookId) ) {
               c->removeBook(bookId);
               break;
           }
        }
    }
    if (categories.contains(newCategory)) {
        categories.value(newCategory)->addBook(bookId);
    }
}

void CatModel::deleteBook(const int& bookId, const int& category)
{
    if (categories.contains(category)) {
        categories[category]->removeBook(bookId);
    }
}

int CatModel::getCategoryId(const int& row) const
{
    if (row < categories.size()) {
        return (categories.begin() + row).value()->id();
    } else {
       return m_dataStorage->selectCategoryId(row);
    }
}


QStringList CatModel::getCategories() const
{
    if (categories.size() == m_dataStorage->countCategories()) {
        QStringList cat;
        for (const auto& c : categories) {
            cat.append(c->name());
        }
        return cat;
    } else {
        return m_dataStorage->selectCategories();
    }
}

void CatModel::fetchMore(const QModelIndex& parent)
{
    Q_UNUSED(parent)
    qDebug() << "CatModel::fetchMore";
    int toFetch = m_dataStorage->countCategories() - categories.size();
    int size = qMin(m_size, toFetch);
    QList<QList<QVariant>> categoryParam = m_dataStorage->selectCategory(m_offset, size);

    beginInsertRows(QModelIndex(), categories.size(), categories.size() + size - 1);
    for ( const auto& c : categoryParam ) {
        categories.insert(c.at(0).toInt(), new Category(c.at(0).toInt(), c.at(1).toString(), c.at(2).toString() ));

        for (const auto& bookId : m_dataStorage->selectCategoryBooks(c.at(0).toInt())) {
            categories[c.at(0).toInt()]->addBook(bookId);
        }
    }
    endInsertRows();
    m_offset += size;

    emit countChanged();
//    emit categoriesChanged();
}

bool CatModel::canFetchMore(const QModelIndex &parent ) const
{
    Q_UNUSED(parent)
    qDebug() << "categories.size() " << categories.size();
    bool ret =  categories.size() <  m_dataStorage->countCategories();
    qDebug() << "---canFetchMore  categories" << ret;

    return ret;
}

Category* CatModel::get(const int& row) const
{
    auto i = categories.begin() + row;
    return i.value();
}

QString CatModel::getCategoryName(const int& catId) const
{
    if (categories.contains(catId)) {
        return categories.value(catId)->name();
    } else {
        return m_dataStorage->selectCategoryName(catId);
    }
}
