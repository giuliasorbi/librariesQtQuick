#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QMap>
#include <QString>
#include "category.h"
#include "book.h"


class DataManager : public QObject
{
    Q_OBJECT
public:
    DataManager();
    QMap<int, Category> categories;
    QMap<int, Book> books;
};

#endif // MANAGER_H
