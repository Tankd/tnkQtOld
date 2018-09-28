#include "engine.h"

#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>
#include <QMetaProperty>

#include <QVariant>
#include "entity.h"

namespace unicorn {

Engine::Engine(QSqlDatabase db, const QString &tableNamePrefix, QObject *parent)
    : QObject(parent),
      _db(db),
      _tableNamePrefix(tableNamePrefix)
{

}

void Engine::dropTable(const QString &tableName)
{
    if( isConnected() == false)
    {
        setLastError( ERR_NOT_CONNECTED, "Database not connected");
        return;
    }

    _db.exec( "DROP TABLE " + getTableName( tableName));
}

void Engine::createTable(QMetaObject meta)
{
    if( isConnected() == false)
    {
        setLastError( ERR_NOT_CONNECTED, "Database not connected");
        return;
    }
    const QString tableName = getTableName(meta.className());

    QSqlQuery q( _db);
    //create table if needed
    if( _db.tables().contains(tableName, Qt::CaseInsensitive) == false)
    {
        qDebug() << "Engine::createTable" << tableName;
        if( _db.driverName() == "QSQLITE")
            q.exec( QString(" CREATE TABLE 'main'.'%1' ("
                            " 'id'  INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL);"
                            ).arg(tableName));
        else
            q.exec( QString(" CREATE TABLE %1 ("
                            " id  integer NOT NULL AUTO_INCREMENT, PRIMARY KEY(id) );"
                            ).arg(tableName));
    }



    //update fields
    QSqlRecord record = _db.record(tableName);
    QStringList currentFields;

    for( int i=0; i< record.count(); i++)
    {
        currentFields<< record.fieldName(i);
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

            qDebug() << "create field" << fieldType << prop.name()<<prop.typeName();



            QString str = QString("ALTER TABLE %1 ADD %2 %3").arg(tableName).arg( prop.name()).arg(fieldType);
            q.exec( str);


            if( findSqlError("create field", q.lastError()))
                return;

            currentFields << prop.name();
        }
    }


}

void Engine::create(unicorn::Entity *entity)
{
    QList<unicorn::Entity*> entities;
    entities << entity;
    create( &entities);
}

void Engine::create(QList<Entity*> *entities)
{
    if( isConnected() == false)
    {
        setLastError( ERR_NOT_CONNECTED, "Database not connected");
        return;
    }

    if( entities->size() == 0)
        return;

    getDb().transaction();
    const QString tableName = getTableName(entities->at(0)->metaObject()->className());

    QSqlQuery q( _db);

    QStringList columns;
    QStringList binds;

    const QMetaObject *meta = entities->at(0)->metaObject();

    for(int i=2; i< meta->propertyCount(); i++)
    {
        columns << meta->property(i).name();
        binds << QString(":%1").arg(meta->property(i).name());
    }

    QString str = QString("INSERT INTO %1(%2) VALUES(%3);").arg( tableName)
            .arg( columns.join(","))
            .arg( binds.join(","));


    q.prepare(str);

    foreach( auto entity, *entities)
    {
        for(int i=2; i< meta->propertyCount(); i++)
        {
            if(QString(meta->property(i).typeName()).right(1) == "*")
            {
                auto sub = meta->property(i).read(entity).value<Entity*>();
                int id = -1;
                if(sub)
                {
                    this->create( sub);
                    id = sub->get_id();
                }
                q.bindValue( QString(":%1").arg(meta->property(i).name()), id);
            }
            else
                q.bindValue( QString(":%1").arg(meta->property(i).name()), meta->property(i).read(entity));
        }

        q.exec();
        if( findSqlError("Engine::create", q.lastError()))
            return;

        entity->set_id( q.lastInsertId().toInt());
    }
    getDb().commit();

}

void Engine::update(Entity *entity)
{
    QList<unicorn::Entity*> entities;
    entities << entity;
    update( &entities);
}

void Engine::update(QList<Entity *> *entities)
{
    if( isConnected() == false)
    {
        setLastError( ERR_NOT_CONNECTED, "Database not connected");
        return;
    }

    if(entities->size() ==0)
        return;


    getDb().transaction();
    const QString tableName = getTableName(entities->at(0)->metaObject()->className());

    QSqlQuery q( _db);


    QStringList binds;

    const QMetaObject *meta = entities->at(0)->metaObject();

    for(int i=2; i< meta->propertyCount(); i++)
    {
        binds << QString("%1=:%1").arg(meta->property(i).name());
    }

    QString str = QString("UPDATE %1 SET %2 WHERE id = :id;")
            .arg( tableName)
            .arg( binds.join(","));


    q.prepare(str);

    foreach( auto entity, *entities)
    {
        for(int i=1; i< meta->propertyCount(); i++)
        {
            QString name = meta->property(i).typeName();
            if(QString(meta->property(i).typeName()).right(1) == "*")
            {
                auto sub = meta->property(i).read(entity).value<Entity*>();
                int id = -1;
                if(sub)
                    id = sub->get_id();
                q.bindValue( QString(":%1").arg(meta->property(i).name()), id);
            }
            else
                q.bindValue( QString(":%1").arg(meta->property(i).name()), meta->property(i).read(entity));
        }

        auto b =  q.boundValues();
        q.exec();
        if( findSqlError("Engine::create", q.lastError()))
        {
            qDebug() << getLastError().sqlText;
            return;
        }

        entity->set_id( q.lastInsertId().toInt());
    }
    getDb().commit();



}

void Engine::getInstancied(Entity *entity, int id)
{
    if( isConnected() == false)
    {
        setLastError( ERR_NOT_CONNECTED, "Database not connected");
        return;
    }

    const QString tableName = getTableName(entity->metaObject()->className());

    QSqlQuery q( _db);
    q.prepare( QString("SELECT * FROM %1 WHERE id = :id").arg( tableName));
    q.bindValue(":id", id);
    q.exec();

    if( findSqlError("Engine::get", q.lastError()))
        return;

    if( q.next())
    {
        for( int i=1; i<entity->metaObject()->propertyCount(); i++)
        {
            auto prop = entity->metaObject()->property(i);
            if( QString(prop.typeName()).right(1) == "*")
            {
                auto sub = prop.read(entity).value<Entity*>();
                if(sub)
                    this->getInstancied( sub, q.record().value( prop.name()).toInt());
            }
            else
                prop.write( entity, q.record().value( prop.name()));
        }
    }

}



void Engine::remove(unicorn::Entity *entity)
{
    QList<unicorn::Entity*> entities;
    entities << entity;
    remove( &entities);
}

void Engine::remove(QList<unicorn::Entity *> *entities)
{
    if( isConnected() == false)
    {
        setLastError( ERR_NOT_CONNECTED, "Database not connected");
        return;
    }



    if(entities->size() ==0)
        return;

    const QString tableName = getTableName(entities->at(0)->metaObject()->className());

    getDb().transaction();
    QSqlQuery q(getDb());
    QStringList ids;
    foreach( auto entity, *entities)
        ids << "id = " + QString::number(entity->get_id());

    QString str = QString("DELETE FROM %1 WHERE %2")
            .arg( tableName)
            .arg( ids.join( " OR " ));

    q.exec(str);

    if( findSqlError("Engine::remove", q.lastError()))
        return;

    getDb().commit();
}



QSqlDatabase Engine::getDb() const
{
    return _db;
}

Engine::Error Engine::getLastError() const
{
    return _lastError;
}


QString Engine::getTableNamePrefix() const
{
    return _tableNamePrefix;
}

}
