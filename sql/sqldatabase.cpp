#include "sqldatabase.h"

#include <QSettings>
#include <QSqlError>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>

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


}
}
