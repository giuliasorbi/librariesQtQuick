#include <QDebug>
#include <QString>
#include "datamanager.h"
#include "datamodel.h"


DataManager::DataManager(QObject* parent)
    : QObject(parent)
{}

void DataManager::saveBook(const int& row, const QString& name, const QString& description, const QString& author, const QString& image, const int& category)
{
    if (row == -1) { // new book
        auto newId = m_bookModel->addBook(name, description, author, image, category);
        m_catModel->updateBook(newId, category, 0); // flag = 0 : new book

    } else {
        if (m_bookModel->updateBook(row, name, description, author, image, category)) {
             m_catModel->updateBook(m_bookModel->getBookId(row), category, 1);
        }

    }
}

void DataManager::deleteBook(const int& row)
{
    m_catModel->deleteBook(m_bookModel->getBookId(row), m_bookModel->getBookCategory(m_bookModel->getBookId(row)));
    m_bookModel->deleteBook(row);
}

void DataManager::saveCategory(const int& row, const QString& name, const QString& description)
{
    if (row == -1) {                                    // new category
        m_catModel->addCategory(name, description);
    } else {                                                // edit category
        if (m_catModel->updateCategory(row, name, description)) {
            m_bookModel->updateCategoryInfo(m_catModel->getCategoryId(row), 0); // flag = 0 : category not deleted
        }
    }
}

void DataManager::deleteCategory(const int& row)
{
    if ( m_catModel->getCategoryId(row) != 0) { // cannot delete "uncategorized book" category
        m_bookModel->updateCategoryInfo(m_catModel->getCategoryId(row), 1); // flag = 0 : category deleted
        m_catModel->deleteCategory(row);
    }
}

// -------------------------------------------------------------------------------------------------

QString DataManager::getCategoryName(const int& catId) const
{
    return m_catModel->getCategoryName(catId);
}

QString DataManager::getBookName(const int& bookId) const
{
    return m_bookModel->getBookName(bookId);
}

// -------------------------------------------------------------------------------------------------




