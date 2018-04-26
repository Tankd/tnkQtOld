#ifndef BASEPARSER_H
#define BASEPARSER_H

#include <QMap>

namespace tnk {
namespace parser {

class BaseParser
{
public:
    typedef QMap< QString, QString > RowData;

    BaseParser();

    virtual void open( const QString& path) = 0;
    virtual void close() = 0;
    virtual RowData nextRow() = 0;

    QString decodeString(const QByteArray& str, const QByteArray &codecName = "ISO-8859-15");



    QStringList headers() const;

protected:
    QStringList m_headers;

};
}
}

#endif // BASEPARSER_H
