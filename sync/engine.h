#ifndef MYDATASYNC_H
#define MYDATASYNC_H

#include <QQmlEngine>
#include <QObject>
#include <QMap>

#include "sql/sqldatabase.h"
#include "common/singleton.h"

#include "querybuilder.h"
#include "object.h"
#include <QJsonObject>


namespace tnk{
namespace sync{


class Engine : public QObject
{
    Q_OBJECT
public:
    explicit Engine(QObject *parent = nullptr);


    QSqlDatabase db() const;
    void setDb(const QSqlDatabase &db);


    /******************************/
    typedef Object* (*selectFirstFunc)(Engine *mds, const QString& filter);

    template <class T>
    static Object* selectFirstCb(Engine *mds, const QString& filter)
    {
        return mds->selectFirst<T>( filter);
    }

    /******************************/

    typedef Object* (*createFunc)(Engine *mds);

    template <class T>
    static Object* createFirstCb(Engine *mds)
    {
        return mds->create<T>();
    }
    /******************************/


    template <class T>
    void registerType() {

        createTables( T::staticMetaObject);

        _selectFirstFuncs.insert( QString(T::staticMetaObject.className()),
                                  &Engine::selectFirstCb<T>);

        _createFuncs.insert( QString(T::staticMetaObject.className()),
                             &Engine::createFirstCb<T>);

        qDebug() <<  T::staticMetaObject.className();
        qmlRegisterType<T>("datasync", 1, 0, T::staticMetaObject.className());
    }


    template <class T>
    T* create( ) { return new T; }

    Q_INVOKABLE QObject* create(const QString& className)
    {
        return _createFuncs[ className] ( this);
    }



    template < class T>
    T* selectFirst( const QString& filter = "1")
    {

        QueryBuilder builder( this->db(),  QueryBuilder::SELECT);
        builder.setMetaObject( (QMetaObject*)&T::staticMetaObject);
        builder.setWhere( filter);

        QSqlQuery q = builder.genQuery();
        q.exec();
        sql::showSqlQueryDebug( &q);

        if(q.next())
        {
            QSqlRecord r = q.record();
            T* obj = new T();

            for(int i=0; i<obj->metaObject()->propertyCount(); i++)
            {
                QMetaProperty prop = obj->metaObject()->property(i);


                if(  QString(prop.typeName()).contains("*")) //Other DataSyncObject
                {
                    int otherId = r.value(prop.name()).toInt();
                    QObject *otherObj = _selectFirstFuncs[ QString(prop.typeName()).remove("*")] ( this, QString("id = '%1'").arg( otherId));

                    prop.write(obj, QVariant::fromValue<QObject*>(otherObj));
                }
                else {
                    QVariant::Type type = r.value(prop.name()).type();
                    if( type == QVariant::LongLong)
                        prop.write(obj, r.value(prop.name()).toInt());
                    else if( type == QVariant::Double)
                        prop.write(obj, r.value(prop.name()).toFloat());
                    else if( type == QVariant::Date)
                        prop.write(obj, r.value(prop.name()).toDate());
                    else prop.write(obj, r.value(prop.name()).toString());
                }
            }
            return obj;
        }
        return NULL;
    }

    template < class T>
    Object* selectFirstObject( const QString& filter = "1")
    {

        QueryBuilder builder( this->db(),  QueryBuilder::SELECT);
        builder.setMetaObject( (QMetaObject*)&T::staticMetaObject);
        builder.setWhere( filter);

        QSqlQuery q = builder.genQuery();
        q.exec();
        sql::showSqlQueryDebug( &q);

        if(q.next())
        {
            QSqlRecord r = q.record();
            Object* obj = new Object();

            for(int i=0; i<obj->metaObject()->propertyCount(); i++)
            {
                QMetaProperty prop = obj->metaObject()->property(i);


                if(  QString(prop.typeName()).contains("*")) //Other DataSyncObject
                {
                    int otherId = r.value(prop.name()).toInt();
                    QObject *otherObj = _selectFirstFuncs[ QString(prop.typeName()).remove("*")] ( this, QString("id = '%1'").arg( otherId));

                    prop.write(obj, QVariant::fromValue<QObject*>(otherObj));
                }
                else {
                    QVariant::Type type = r.value(prop.name()).type();
                    if( type == QVariant::LongLong)
                        prop.write(obj, r.value(prop.name()).toInt());
                    else if( type == QVariant::Double)
                        prop.write(obj, r.value(prop.name()).toFloat());
                    else if( type == QVariant::Date)
                        prop.write(obj, r.value(prop.name()).toDate());
                    else prop.write(obj, r.value(prop.name()).toString());
                }
            }
            return obj;
        }
        return NULL;
    }

