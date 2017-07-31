#include <QMap>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "datamodel.h"

DataModel::DataModel(QObject* parent)
    : QAbstractListModel(parent)
{}


QVariant DataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }


    if (index.row() >= m_books.size()) {
        return QVariant();
    }

    auto i = m_books.begin() + index.row();

    if (role == TitleRole) {
        return i.value()->name();
    } else if (role == DescRole) {
        return i.value()->description();
    } else if (role == CategoryRole) {
        return m_categories.value(i.value()->category())->name();
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
    return m_books.size();

}

bool DataModel::setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole)
{
    qDebug() << "index row " << index.row() << " new value " << value.toString();
    qDebug() << m_books.size();
    auto i = m_books.begin() + index.row();
    qDebug() << i.value()->name();
//    Book* b = this->get(index.row());
//    qDebug() << "after get book";
//    qDebug() << "name " << b->name();
//     qDebug() << "name " << m_categories.value(0)->name();
//    m_books[index.row()]->set(value.toString());
     return true;
}


//bool DataModel::setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole)
//{

//    if (role != Qt::DisplayRole) {
//            return false;
//    }

//    QList<QVariant> list = value.toList(); // title, description, author, image, category
//    auto c = 0;
//    auto id = 0;
//    for (const auto& b : m_books) {
//        if (c == index.row()) {
//            id = b.id();
//            break;
//        }
//        c++;
//    }

//    if (!m_books.contains(id)) {
//        return false;
//    }
//    if (m_books.value(id).name() != list.at(0).toString()) {
//        m_books[id].setName(list.at(0).toString());
//    }
//    if (m_books.value(id).description() != list.at(1).toString()) {
//        m_books[id].setDescription(list.at(1).toString());
//    }
//    if (m_books.value(id).author() != list.at(2).toString()) {
//        m_books[id].setAuthor(list.at(2).toString());
//    }
//    if (m_books.value(id).image() != list.at(3).toString()) {
//          m_books[id].setImage(list.at(3).toString());
//    }
//    if (m_books.value(id).category() != list.at(4).toInt()) {
//        m_categories[m_books.value(id).category()].removeBook(m_books.value(id).id());
//        m_categories[list.at(4).toInt()].addBook(m_books.value(id).id());
//        m_books[id].setCategory(list.at(4).toInt());
//    }

//    emit (dataChanged(index,index));
//    emit (updateBookInfo(index));

//    return true;
//}

QVariant DataModel::headerData(int section, Qt::Orientation orientation, int role) const {
    Q_UNUSED(section)

    if (role != Qt::DisplayRole) {
        return QVariant();
    }
    if (orientation == Qt::Horizontal) {
        return QString("BookList");
    }
    return QVariant();
}


//Book DataModel::getBook(const int& row) const {
//    auto c = 0;
//    for (const auto& b : m_books) {
//        if (c == row) {
//            return m_books.value(b.id());
//        }
//        c++;
//    }
//}

//bool DataModel::removeRows(int row, int count, const QModelIndex &parent )
//{

//    beginRemoveRows(parent, row, row+count-1);
//    auto c = 0;
//    for (const auto& b : m_books) {
//        if (c == row) {
//            m_books.remove(b.id());
//            m_categories[b.category()].removeBook(b.id());
//            break;
//        }
//        c++;
//    }
//    endRemoveRows();

//    emit (dataChanged(parent, parent));

//    QModelIndex i = index(row, 0, QModelIndex());
//    if (!i.isValid()) {
//        i = index(row-1, 0, QModelIndex());
//    }
//    emit (updateBookInfo(i));
//    return true;
//}

//QString DataModel::getCategoryName(const int& id)
//{
//    return m_categories.value(id).name();
//}



//bool DataModel::addBook(QList<QVariant> bookParam) {
//    auto id = 0;
//    if ( !m_books.empty() ) {
//        id = m_books.keys().last();
//        id++;
//    }

//    beginInsertRows(QModelIndex(), m_books.size()-1, m_books.size()-1);
//    m_books.insert(id, Book(id, bookParam.at(0).toString(), bookParam.at(1).toString(), bookParam.at(2).toString(), bookParam.at(3).toString(), bookParam.at(4).toInt()));
//    m_categories[bookParam.at(4).toInt()].addBook(id);
//    endInsertRows();

//    return true;
//}

void DataModel::fetchMore(const QModelIndex &parent)
{
    Q_UNUSED(parent)
    m_categories.insert(0, new Category(0, "uncategorized books", "uncategorized books"));
    m_categories.insert(1, new Category(1, "computer science", "computer science category"));
    m_categories.insert(2, new Category(2, "action", "action category"));

    beginInsertRows(QModelIndex(), m_books.size(), m_books.size() + 2);
    QString descr = "The C++11 standard allows programmers to express ideas more clearly, simply, and directly, and to write faster, more efficient code. Bjarne Stroustrup, the designer and original implementer of C++, thoroughly covers the details of this language and its use in his definitive reference,The C++ Programming Language, Fourth Edition.";
    m_books.insert(0, new Book(0, "A Tour of C++", descr, "Bjarne Stroustrup", "tour.jpg", 1));
    m_categories[1]->addBook(0);

    descr = "Coming to grips with C++11 and C++14 is more than a matter of familiarizing yourself with the features they introduce (e.g., auto type declarations, move semantics, lambda expressions, and concurrency support). The challenge is learning to use those features effectively -- so that your software is correct, efficient, maintainable, and portable.";
    m_books.insert(1, new Book(1, "Effective Modern C++", descr, "Scott Meyers", "effectiveModernC++.jpg", 1));
    m_categories[1]->addBook(1);
    //    m_books.insert(1, Book(1, "Effective Modern C++", descr, "Scott Meyers", "effectiveModernC++.jpg", 1));
    m_books.insert(2, new Book(2, "Title Book Example", "Description Example", "Author Example", "", 2));
    m_categories[2]->addBook(2);
    qDebug() << "fetch";
    endInsertRows();
}


bool DataModel::canFetchMore(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_books.size() < 2;
}

QHash<int, QByteArray> DataModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "title";
    roles[DescRole] = "desc";
    roles[ImgRole] = "img";
    roles[CategoryRole] = "category";
    return roles;
}


Book* DataModel::get(const int& row) const
{
    auto i = m_books.begin() + row;
    return i.value();
}


Category* DataModel::getCategory(const int& row) const
{
    return m_categories.value(row);
}


void DataModel::onSaveBook(const int& row, const QString& name)
{
    qDebug() << "Model slot " <<  row << " name " << name;
    qDebug() << "size " << m_books.size();
    auto i = m_books.begin() + row;
    i.value()->setName(name);

//    m_books[0]->setName(name);
//    QModelIndex index= createIndex(row, 0);
//    this->setData(index, name, Qt::DisplayRole);

}

QStringList DataModel::getCategories()
{
    QStringList cat;
    for (const auto& c : m_categories) {
        cat.append(c->name());
    }
    return cat;
}
