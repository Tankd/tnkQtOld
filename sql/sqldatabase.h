#ifndef SQLDATABASE_H
#define SQLDATABASE_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QJsonObject>


namespace tnk {
namespace sql{
typedef QList<QSqlRecord> SqlRecordList;

QSqlDatabase loadConfig(const QString &name, const QString& prefix);
QSqlDatabase setupSqlDatabase( const QString& name, QJsonObject data);

void showSqlDebug(QSqlQuery *q);
void showSqlDebug(QSqlDatabase *db);


void createTable(QSqlDatabase db, const QString &tableName, QList<QSqlField> fields);
void createTable(QSqlDatabase db, const QString &tableName, QMetaObject meta);

void checkConnected( QSqlDatabase db);
}
}


#endif // DATABASECONFIG_H
