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

    virtual QList<RowData> readAll()
    {
        QList<RowData> result;

        while(1)
        {

            auto row = nextRow();
            if( row.isEmpty())
                break;

            result << row;

        }


        return result;
    }

    QString decodeString(const QByteArray& str, const QByteArray &codecName = "ISO-8859-15");



    QStringList headers() const;

protected:
    QStringList m_headers;

};
}
}

#endif // BASEPARSER_H
