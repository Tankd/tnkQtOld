#ifndef COUCHDB_H
#define COUCHDB_H

#include "ws/restws.h"

namespace tnk {
namespace ws{
class CouchDb : public RestWs
{
    Q_OBJECT
public:
    explicit CouchDb(QObject *parent = nullptr);

    QNetworkReply* allDatabases()
    {
        return get("_all_dbs");
    }

    QNetworkReply *createDatabase( const QString& name)
    {
        return put("name");
    }

    QNetworkReply *getDocument( const QByteArray& id)
    {
        return get(database() + "/" + id);
    }

    QNetworkReply *getAllDocuments()
    {
          return get(database() + "/_all_docs");
    }


    QNetworkReply *createDocument( QJsonObject &object)
    {
        return post(database(), object);
    }

    QNetworkReply *findDocument(QJsonObject& selector)
    {
        return post(database(), selector);
    }


    QString database() const;
    void setDatabase(const QString &database);

private:
    QString m_database;

};
}}

#endif // COUCHDB_H
