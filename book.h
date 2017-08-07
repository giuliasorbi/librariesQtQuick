#ifndef BOOK_H
#define BOOK_H

#include <QDebug>
#include <QObject>
#include <QString>
#include <QVector>

class Book : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

    Q_PROPERTY(QString description READ description() WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(QString author READ author WRITE setAuthor NOTIFY authorChanged)
    Q_PROPERTY(QString image READ image WRITE setImage NOTIFY imageChanged)
    Q_PROPERTY(int category READ category() WRITE setCategory NOTIFY categoryChanged)

public:
    Book(QObject *parent = nullptr);
    Book(int id, QString name, QString desc, QString author, QString image, int category, QObject *parent = nullptr);
    int id() const { return m_id; }
    QString name() const { return m_name; }
    QString author() const { return m_author; }
    QString description() const { return m_description; }
    QString image() const { return m_image; }
    int category() const { return m_category; }
    void setName(const QString& name) { m_name = name; emit(nameChanged()); }

    void setAuthor(const QString& a) { m_author = a; emit(authorChanged()); }
    void setDescription(const QString& desc) { m_description = desc; emit(descriptionChanged()); }
    void setCategory(const int& cat) { m_category = cat; emit(categoryChanged()); }
    void setImage(const QString& image) { m_image = image; emit(imageChanged()); }
private:
    int m_id;
    QString m_name;
    QString m_description;
    QString m_author;
    QString m_image;
    int m_category;
signals:
    void nameChanged();
    void descriptionChanged();
    void authorChanged();
    void imageChanged();
    void categoryChanged();
    void idChanged();

};

#endif // BOOK_H

