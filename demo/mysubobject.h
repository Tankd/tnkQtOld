#ifndef MYSUBOBJECT_H
#define MYSUBOBJECT_H

#include "sync/object.h"
#include "common/easyproperty.h"

class MySubObject : public tnk::sync::Object
{
    Q_OBJECT
public:
    explicit MySubObject(QObject *parent = nullptr);
    PROPERTY( QString, name)
};

#endif // MYSUBOBJECT_H
