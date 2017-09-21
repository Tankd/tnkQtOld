#include "object.h"

#include <QMetaProperty>

namespace tnk{
namespace sync{

int Object::dataFirstIndex = 1;

Object::Object( QObject *parent) : QObject(parent)
{
    m_id = -1;
}

/*
QJsonObject Object::toJsonObject( DataSync::Database *base)
{
    QJsonObject obj;


    for(int i=dataFirstIndex; i<metaObject()->MyPROPERTYCount(); i++)
    {
        QMetaProperty prop = metaObject()->MyPROPERTY(i);

        if( dataSync->tableFields().keys().contains( QString(prop.typeName()).remove("*"))) //Other DataSyncObject
        {
            Object* otherObj =  qvariant_cast<Object *>(prop.read(this));
            obj.insert( prop.name(), otherObj->id( ));
        }
        else
        {

            obj.insert( prop.name(), prop.read(this).toString());
        }
    }


    return obj;
}

void Object::fromJsonObject(DataSync::Database *base, QJsonObject jsonObject)
{
    for(int i=dataFirstIndex; i<metaObject()->MyPROPERTYCount(); i++)
    {
        QMetaProperty prop = metaObject()->MyPROPERTY(i);

        if( base->tableFields().keys().contains( QString(prop.typeName()).remove("*"))) //Other DataSyncObject
        {
           // DataSyncObject* otherObj =  qvariant_cast<DataSyncObject *>(prop.read(this));
           // obj.insert( prop.name(), otherObj->uuid( ));

//            DataSyncObject *otherObject = jsonObject.value()
        }
        else
        {
            prop.write( this, jsonObject.value(prop.name()));
        }
    }

}*/


QDebug operator<<(QDebug dbg, const Object *object)
{
     dbg.space() << object->metaObject()->className();
      for(int i=1; i<object->metaObject()->propertyCount(); i++)
      {
           QMetaProperty prop = object->metaObject()->property(i);
           dbg.nospace() << prop.name() << "=" << prop.read(object)<< " ; ";
      }

    return dbg;
}


}
}
