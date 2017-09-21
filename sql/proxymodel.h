#ifndef PROXYMODEL_H
#define PROXYMODEL_H

#include <QSortFilterProxyModel>

namespace tnk {
class ProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QString filter READ filter WRITE setFilter NOTIFY filterChanged)

private:
    QHash<int, QByteArray> roles;

signals:
    void filterChanged();

public:
    explicit ProxyModel(QObject *parent = 0);

    virtual QHash<int, QByteArray> roleNames() const{return roles;}
    void generateRoleNames();

    Q_INVOKABLE void setFilter( const QString filter);
    QString filter() const;

private:
    QString m_filter;
};
}

#endif // PROXYMODEL_H
