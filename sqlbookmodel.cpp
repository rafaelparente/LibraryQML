#include "sqlbookmodel.h"
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

SqlBookModel::SqlBookModel(QObject *parent) : QSqlRelationalTableModel (parent)
{
    setTable("Books");
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    setSort(1, Qt::AscendingOrder);

    //setRelation(2, QSqlRelation("Authors", "id", "name"));
    //setRelation(3, QSqlRelation("Categories", "id", "name"));

    QSqlQuery query;
    if (!query.exec("SELECT * FROM Books ORDER BY Books.title"))
        qFatal("Books SELECT query failed: %s", qPrintable(query.lastError().text()));

    setQuery(query);
    if (lastError().isValid())
        qFatal("Cannot set query on SqlBookModel: %s", qPrintable(lastError().text()));
}

QString SqlBookModel::isbn() const
{
    return m_isbn;
}

void SqlBookModel::setIsbn(const QString &isbn)
{
    if (isbn == m_isbn)
        return;

    m_isbn = isbn;

    const QString filterString = QString::fromLatin1(
        "(isbn='%1')").arg(m_isbn);
    setFilter(filterString);
    select();

    emit isbnChanged();
}

QVariant SqlBookModel::data(const QModelIndex &index, int role) const
{
    if (role < Qt::UserRole)
        return QSqlTableModel::data(index, role);

    const QSqlRecord sqlRecord = record(index.row());
    return sqlRecord.value(role - Qt::UserRole);
}

QHash<int, QByteArray> SqlBookModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[Qt::UserRole] = "isbn";
    names[Qt::UserRole + 1] = "title";
    names[Qt::UserRole + 2] = "author";
    names[Qt::UserRole + 3] = "category";
    return names;
}

bool SqlBookModel::doCreate(const QString &isbn, const QString &title, const QString &author, const QString &category)
{
    if (isbn.length() != 10) {
        return false;
    }

    QSqlRecord newRecord = record();
    newRecord.setValue("isbn", isbn);
    newRecord.setValue("title", title);
    newRecord.setValue("author", author);
    newRecord.setValue("category", category);
    if (!insertRecord(rowCount(), newRecord)) {
        return false;
    }

    if (!submitAll())
    {
        removeRow(rowCount() - 1);
        return false;
    }

    return true;
}

bool SqlBookModel::doUpdate(int currentBook, const QString &title, const QString &author, const QString &category)
{
    QSqlQuery q;
    q.prepare(QLatin1String("update books"
                            " set title=?, author=?, category=?"
                            " where books.isbn=?"));
    q.addBindValue(title);
    q.addBindValue(author);
    q.addBindValue(category);
    q.addBindValue(record(currentBook).value("isbn"));
    if (!q.exec())
    {
        return false;
    }
    if (!submitAll())
    {
        return false;
    }

    return true;
}

bool SqlBookModel::doDelete(int currentBook)
{
    QSqlQuery q;
    q.prepare(QLatin1String("delete from books where books.isbn=?"));
    q.addBindValue(record(currentBook).value("isbn"));
    if (!q.exec())
    {
        return false;
    }
    if (!submitAll())
    {
        return false;
    }
    return true;
}
