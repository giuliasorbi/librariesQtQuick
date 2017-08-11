#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QMap>
#include <QString>
#include "category.h"
#include "book.h"
#include "catmodel.h"
#include "datamodel.h"


class DataManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(DataModel* bookModel READ bookModel WRITE setBookModel NOTIFY bookModelChanged)
    Q_PROPERTY(CatModel* catModel READ catModel WRITE setCatModel NOTIFY catModelChanged)

public:
    DataManager(QObject *parent = nullptr);

    DataModel* bookModel() const { return m_bookModel; }
    CatModel* catModel() const { return m_catModel; }

    Q_INVOKABLE void setBookModel(DataModel* m) { m_bookModel = m; emit bookModelChanged(); }
    Q_INVOKABLE void setCatModel(CatModel* m) { m_catModel = m; emit catModelChanged(); }

    Q_INVOKABLE void saveBook(const int& row, const QString& name, const QString& description, const QString& author, const QString& image, const int& category);
    Q_INVOKABLE void deleteBook(const int& row);

    Q_INVOKABLE void saveCategory(const int& row, const QString& name, const QString& description);
    Q_INVOKABLE void deleteCategory(const int& row);

    Q_INVOKABLE QString getCategoryName(const int& catId) const;
    Q_INVOKABLE QStringList getBooksTitles(const QVector<int> books) const;

private:
    DataModel* m_bookModel;
    CatModel* m_catModel;

signals:
    void bookModelChanged();
    void catModelChanged();
};

#endif // MANAGER_H
