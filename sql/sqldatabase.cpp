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




/*
Database::Database()
{

}

void Database::loadConfig(const QString &prefix)
{
    m_driver = Config::self()->value(prefix+"/driver").toString();
    m_host =  Config::self()->value(prefix+"/host").toString();
    m_port =  Config::self()->value(prefix+"/host").toInt();
    m_user =  Config::self()->value(prefix+"/user").toString();
    m_password =  Config::self()->value(prefix+"/password").toString();
    m_databaseName =  Config::self()->value(prefix+"/database").toString();
}


void Database::setup(const QString &name, QJsonObject data)
{   
    m_driver = data.value("driver").toString();
    m_host = data.value("host").toString();
    m_port = data.value("port").toInt();
    m_user = data.value("user").toString();
    m_password = data.value("password").toString();
    m_databaseName = data.value("database").toString();
}

void Database::open(QString suffix)
{
    if( m_database.connectionName() != databaseName() + suffix)
        m_database = QSqlDatabase::addDatabase( driver(), databaseName() + suffix);

    qDebug() << "Database::open driver" << m_database.databaseName() << QSqlDatabase::isDriverAvailable( driver());

    if( driver() != "QSQLITE")
    {
        m_database.setHostName( host());
        m_database.setPort( port());
        m_database.setUserName( user());
        m_database.setPassword( password());
    }
    else
    {
        QString path = databaseName();
        path.remove( path.lastIndexOf("/"), path.count());
        QDir().mkpath( path);
    }

    m_database.setDatabaseName( databaseName());



    m_database.open();

    if( m_database.isOpen() == false)
        showDebug();

    qDebug() << "isopen" << m_database.isOpen();
}

void Database::close()
{
    m_database.close();
}

void Database::showDebug( QSqlQuery *q)
{
    if(q == 0)
        return;
    if( q->lastError().isValid())
    {
        qDebug() << "database error" << q->lastError().databaseText() << q->lastError().driverText();
        qDebug() << q->lastQuery();
    }

}

void Database::showDebug()
{
    qDebug() << "database error" << databaseName() << m_database.lastError().databaseText() << m_database.lastError().driverText();
}


QString Database::driver() const
{
    return m_driver;
}

void Database::setDriver(const QString &driver)
{
    m_driver = driver;
}


QSqlDatabase Database::database() const
{
    return m_database;
}

QString Database::host() const
{
    return m_host;
}

void Database::setHost(const QString &host)
{
    m_host = host;
}

uint Database::port() const
{
    return m_port;
}

void Database::setPort(const uint &port)
{
    m_port = port;
}

QString Database::user() const
{
    return m_user;
}

void Database::setUser(const QString &user)
{
    m_user = user;
}

QString Database::password() const
{
    return m_password;
}

void Database::setPassword(const QString &password)
{
    m_password = password;
}

QString Database::databaseName() const
{
    return m_databaseName;
}

void Database::setDatabaseName(const QString &databaseName)
{
    m_databaseName = databaseName;
}
*/

}
}
