#ifndef SQLBOOKMODEL_H
#define SQLBOOKMODEL_H

#include <QSqlTableModel>


class SqlBookModel : public QSqlTableModel
{
    Q_OBJECT

public:
    SqlBookModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void saveDetails(const QMap<QString, QString> &details);
};

#endif // SQLBOOKMODEL_H
