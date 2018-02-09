#include "proxymodel.h"

namespace tnk {
namespace sql{
ProxyModel::ProxyModel(QObject *parent) : QSortFilterProxyModel(parent)
{
    setFilterCaseSensitivity( Qt::CaseInsensitive);
    setFilterKeyColumn(-1);
}


void ProxyModel::generateRoleNames()
{
    roles.clear();
    int nbCols = this->columnCount();
    for (int i = 0; i < nbCols; i++) {
        roles[Qt::UserRole + i + 1] = QVariant(this->headerData(i, Qt::Horizontal).toString()).toByteArray();
    }


}

void ProxyModel::setFilter(const QString filter)
{
    m_filter = filter;
    QSortFilterProxyModel::setFilterWildcard( "*" + m_filter +"*");
    emit filterChanged();
}

QString ProxyModel::filter() const
{
    return m_filter;
}

}
}
