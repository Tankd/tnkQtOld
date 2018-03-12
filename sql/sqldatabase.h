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
}
}


#endif // DATABASECONFIG_H
