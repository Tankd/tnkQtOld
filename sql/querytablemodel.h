#ifndef QUERYTABLEMODEL_H
#define QUERYTABLEMODEL_H

#include <QSqlQueryModel>

namespace tnk {
namespace sql{
class QueryTableModel : public QSqlQueryModel
{
    Q_OBJECT

private:
    QHash<int, QByteArray> roles;

    QSqlDatabase m_db;

    QString _queryText;
    QString _filter;
    QString _sort;

    void generateRoleNames();


public:
    QueryTableModel(QSqlDatabase database, QObject *parent = 0);
    virtual ~QueryTableModel();
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role=Qt::DisplayRole ) const;


    virtual QHash<int, QByteArray> roleNames() const{return roles;}

    Q_INVOKABLE void select();
    QString queryText() const;
    void setQueryText(const QString &queryText);
    QString filter() const;
    Q_INVOKABLE void setFilter(const QString &filter);

    QString sort() const;
    void setSort(const QString &sort);
};

}
}
#endif // QUERYTABLEMODEL_H
