#include "sqlbookmodel.h"
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>

#include "initdb.h"

static const char *booksTableName = "Books";

static void createTable()
{
    const QStringList &tables = QSqlDatabase::database().tables();
    if (tables.contains(booksTableName)) {
        // The table already exists; we don't need to do anything.
        return;
    }

    QSqlQuery q;
    if (!tables.contains("books", Qt::CaseInsensitive))
    {
        if (!q.exec(QLatin1String(
                        "create table books("
                        "isbn varchar primary key, "
                        "title varchar not null, "
                        "author integer not null, "
                        "category integer not null,"
                        "foreign key(author) references Authors ( id ), "
                        "foreign key(category) references Categories ( id ))")))
            return;
    }

    if (!q.prepare(QLatin1String("insert into authors(name) values(?)")))
        return;
    QVariant asimovId = addAuthor(q, QLatin1String("Isaac Asimov"));
    QVariant greeneId = addAuthor(q, QLatin1String("Graham Greene"));
    QVariant pratchettId = addAuthor(q, QLatin1String("Terry Pratchett"));

    if (!q.prepare(QLatin1String("insert into categories(name) values(?)")))
        return;
    QVariant sfiction = addCategory(q, QLatin1String("Science Fiction"));
    QVariant fiction = addCategory(q, QLatin1String("Fiction"));
    QVariant fantasy = addCategory(q, QLatin1String("Fantasy"));

    if (!q.prepare(QLatin1String("insert into books(isbn, title, author, category) values(?, ?, ?, ?)")))
        return;
    addBook(q, "3243242348", QLatin1String("Foundation"), asimovId, sfiction);
    addBook(q, "2347290347", QLatin1String("Foundation and Empire"), asimovId, fantasy);
    addBook(q, "5345793573", QLatin1String("Second Foundation"), greeneId, fantasy);
    addBook(q, "5045846894", QLatin1String("Foundation's Edge"), pratchettId, fiction);
    addBook(q, "2392428346", QLatin1String("Foundation and Earth"), pratchettId, sfiction);
}

SqlBookModel::SqlBookModel(QObject *parent) : QSqlTableModel (parent)
{
    createTable();
    setTable(booksTableName);
    setEditStrategy(QSqlTableModel::OnManualSubmit);

    QSqlQuery query;
    if (!query.exec("SELECT * FROM Books"))
        qFatal("Books SELECT query failed: %s", qPrintable(query.lastError().text()));

    setQuery(query);
    if (lastError().isValid())
        qFatal("Cannot set query on SqlBookModel: %s", qPrintable(lastError().text()));
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

void SqlBookModel::saveDetails(const QMap<QString, QString> &details)
{
    QSqlRecord newRecord = record();
    newRecord.setValue("isbn", details["isbn"]);
    newRecord.setValue("title", details["title"]);
    newRecord.setValue("author", details["author"].toInt());
    newRecord.setValue("category", details["category"].toInt());
    if (!insertRecord(rowCount(), newRecord)) {
        return;
    }

    submitAll();
}
