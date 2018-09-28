#ifndef PROXYMODEL_H
#define PROXYMODEL_H

#include "sql_global.h"
#include <QSortFilterProxyModel>

namespace tnk {
namespace sql{
class Q_TNK_SQL_EXPORT ProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QString filter READ filter WRITE setFilter NOTIFY filterChanged)

private:
    QHash<int, QByteArray> roles;

signals:
    void filterChanged();

public:
    explicit ProxyModel(QObject *parent = nullptr);

    virtual QHash<int, QByteArray> roleNames() const{return roles;}
    void generateRoleNames();

    Q_INVOKABLE void setFilter( const QString filter);
    QString filter() const;

private:
    QString m_filter;
};
}
}

#endif // PROXYMODEL_H
