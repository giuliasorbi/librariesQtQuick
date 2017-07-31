#include <QMap>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QImage>
#include <QStandardPaths>
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
//    qDebug() << "data.....ROW " << index.row() << "id book " << i.value()->id();

    if (role == TitleRole) {
//        qDebug() <<i.value()->name();
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
    qDebug() << "row count " << m_books.size();
    return m_books.size();
}

bool DataModel::setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole)
{
    Q_UNUSED(role)
    // name, desc, author, image, category
//    qDebug() << "index row " << index.row();
//    qDebug() << m_books.size();

    QList<QVariant> list = value.toList(); // title, description, author, image, category

    auto i = m_books.begin() + index.row();

    if (i.value()->name() != list.at(0).toString()) {
        i.value()->setName(list.at(0).toString());
    }

    if (i.value()->description() != list.at(1).toString()) {
        i.value()->setDescription(list.at(1).toString());
    }

    if (i.value()->author() != list.at(2).toString()) {
        i.value()->setAuthor(list.at(2).toString());
    }
    if (i.value()->image() != list.at(3).toString()) {
        i.value()->setImage(list.at(3).toString());
    }

    if (i.value()->category() != list.at(4).toInt()) {

        m_categories[i.value()->category()]->removeBook(i.value()->id());
        m_categories[list.at(4).toInt()]->addBook(i.value()->id());
        i.value()->setCategory(list.at(4).toInt());
    }

    emit (dataChanged(index,index));
    return true;
}

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

bool DataModel::removeRows(int row, int count, const QModelIndex &parent)
{
    qDebug() << "remove";
    beginRemoveRows(parent, row, row + count - 1);
    auto i = m_books.begin() + row;
    m_books.remove(i.value()->id());
    m_categories[i.value()->category()]->removeBook(i.value()->id());
    endRemoveRows();
    qDebug() << "after remove" << m_books.size();

    qDebug() << "before data changed";
    emit (dataChanged(parent, parent));
    qDebug() << "after data changed";


    return true;

}

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


void DataModel::onSaveBook(const int& row, const QString& name, const QString& description, const QString& author, const QString& image, const int& category)
{
//    qDebug() << "Model slot " <<  row << " name " << name;
    QList<QVariant> bookParam {name, description, author, image, category};

    if (row >= m_books.size()) {    // new book
        auto id = 0;
        if ( !m_books.empty() ) {
            id = m_books.keys().last();
            id++;
        }
        beginInsertRows(QModelIndex(), m_books.size(), m_books.size());
        m_books.insert(id, new Book(id, bookParam.at(0).toString(), bookParam.at(1).toString(), bookParam.at(2).toString(), bookParam.at(3).toString(), bookParam.at(4).toInt()));
        m_categories[bookParam.at(4).toInt()]->addBook(id);
        endInsertRows();
    } else {    // edit book
        QModelIndex index = createIndex(row, 0);
        this->setData(index, bookParam, Qt::DisplayRole);
    }

}


void DataModel::onSaveImage(const QString& url)
{
    qDebug() << "Model slot " <<  url << " url";
    QImage* imageObject = new QImage();
    imageObject->load(QUrl(url).toLocalFile());
    QString name = url.right(url.size()-url.lastIndexOf("/")-1);
    imageObject->save(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/" + name );
}

QStringList DataModel::getCategories()
{
    QStringList cat;
    for (const auto& c : m_categories) {
        cat.append(c->name());
    }
    return cat;
}

void DataModel::onDeleteBook(const int& row)
{
    qDebug() << row;
     removeRows(row, 1, QModelIndex());
}
