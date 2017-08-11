#include <QString>
#include <QDebug>
#include "category.h"

Category::Category(QObject *parent)
    : QObject(parent)
{}

Category::Category(int id, QString name, QString description, QObject *parent)
    : m_id(id),
      m_name(name),
      m_description(description),
      m_books(),
      QObject(parent)
{}
