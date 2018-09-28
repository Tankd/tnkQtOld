#ifndef SQLDATABASE_H
#define SQLDATABASE_H

#include "sql_global.h"

#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QJsonObject>


namespace tnk {
namespace sql{
typedef QList<QSqlRecord> SqlRecordList;

Q_TNK_SQL_EXPORT QSqlDatabase setupSqlDatabase( const QString& name, QJsonObject data);

Q_TNK_SQL_EXPORT void showSqlDebug(QSqlQuery *q);
Q_TNK_SQL_EXPORT void showSqlDebug(QSqlDatabase *db);


Q_TNK_SQL_EXPORT void createTable(QSqlDatabase db, const QString &tableName, QList<QSqlField> fields);
Q_TNK_SQL_EXPORT void createTable(QSqlDatabase db, const QString &tableName, QMetaObject meta);

Q_TNK_SQL_EXPORT void checkConnected( QSqlDatabase db);
}
}


#endif // DATABASECONFIG_H
