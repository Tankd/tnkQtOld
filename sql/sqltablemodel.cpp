#include "sqltablemodel.h"

namespace tnk {

TableModel::TableModel(QSqlDatabase database, QObject *parent) : QSqlRelationalTableModel(parent, database)
{

}


QHash<int, QByteArray> TableModel::roleNames() const{return roles;}

QVariant TableModel::data(const QModelIndex &index, int role) const
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



bool TableModel::select()
{
    bool ret = QSqlRelationalTableModel::select();
    generateRoleNames();
    return ret;
}

void TableModel::generateRoleNames()
{
    roles.clear();
    int nbCols = this->columnCount();
    for (int i = 0; i < nbCols; i++) {
        roles[Qt::UserRole + i + 1] = QVariant(this->headerData(i, Qt::Horizontal).toString()).toByteArray();
    }
}

}
