#ifndef INITDB_H
#define INITDB_H

#include <QtSql>

void addBook(QSqlQuery &q, const QString &isbn, const QString &title,
             const QVariant &authorId, const QVariant &genreId)
{
    q.addBindValue(isbn);
    q.addBindValue(title);
    q.addBindValue(authorId);
    q.addBindValue(genreId);
    q.exec();
}

QVariant addCategory(QSqlQuery &q, const QString &name)
{
    q.addBindValue(name);
    q.exec();
    return q.lastInsertId();
}

QVariant addAuthor(QSqlQuery &q, const QString &name)
{
    q.addBindValue(name);
    q.exec();
    return q.lastInsertId();
}

QSqlError initDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setPort(5432);
    db.setDatabaseName("postgres");
    db.setUserName("postgres");
    db.setPassword("12345678");

    if (!db.open())
        return db.lastError();

    QSqlQuery q;
    QStringList tables = db.tables();
    if (!tables.contains("books", Qt::CaseInsensitive))
    {
        if (!q.exec(QLatin1String("create table books(isbn varchar primary key, title varchar not null, author integer not null, category integer not null)")))
            return q.lastError();
    }
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

    return QSqlError();
}

#endif
