#ifndef MYOBJECT_H
#define MYOBJECT_H

#include "sync/object.h"
#include "common/easyproperty.h"

class MyObject : public tnk::sync::Object
{
    Q_OBJECT
public:
    explicit MyObject(QObject *parent = nullptr);

    PROPERTY(int, count)
    PROPERTY( QString, name)
signals:

public slots:
};

#endif // MYOBJECT_H
