#ifndef CATEGORY_H
#define CATEGORY_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QDebug>

class Category: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString cname READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString desc READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(QVector<int> books READ books NOTIFY booksChanged)
    Q_PROPERTY(bool defaultCategory READ defaultCategory NOTIFY defaultChanged)


public:
    Category(QObject *parent = nullptr);
    Category(int id, QString name, QString description, QObject *parent = nullptr);
    QString name() const { return m_name; }
    QString description() const { return m_description; }
    int id() const { return m_id; }
    QVector<int> books() const { return m_books; }
    void removeBook(const int& bookId) { m_books.remove(m_books.indexOf(bookId)); }
    void addBook(const int& bookId) { m_books.append(bookId); }
    void setName(const QString& name) { m_name = name; emit(nameChanged()); }
    void setDescription(const QString& description) { m_description = description; emit(descriptionChanged()); }
    bool defaultCategory() { if (m_id == 0) return true; return false;}
private:
    int m_id;
    QString m_name;
    QString m_description;
    QVector<int> m_books;
signals:
    void nameChanged();
    void descriptionChanged();
    void booksChanged();
    void defaultChanged();

};

#endif // CATEGORY_H
