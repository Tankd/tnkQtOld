#include "querybuilder.h"

namespace tnk{
namespace sync{

QueryBuilder::QueryBuilder(QSqlDatabase db, QueryBuilder::Type type)
    :m_db(db),
      m_type( type)
{}

QSqlQuery QueryBuilder::genQuery()
{
    if( type() == QueryBuilder::SELECT)
        return genSelect();
    else if( type() == QueryBuilder::INSERT)
        return genInsert();
    else if( type() == QueryBuilder::UPDATE)
        return genUpdate();
    else if( type() == QueryBuilder::DELETE)
        return genDelete();

    return QSqlQuery();
}

QString QueryBuilder::where() const
{
    return m_where;
}

void QueryBuilder::setWhere(const QString &where)
{
    m_where = where;
}

QueryBuilder::Type QueryBuilder::type() const
{
    return m_type;
}

void QueryBuilder::setType(const QueryBuilder::Type &type)
{
    m_type = type;
}

QSqlDatabase QueryBuilder::db() const
{
    return m_db;
}

void QueryBuilder::setDb(QSqlDatabase db)
{
    m_db = db;
}

QMetaObject *QueryBuilder::metaObject() const
{
    return m_metaObject;
}

void QueryBuilder::setMetaObject(QMetaObject *metaObject)
{
    m_metaObject = metaObject;
}

QSqlQuery QueryBuilder::genSelect()
{
    QSqlQuery q( db());
    QString tableName = QString( metaObject()->className());

    QString base = QString("SELECT * FROM %1 ").arg( tableName);

    if( where().isEmpty() == false)
        base.append(" WHERE " + where());

    q.prepare( base);

    return q;
}

QSqlQuery QueryBuilder::genInsert()
{
    QSqlQuery q( db());
    QString tableName = QString( metaObject()->className());

    QString base = QString("INSERT INTO %1 ").arg( tableName);

    QStringList fields;
    QStringList values;
    // ()
    for(int i=1; i<metaObject()->propertyCount(); i++)
    {
        QMetaProperty prop = metaObject()->property(i);
        if( QString(prop.name()) != "id")
        {
            fields << QString(prop.name());
            values << ":" + QString(prop.name());
        }
    }

    q.prepare( base + "(" + fields.join(",") + ") VALUES(" + values.join(",")+ ")");

    return q;
}

QSqlQuery QueryBuilder::genUpdate()
{
    QSqlQuery q( db());
    QString tableName = QString( metaObject()->className());

    QString base = QString("UPDATE %1 SET ").arg( tableName);
    QStringList values;

    for(int i=1; i<metaObject()->propertyCount(); i++)
    {
        QMetaProperty prop = metaObject()->property(i);
        if( QString(prop.name()) != "id")
            values << QString(prop.name()) + "=:" + QString(prop.name());
    }

    base.append( values.join(","));


    if( where().isEmpty() == false)
        base.append(" WHERE " + where());

    q.prepare( base);


    return q;
}

QSqlQuery QueryBuilder::genDelete()
{
    QSqlQuery q( db());
    QString tableName = QString( metaObject()->className());

    QString base = QString("DELETE  FROM %1 ").arg( tableName);

    if( where().isEmpty() == false)
        base.append(" WHERE " + where());

    q.prepare( base);
    return q;
}

}}
