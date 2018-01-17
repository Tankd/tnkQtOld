#include "object.h"

#include <QMetaProperty>

namespace tnk{
namespace sync{

int Object::dataFirstIndex = 3;

Object::Object( QObject *parent) : QObject(parent)
{
    m_id = -1;
}

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
