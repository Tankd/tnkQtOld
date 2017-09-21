#ifndef QUERYBUILDER_H
#define QUERYBUILDER_H

#include <QStringList>
#include <QList>

#include "sql/sqldatabase.h"
#include <QSqlQuery>
#include <QMetaProperty>

namespace tnk{
namespace sync{

class QueryBuilder
{
public:
    typedef enum Type {
        SELECT,
        INSERT,
        UPDATE,
        DELETE
    }Type;

    QueryBuilder( tnk::Database *db, Type type);



    QSqlQuery genQuery();

    QString where() const;
    void setWhere(const QString &where);


    Type type() const;
    void setType(const Type &type);

    tnk::Database *db() const;
    void setDb( tnk::Database *db);

    QMetaObject *metaObject() const;
    void setMetaObject(QMetaObject *metaObject);

private:
    Type m_type;
    QString m_where;
    tnk::Database *m_db;
    QMetaObject *m_metaObject;



    QSqlQuery genSelect();
    QSqlQuery genInsert();
    QSqlQuery genUpdate();
    QSqlQuery genDelete();
};





}
}



















#endif // QUERYBUILDER_H
