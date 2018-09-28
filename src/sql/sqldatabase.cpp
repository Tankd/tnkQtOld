#include "sqldatabase.h"

#include <QSettings>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>
#include <QtSql/QSqlField>
#include <QMetaProperty>


namespace tnk {
namespace sql{


QSqlDatabase setupSqlDatabase(const QString &name, QJsonObject data)
{
    QSqlDatabase db = QSqlDatabase::addDatabase( data.value("driver").toString(), name);

    db.setHostName(  data.value("host").toString());
    db.setPort(  data.value("port").toInt());
    db.setUserName(  data.value("user").toString());
    db.setPassword(  data.value("password").toString());
    db.setDatabaseName( data.value("database").toString());

    return db;
}

void showSqlDebug(QSqlQuery *q)
{
    if(q == nullptr)
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
