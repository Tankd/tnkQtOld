#ifndef DATASYNCOBJET_H
#define DATASYNCOBJET_H

#include <QObject>
#include <QDateTime>
#include "common/easyproperty.h"

#include <QJsonObject>
#include <QUuid>


#include <QDebug>

namespace tnk{
namespace sync{

class Object : public QObject
{
    Q_OBJECT



public:
    explicit Object( QObject *parent = 0);

    PROPERTY(int, id)

    public:

        static int dataFirstIndex;
    /*
    virtual QJsonObject toJsonObject(DataSync::Database *base);
    virtual void fromJsonObject(DataSync::Database *base, QJsonObject jsonObject);
    */
};

QDebug operator<<(QDebug dbg, const Object *object);

}}

#endif // DATASYNCOBJET_H
