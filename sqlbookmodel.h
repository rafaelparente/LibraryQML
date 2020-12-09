#ifndef SQLBOOKMODEL_H
#define SQLBOOKMODEL_H

#include <QSqlRelationalTableModel>


class SqlBookModel : public QSqlRelationalTableModel
{
    Q_OBJECT
    Q_PROPERTY(QString isbn READ isbn WRITE setIsbn NOTIFY isbnChanged)

public:
    SqlBookModel(QObject *parent = nullptr);

    QString isbn() const;
    void setIsbn(const QString &isbn);

    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE bool doCreate(const QString &isbn, const QString &title, const QString &author, const QString &category);
    Q_INVOKABLE bool doUpdate(int currentBook, const QString &title, const QString &author, const QString &category);
    Q_INVOKABLE bool doDelete(int currentBook);
    Q_INVOKABLE bool doSearch(const QString &text);

signals:
    void isbnChanged();

private:
    QString m_isbn;
};

#endif // SQLBOOKMODEL_H
