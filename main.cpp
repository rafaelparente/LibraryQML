#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include "sqlbookmodel.h"

static void connectToDatabase()
{
    QSqlDatabase database = QSqlDatabase::database();
    if (!database.isValid()) {
        database = QSqlDatabase::addDatabase("QPSQL");
        database.setHostName("localhost");
        database.setPort(5432);
        database.setDatabaseName("postgres");
        database.setUserName("postgres");
        database.setPassword("12345678");
        if (!database.isValid())
            qFatal("Cannot add database: %s", qPrintable(database.lastError().text()));
    }

    if (!database.open()) {
        qFatal("Cannot open database: %s", qPrintable(database.lastError().text()));
    }

    QSqlQuery q;
    QStringList tables = database.tables();
    if (!tables.contains("Authors", Qt::CaseInsensitive))
    {
        if (!q.exec(QLatin1String("create table Authors(id serial primary key, name varchar not null)")))
            return;
    }
    if (!tables.contains("Categories", Qt::CaseInsensitive))
    {
        if (!q.exec(QLatin1String("create table Categories(id serial primary key, name varchar not null)")))
            return;
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<SqlBookModel>("library.sqlbookmodel", 1, 0, "SqlBookModel");

    connectToDatabase();

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
