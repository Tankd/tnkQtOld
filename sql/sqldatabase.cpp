#include "sqldatabase.h"

#include <QSettings>
#include <QSqlError>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>
#include <QSqlField>
#include <QMetaProperty>

#include "common/config.h"

namespace tnk {
namespace sql{

QSqlDatabase loadConfig(const QString& name, const QString &prefix)
{
    QSqlDatabase db = QSqlDatabase::addDatabase( Config::self()->value(prefix+"/driver").toString(), name);

    db.setHostName(  Config::self()->value(prefix+"/host").toString());
    db.setPort(  Config::self()->value(prefix+"/port").toInt());
    db.setUserName(  Config::self()->value(prefix+"/user").toString());
    db.setPassword(  Config::self()->value(prefix+"/password").toString());
    db.setDatabaseName( Config::self()->value(prefix+"/database").toString());

    return db;
}

QSqlDatabase setupSqlDatabase(const QString &name, QJsonObject data)
{
    QSqlDatabase db = QSqlDatabase::addDatabase( data.value("driver").toString());

    db.setHostName(  data.value("host").toString());
    db.setPort(  data.value("port").toInt());
    db.setUserName(  data.value("user").toString());
    db.setPassword(  data.value("password").toString());
    db.setDatabaseName( data.value("database").toString());

    return db;
}

void showSqlDebug(QSqlQuery *q)
{
    if(q == 0)
        return;
    if( q->lastError().isValid())
    {
        qDebug() << "query error" << q->lastError().databaseText() << q->lastError().driverText();
        qDebug() << q->lastQuery();
    }
}


void showSqlDebug(QSqlDatabase *db)
{
    if(db == 0)
        return;
    if( db->lastError().isValid())
    {
        qDebug() << "database error" << db->lastError().databaseText() << db->lastError().driverText() ;
    }
}

void createTable(QSqlDatabase db, const QString &tableName, QList<QSqlField> fields)
{
    if( db.tables().contains(tableName))
    {
        return;
    }

    QString str = QString(
                " CREATE TABLE 'main'.'%1' ("
                ).arg(tableName);

    QStringList list;
    list << " 'id'  INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL ";
    foreach( auto field, fields)
    {
        QString fieldType;
        if( field.type() == QVariant::Int)
            fieldType = "INTEGER";
        else if( field.type() == QVariant::Double)
            fieldType = "REAL";
        else if( field.type() == QVariant::String)
            fieldType = "TEXT";
        else if( field.type() == QVariant::Date)
            fieldType = "DATE";
        else if( field.type() == QVariant::DateTime)
            fieldType = "DATETIME";
        else fieldType = "INTEGER";

        list <<  QString("%1 %2").arg( field.name()).arg(fieldType);
    }
    str.append( list.join(","));

    str.append(");");


    QSqlQuery q( db);
    q.exec( str);

    showSqlDebug(&q);

}

void createTable(QSqlDatabase db, const QString &tableName, QMetaObject meta)
{
    QList<QSqlField> fields;
    for(int i = meta.propertyOffset(); i < meta.propertyCount(); i++)
    {
        fields << QSqlField( meta.property(i).name(), meta.property(i).type());
    }


    createTable(db, tableName, fields);
}

void checkConnected(QSqlDatabase db)
{
    db.close();
    db.open();
}


}
}
