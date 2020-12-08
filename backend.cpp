#include "backend.h"
#include "initdb.h"

BackEnd::BackEnd(QObject *parent) :
    QObject(parent)
{
    // Initialize the database:
    QSqlError err = initDb();
    if (err.type() != QSqlError::NoError) {
        return;
    }

    QSqlQuery q;
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

QString BackEnd::userName()
{
    return m_userName;
}

void BackEnd::setUserName(const QString &userName)
{
    if (userName == m_userName)
        return;

    m_userName = userName;
    emit userNameChanged();
}
