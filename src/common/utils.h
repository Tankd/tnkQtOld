#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include "common_global.h"

namespace tnk {
namespace utils
{

#define PROPERTY(type, name) \
    Q_SIGNALS: \
    void name##Changed(); \
    public:                          \
    Q_PROPERTY(type name READ get_##name() WRITE set_##name NOTIFY name##Changed)  \
    type get_##name() const { return m_##name; } \
    void set_##name( type value) { m_##name = value; emit  name##Changed(); } \
    private: \
    type m_##name;

Q_TNK_COMMON_EXPORT QByteArray  fromFile( const QString& fileName);
Q_TNK_COMMON_EXPORT bool  toFile( const QString& fileName, const QByteArray& data);



}
}

#endif // UTILS_H
