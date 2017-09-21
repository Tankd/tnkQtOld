#include "utils.h"

#include <QFile>
namespace tnk {

namespace utils
{


QByteArray fromFile(const QString &fileName)
{
    QFile in( fileName);
    in.open(QFile::ReadOnly);
    if( in.isOpen() == false)
        return QByteArray();
    QByteArray ba = in.readAll();
    in.close();

    return ba;
}

bool toFile(const QString &fileName, const QByteArray &data)
{
    QFile out(fileName);
    out.open(QFile::WriteOnly);

    if( out.isOpen() == false)
        return false;

    out.write( data);
    out.close();

    return true;
}


}
}
