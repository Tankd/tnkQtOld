#ifndef SQLDATABASE_H
#define SQLDATABASE_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QJsonObject>


namespace tnk {

typedef QList<QSqlRecord> SqlRecordList;

class Database
{
public:
    Database();

    void setup( const QString& name, QJsonObject data);
    void open();
    void close();

    static void showDebug(QSqlQuery *q);
    void showDebug();

    QString driver() const;
    void setDriver(const QString &driver);


    QString host() const;
    void setHost(const QString &host);

    uint port() const;
    void setPort(const uint &port);

    QString user() const;
    void setUser(const QString &user);

    QString password() const;
    void setPassword(const QString &password);

    QString databaseName() const;
    void setDatabaseName(const QString &databaseName);



    QSqlDatabase database() const;



protected:
    QSqlDatabase m_database;    
    QString m_driver;
    QString m_host;
    uint m_port;
    QString m_user;
    QString m_password;
    QString m_databaseName;
};

}


#endif // DATABASECONFIG_H
