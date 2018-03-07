#include "couchdb.h"

namespace tnk {
namespace ws{
CouchDb::CouchDb(QObject *parent) : RestWs(parent)
{

}

QString CouchDb::database() const
{
    return m_database;
}

void CouchDb::setDatabase(const QString &database)
{
    m_database = database;
}

}}