    template< class T>
    QList<T*> select( const QString& filter = "1")
    {
        QList<T*> result;
        QueryBuilder builder( this->db(),  QueryBuilder::SELECT);
        builder.setMetaObject( (QMetaObject*)&T::staticMetaObject);
        builder.setWhere( filter);

        QSqlQuery q = builder.genQuery();
        q.exec();
        sql::showSqlQueryDebug( &q);

        while(q.next())
        {
            QSqlRecord r = q.record();
            T* obj = new T();

            for(int i=0; i<obj->metaObject()->propertyCount(); i++)
            {
                QMetaProperty prop = obj->metaObject()->property(i);

                if(  QString(prop.typeName()).contains("*")) //Other DataSyncObject
                {
                    int otherId = r.value(prop.name()).toInt();
                    QObject *otherObj = _selectFirstFuncs[ QString(prop.typeName()).remove("*")] ( this, QString("id = '%1'").arg( otherId));

                    prop.write(obj, QVariant::fromValue<QObject*>(otherObj));
                }
                else {
                    QVariant type = r.value(prop.name()).type();
                    if( type == QVariant::Int)
                        prop.write(obj, r.value(prop.name()).toInt());
                    else if( type == QVariant::Double)
                        prop.write(obj, r.value(prop.name()).toFloat());
                    else if( type == QVariant::Date)
                        prop.write(obj, r.value(prop.name()).toDate());
                    else prop.write(obj, r.value(prop.name()).toString());
                }
            }
            result << obj;
        }

        return result;
    }

    template< class T>
    QList<Object*> selectObjects( const QString& filter = "1")
    {      
        QList<Object*> result;
        QueryBuilder builder( this->db(),  QueryBuilder::SELECT);
        builder.setMetaObject( (QMetaObject*)&T::staticMetaObject);
        builder.setWhere( filter);

        QSqlQuery q = builder.genQuery();
        q.exec();
        sql::showSqlQueryDebug( &q);

        while(q.next())
        {
            QSqlRecord r = q.record();
            T* obj = new T();

            for(int i=0; i<obj->metaObject()->propertyCount(); i++)
            {
                QMetaProperty prop = obj->metaObject()->property(i);

                if(  QString(prop.typeName()).contains("*")) //Other DataSyncObject
                {
                    int otherId = r.value(prop.name()).toInt();
                    QObject *otherObj = _selectFirstFuncs[ QString(prop.typeName()).remove("*")] ( this, QString("id = '%1'").arg( otherId));

                    prop.write(obj, QVariant::fromValue<QObject*>(otherObj));
                }
                else {
                    QVariant type = r.value(prop.name()).type();
                    if( type == QVariant::Int)
                        prop.write(obj, r.value(prop.name()).toInt());
                    else if( type == QVariant::Double)
                        prop.write(obj, r.value(prop.name()).toFloat());
                    else if( type == QVariant::Date)
                        prop.write(obj, r.value(prop.name()).toDate());
                    else prop.write(obj, r.value(prop.name()).toString());
                }
            }
            result << obj;
        }
        return result;
    }

    Q_INVOKABLE void update(Object* object);

    void remove(Object* object);

    template< class T>
    void removeAll(const QString& filter = "1")
    {
        QueryBuilder builder( this->db(),  QueryBuilder::DELETE);
        builder.setMetaObject( (QMetaObject*)&T::staticMetaObject);
        builder.setWhere( filter);
        QSqlQuery q = builder.genQuery();
        q.exec();
        sql::showSqlQueryDebug( &q);
    }

protected:
    QSqlDatabase m_db;
    QMap<QString, Engine::selectFirstFunc> _selectFirstFuncs;
    QMap<QString, Engine::createFunc> _createFuncs;

    void createTables( QMetaObject meta);



};


}
}
#endif // DATABASE_H
