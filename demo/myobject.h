#ifndef MYOBJECT_H
#define MYOBJECT_H

#include "sync/object.h"
#include "sync/model.h"
#include "common/easyproperty.h"

#include "mysubobject.h"

class MyObject : public tnk::sync::Object
{
    Q_OBJECT
public:
    explicit MyObject(QObject *parent = nullptr);

    PROPERTY(int, count)
    PROPERTY( QString, name0)
    PROPERTY( MySubObject*, sub)
    signals:

        public slots:
};



    class MyObjectModel : public tnk::sync::Model {

    public:
        MyObjectModel(tnk::sync::Engine *engine, QObject *parent = nullptr)
            :tnk::sync::Model( engine, parent)
        { }

        SYNCMODEL(MyObject)
    };



#endif // MYOBJECT_H
