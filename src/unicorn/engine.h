#ifndef ENGINE_H
#define ENGINE_H

#include "unicorn_global.h"

#include <QObject>
#include <QDebug>
#include <QMetaProperty>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>


#include "entity.h"

namespace unicorn {



class Q_TNK_UNICORN_EXPORT Engine : public QObject
{
    Q_OBJECT
public:
    typedef enum ErrorType{
        NONE,
        ERR_NOT_CONNECTED,
        ERR_SQL
    }ErrorType;

    typedef struct Error{
        ErrorType type = NONE;
        QString text;
        QString sqlText;
    }Error;


    explicit Engine(QSqlDatabase db, const QString& tableNamePrefix = QString(), QObject *parent = nullptr);


    void createTable(QMetaObject meta);
    void dropTable(const QString& tableName);

    void create(unicorn::Entity *entity);
    void create(QList<Entity *> *entities);

    void update(unicorn::Entity *entity);
    void update(QList<Entity *> *entities);



    template< class T = unicorn::Entity>
    T* get( int id)
    {
        if( isConnected() == false)
        {
            setLastError( ERR_NOT_CONNECTED, "Database not connected");
            return nullptr;
        }

        const QString tableName = getTableName(T::staticMetaObject.className());

        QSqlQuery q( _db);
        q.prepare( QString("SELECT * FROM %1 WHERE id = :id").arg( tableName));
        q.bindValue(":id", id);
        q.exec();

        if( findSqlError("Engine::get", q.lastError()))
            return nullptr;

        T* entity = nullptr;

        if( q.next())
        {
            entity = new T();

            for( int i=1; i<entity->metaObject()->propertyCount(); i++)
            {
                QMetaProperty prop = entity->metaObject()->property(i);
                if( QString(prop.typeName()).right(1) == "*")
                {

                    QVariant var = prop.read(entity);
                    auto sub = var.value<unicorn::Entity*>();
                    if(sub)
                        this->getInstancied( sub, q.record().value( prop.name()).toInt());
                }
                else
                    prop.write( entity, q.record().value( prop.name()));
            }
        }

        return entity;
    }

    template <class T = unicorn::Entity>
    QList<T*> getAll( const QString& condition)
    {

        QList<T*> results;

        if( isConnected() == false)
        {
            setLastError( ERR_NOT_CONNECTED, "Database not connected");
            return results;
        }

        const QString tableName = getTableName(T::staticMetaObject.className());



        QStringList joins;
        for( int i=1; i<T::staticMetaObject.propertyCount(); i++)
        {
            auto prop = T::staticMetaObject.property(i);
            if( QString(prop.typeName()).right(1) == "*")
            {
                    joins << QString("INNER JOIN '%1' ON '%2'.'%3' = '%1'.id")
                             .arg( getTableName( QString(prop.typeName()).remove("*")))
                             .arg(tableName )
                             .arg(prop.name());

            }
        }

        QSqlQuery q( _db);
        q.prepare( QString("SELECT * FROM %1 %3 WHERE %2")
                   .arg( tableName)
                   .arg(condition)
                   .arg( joins.join(" "))
                   );

        q.exec();

        if( findSqlError("Engine::get", q.lastError()))
            return results;


        //qDebug() << q.lastQuery() << q.boundValues();
        if( q.next())
        {
            T* entity = new T();
            for( int i=1; i<T::staticMetaObject.propertyCount(); i++)
            {
                auto prop = T::staticMetaObject.property(i);
                if( QString(prop.typeName()).right(1) == "*")
                {
                    QVariant var = prop.read(entity);
                    auto sub = var.value<unicorn::Entity*>();
                    if(sub)
                    {
                        this->getInstancied( sub, q.record().value( prop.name()).toInt());
                    }
                }
                else
                    prop.write( entity, q.record().value( prop.name()));
            }
            results << entity;
        }

        return results;
    }

    void remove(unicorn::Entity* entity);
    void remove(QList<unicorn::Entity*> *entities);

    QSqlDatabase getDb() const;
    Error getLastError() const;

    QString getTableNamePrefix() const;
    QString getTableName(const QString& className ) const {
        return (getTableNamePrefix() + "_" + className.toLower());
    }


    bool isConnected()
    {
        if( _db.isValid() && _db.isOpen())
            return true;
        return false;
    }

protected:
    QSqlDatabase _db;
    QString _tableNamePrefix;
    Error _lastError;

      void getInstancied(unicorn::Entity *entity, int id);


    void setLastError( Engine::ErrorType type, const QString& text, const QString& sqlText = QString())
    {
        _lastError.type = type;
        _lastError.text = text;
        _lastError.sqlText = sqlText;
    }
    bool findSqlError( const QString& text, const QSqlError& error)
    {
        if( error.isValid() == false)
            return false;

        setLastError( ERR_SQL, text, error.databaseText() + "-" + error.driverText());
        return true;
    }



};

}

#endif // ENGINE_H
