#include "querytablemodel.h"
#include <QSqlError>
#include <QDebug>

namespace tnk {
namespace sql{
QString QueryTableModel::queryText() const
{
    return _queryText;
}

void QueryTableModel::setQueryText(const QString &queryText)
{
    _queryText = queryText;
}

QString QueryTableModel::filter() const
{
    return _filter;
}

void QueryTableModel::setFilter(const QString &filter)
{
    _filter = filter;
    select();
}
QueryTableModel::QueryTableModel(QSqlDatabase database, QObject *parent)
    :QSqlQueryModel(parent)
{
    m_db = database;
}

QueryTableModel::~QueryTableModel()
{

}

QVariant QueryTableModel::data ( const QModelIndex & index, int role ) const
{
    if(index.row() >= rowCount()) {
        return QString("");
    }
    if(role < Qt::UserRole)
    {
        return QSqlQueryModel::data(index, role);
    }
    else {
        return QSqlQueryModel::data(this->index(index.row(), role - Qt::UserRole - 1), Qt::DisplayRole);
    }

}



QString QueryTableModel::sort() const
{
    return _sort;
}

void QueryTableModel::setSort(const QString &sort)
{
    _sort = sort;
}
void QueryTableModel::generateRoleNames()
{
    roles.clear();
    int nbCols = this->columnCount();
    for (int i = 0; i < nbCols; i++) {
        roles[Qt::UserRole + i + 1] = QVariant(this->headerData(i, Qt::Horizontal).toString()).toByteArray();
    }


}

void QueryTableModel::select()
{
    QString q = _queryText;
    if(_filter.isEmpty() == false)
        q.append( " WHERE " + _filter);

    if(_sort.isEmpty() == false)
        q.append( " ORDER BY " + _sort);

    this->setQuery( q, m_db);

    generateRoleNames();


}

}
}

