#include "book.h"

Book::Book(QObject *parent)
    : QObject(parent)
{}

Book::Book(int id, QString name, QString desc, QString author, QString image, int category, QObject *parent)
    : m_id(id),
      m_name(name),
      m_description(desc),
      m_author(author),
      m_image(image),
      m_category(category),
      QObject(parent)
{}
