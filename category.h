#ifndef CATEGORY_H
#define CATEGORY_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QDebug>

class Category: public QObject
{
Q_OBJECT
     Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
public:
    Category(QObject *parent = nullptr);
    Category(int id, QString name, QString description, QObject *parent = nullptr);
    QString name() const { return m_name; }
    QString description() const { return m_description; }
    int id() const {return m_id; }
    QVector<int> books() const { return m_books; }
    void removeBook(const int& bookId) { m_books.remove(m_books.indexOf(bookId)); }
    void addBook(const int& bookId) { m_books.append(bookId); }
    void setName(const QString& name) { m_name = name; }
    void setDescription(const QString& description) { m_description = description; }
private:
    int m_id;
    QString m_name;
    QString m_description;
    QVector<int> m_books;
signals:
    void nameChanged();
};

#endif // CATEGORY_H
