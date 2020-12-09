#ifndef INITDB_H
#define INITDB_H

#include <QtSql>

QVariant addAuthor(QSqlQuery &q, const QString &name)
{
    q.addBindValue(name);
    q.exec();
    return q.lastInsertId();
}

QVariant addCategory(QSqlQuery &q, const QString &name)
{
    q.addBindValue(name);
    q.exec();
    return q.lastInsertId();
}

void addBook(QSqlQuery &q, const QString &isbn, const QString &title,
             const QVariant &authorId, const QVariant &genreId)
{
    q.addBindValue(isbn);
    q.addBindValue(title);
    q.addBindValue(authorId);
    q.addBindValue(genreId);
    q.exec();
}

QSqlError initDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    if (!db.isValid())
        db.lastError();

    db.setHostName("localhost");
    db.setPort(5432);
    db.setDatabaseName("postgres");
    db.setUserName("postgres");
    db.setPassword("12345678");
    if (!db.open())
        return db.lastError();

    QSqlQuery q;
    QStringList tables = db.tables();
    if (!tables.contains("authors", Qt::CaseInsensitive))
    {
        if (!q.exec(QLatin1String("create table authors(id serial primary key, name varchar not null)")))
            return q.lastError();
    }
    if (!tables.contains("categories", Qt::CaseInsensitive))
    {
        if (!q.exec(QLatin1String("create table categories(id serial primary key, name varchar not null)")))
            return q.lastError();
    }
    if (!tables.contains("books", Qt::CaseInsensitive))
    {
        if (!q.exec(QLatin1String(
                        "create table books("
                        "isbn varchar(10) primary key, "
                        "title varchar not null, "
                        "author integer not null, "
                        "category integer not null,"
                        "foreign key(author) references Authors ( id ), "
                        "foreign key(category) references Categories ( id ))")))
            return q.lastError();
    }

    if (!q.prepare(QLatin1String("insert into authors(name) values(?)")))
        return q.lastError();
    QVariant asimovId = addAuthor(q, QLatin1String("Isaac Asimov"));
    QVariant greeneId = addAuthor(q, QLatin1String("Graham Greene"));
    QVariant pratchettId = addAuthor(q, QLatin1String("Terry Pratchett"));

    if (!q.prepare(QLatin1String("insert into categories(name) values(?)")))
        return q.lastError();
    QVariant sfiction = addCategory(q, QLatin1String("Science Fiction"));
    QVariant fiction = addCategory(q, QLatin1String("Fiction"));
    QVariant fantasy = addCategory(q, QLatin1String("Fantasy"));

    if (!q.prepare(QLatin1String("insert into books(isbn, title, author, category) values(?, ?, ?, ?)")))
        return q.lastError();
    addBook(q, "3243242348", QLatin1String("Foundation"), asimovId, sfiction);
    addBook(q, "2347290347", QLatin1String("Foundation and Empire"), asimovId, fantasy);
    addBook(q, "5345793573", QLatin1String("Second Foundation"), greeneId, fantasy);
    addBook(q, "5045846894", QLatin1String("Foundation's Edge"), pratchettId, fiction);
    addBook(q, "2392428346", QLatin1String("Foundation and Earth"), pratchettId, sfiction);

    return QSqlError();
}

#endif
