#include "sqldatabase.h"

#include <QSettings>
#include <QSqlError>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>

namespace tnk {

Database::Database()
{

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

void Database::open()
{
    if( m_database.connectionName() != databaseName())
        m_database = QSqlDatabase::addDatabase( driver(), databaseName());

    qDebug() << QSqlDatabase::isDriverAvailable( driver());

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


}
