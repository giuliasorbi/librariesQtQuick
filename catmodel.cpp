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
//    qDebug() << "rowCount CATEGORIES" << categories.size();
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
    endRemoveRows();

//    emit dataChanged(parent, parent);
    emit countChanged();
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
    if (m_canFetch) {
        m_canFetch = false;
    }
    emit categoriesChanged();
}

bool CatModel::updateCategory(const int& row, const QString& name, const QString& description)
{
    bool updateBook = false;
    auto i = categories.begin() + row;

    if (i.value()->name() != name) {
        i.value()->setName(name);
        emit categoriesChanged();
        updateBook = true;
    }

    if (i.value()->description() != description) {
        i.value()->setDescription(description);
    }

    QModelIndex ind = index(row, 0);
    emit (dataChanged(ind, ind));

    return updateBook;
}

void CatModel::addCategory(const QString& name, const QString& description)
{
    auto newId = 0;
    if ( !categories.empty() ) {
        newId = categories.keys().last();
        newId++;
    }
    beginInsertRows(QModelIndex(), categories.size(), categories.size());
    categories.insert(newId, new Category(newId, name, description));
    endInsertRows();

    emit countChanged();
    emit categoriesChanged();
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
    categories.value(newCategory)->addBook(bookId);
}

void CatModel::deleteBook(const int& bookId, const int& category)
{
    categories[category]->removeBook(bookId);
}

int CatModel::getCategoryId(const int& row) const
{
    return (categories.begin() + row).value()->id();
}


QStringList CatModel::getCategories() const
{
    QStringList cat;
    for (const auto& c : categories) {
        cat.append(c->name());
    }
    return cat;
}


void CatModel::init()
{
    beginInsertRows(QModelIndex(), categories.size(), categories.size() + 2);

    categories.insert(categories.size(), new Category(categories.size(), "uncategorized books", "uncategorized books"));
    categories.insert(categories.size(), new Category(categories.size(), "computer science", "computer science category"));
    categories.insert(categories.size(), new Category(categories.size(), "action", "action category"));

    QString descr = "The C++11 standard allows programmers to express ideas more clearly, simply, and directly, and to write faster, more efficient code. Bjarne Stroustrup, the designer and original implementer of C++, thoroughly covers the details of this language and its use in his definitive reference,The C++ Programming Language, Fourth Edition.";
    categories[1]->addBook(0);
    descr = "Coming to grips with C++11 and C++14 is more than a matter of familiarizing yourself with the features they introduce (e.g., auto type declarations, move semantics, lambda expressions, and concurrency support). The challenge is learning to use those features effectively -- so that your software is correct, efficient, maintainable, and portable.";
    categories[1]->addBook(1);
    categories[2]->addBook(2);

    endInsertRows();

    emit countChanged();
    emit categoriesChanged();
}

Category* CatModel::get(const int& row) const
{
    auto i = categories.begin() + row;
    return i.value();
}
