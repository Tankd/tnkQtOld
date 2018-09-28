#ifndef ENTITY_H
#define ENTITY_H

#include "unicorn_global.h"
#include <QObject>


#include <QJsonObject>
#include <QMetaProperty>

#define UC_PROPERTY(type, name, defaultValue) \
    Q_SIGNALS: \
    void name##Changed(); \
    public:                          \
    Q_PROPERTY(type name READ get_##name() WRITE set_##name NOTIFY name##Changed)  \
    type get_##name() const { return m_##name; } \
    void set_##name( type value) { m_##name = value; emit  name##Changed(); } \
    private: \
    type m_##name = defaultValue;


class QSqlRecord;

namespace unicorn {

class Q_TNK_UNICORN_EXPORT Entity : public QObject
{
    Q_OBJECT
public:
    explicit Entity(QObject* parent = nullptr);

    QJsonObject toJsonObject();

    UC_PROPERTY( int, id, -1)
};

}

#endif // ENTITY_H
