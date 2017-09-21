#ifndef UTILS_H
#define UTILS_H

#include <QString>

namespace tnk {
namespace utils
{


QByteArray fromFile( const QString& fileName);
bool toFile( const QString& fileName, const QByteArray& data);

}
}

#endif // UTILS_H
