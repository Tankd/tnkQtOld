#include "sync/engine.h"
#include <QDebug>
#include <QMetaProperty>

namespace tnk{
namespace sync{

Engine::Engine( const QString &name, QJsonObject data, QObject *parent)
    : QObject(parent)
{
    m_db = tnk::sql::setupSqlDatabase( name, data);
    m_db.open();
}

QSqlDatabase Engine::db() const
{
    return m_db;
}

void Engine::update(Object *object)
{
    if( object->get_id() == -1) // POST
    {
        QueryBuilder builder( this->db(),  QueryBuilder::INSERT);
        builder.setMetaObject( (QMetaObject*)object->metaObject());
        QSqlQuery q = builder.genQuery();

        for(int i=1; i<object->metaObject()->propertyCount(); i++)
        {
            QMetaProperty prop = object->metaObject()->property(i);

            if( q.lastQuery().contains(":" + QString(prop.name())))
            {
                if( QString(prop.typeName()).contains("*"))
                {
                    Object* otherObj = prop.read(object).value<Object*>();
                    update(otherObj);
                    q.bindValue(":" + QString(prop.name()), otherObj->get_id());
                }
                else // standard value

                    q.bindValue(":" + QString(prop.name()), prop.read(object));
            }
        }

        q.exec();
        sql::showSqlQueryDebug( &q);

        object->setProperty("id", q.lastInsertId().toInt());

    }
    else { // PUT

        QueryBuilder builder( this->db(),  QueryBuilder::UPDATE);
        builder.setMetaObject( (QMetaObject*)object->metaObject());

        builder.setWhere( "id = :id");

        QSqlQuery q = builder.genQuery();


        for(int i=1; i<object->metaObject()->propertyCount(); i++)
        {
            QMetaProperty prop = object->metaObject()->property(i);

            if( q.lastQuery().contains(":" + QString(prop.name())))
            {
                if( QString(prop.typeName()).contains("*"))
                {
                    Object* otherObj = prop.read(object).value<Object*>();
                    update(otherObj);
                    q.bindValue(":" + QString(prop.name()), otherObj->get_id());
                }
                else // standard value
                    q.bindValue(":" + QString(prop.name()), prop.read(object));
            }
        }

        q.exec();
        sql::showSqlQueryDebug( &q);

    }
}

void Engine::remove(Object *object)
{
    QueryBuilder builder( this->db(),  QueryBuilder::DELETE);
    builder.setMetaObject( (QMetaObject*)object->metaObject());
    builder.setWhere( QString("id = '%1'").arg( object->get_id()));
    QSqlQuery q = builder.genQuery();
    q.exec();
    sql::showSqlQueryDebug( &q);
}

void Engine::createTables(QMetaObject meta)
{

    QSqlQuery q( m_db);
    //check table
    if( m_db.tables().contains(meta.className(), Qt::CaseInsensitive) == false)
    {
        qDebug() << "create" << meta.className() << "table";
        QSqlQuery q( m_db);

        if( m_db.driverName() == "QSQLITE")
            q.exec( QString(" CREATE TABLE 'main'.'%1' ("
                            " 'id'  INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL);"
                            ).arg(meta.className()));
        else
            q.exec( QString(" CREATE TABLE %1 ("
                            " id  integer NOT NULL AUTO_INCREMENT, PRIMARY KEY(id) );"
                            ).arg(meta.className()));

       sql::showSqlQueryDebug( &q);
    }
    //check fields
    if( m_db.driverName() == "QSQLITE")
        q.exec( QString("PRAGMA table_info(%1);").arg(meta.className()));
    else
        q.exec( QString("SHOW COLUMNS FROM %1;").arg(meta.className()));
    sql::showSqlQueryDebug( &q);

    QStringList currentFields;
    while(q.next())
    {
        if( m_db.driverName() == "QSQLITE")
            currentFields <<  q.record().value("name").toString();
        else
            currentFields <<  q.record().value("field").toString();
    }


    for(int i=1; i<meta.propertyCount(); i++)
    {
        QMetaProperty prop = meta.property(i);

        if (currentFields.contains( prop.name()) == false) // field does not exist
        {

            QString fieldType;
            if( prop.type() == QVariant::Int)
                fieldType = "INTEGER";
            else if( prop.type() == QVariant::Double)
                fieldType = "REAL";
            else if( prop.type() == QVariant::String)
                fieldType = "TEXT";
            else if( prop.type() == QVariant::Date)
                fieldType = "DATE";
            else if( prop.type() == QVariant::DateTime)
                fieldType = "DATETIME";
            else fieldType = "INTEGER";

            QString foreign = QString();
            /* if( m_tableFields.contains( QString(prop.typeName()).remove("*")))
            {
                foreign = QString("REFERENCES %1(id)").arg(QString(prop.typeName()).remove("*"));
            }*/

            qDebug() << "create field" << fieldType << prop.name();
            QString str = QString("ALTER TABLE %1 ADD %2 %3 %4").arg( meta.className()).arg( prop.name()).arg(fieldType).arg(foreign);

            q.exec( str);
            sql::showSqlQueryDebug( &q);

            currentFields << prop.name();
        }
    }


}

}}

