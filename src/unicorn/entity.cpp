#include "entity.h"
#include <QtSql/QSqlRecord>
#include <QDebug>

namespace unicorn {



Entity::Entity(QObject *parent)
    :QObject(parent)
{

}

QJsonObject Entity::toJsonObject()
{
    QJsonObject result;
    for(int i=1; i<this->metaObject()->propertyCount(); i++)
    {
        auto prop = metaObject()->property(i);
        if( QString(prop.typeName()).right(1) == "*")
        {
            auto sub = prop.read(this).value<Entity*>();
            int id = -1;
            if(sub)
                id = sub->get_id();
            result.insert(
                        prop.name(),
                        sub->toJsonObject());
        }
        else
            result.insert(
                        prop.name(),
                        prop.read( this).toString());
    }
    return result;

}



}
