#ifndef BASEPARSER_H
#define BASEPARSER_H

#include "parser_global.h"
#include <QMap>

namespace tnk {
namespace parser {

class Q_TNK_PARSER_EXPORT BaseParser
{
public:
    typedef QMap< QString, QString > RowData;

    BaseParser();
    virtual ~BaseParser(){}

    virtual void open( const QString& path) = 0;
    virtual void selectTable( const QString& tableName = QString(), int headerLine = 0 ) = 0;
    virtual void close() = 0;
    virtual RowData nextRow() = 0;

    virtual QList<RowData> readAll();

    QString decodeString(const QByteArray& str, const QByteArray &codecName = "ISO-8859-15");
    QString decodeString(const QString &str);


    QStringList headers() const;

    bool isOpen() const;

    QStringList tables() const;

    char nth_letter(int n)
    {
        return static_cast<char>('A' - 1 + n);
    }


protected:
    QStringList m_headers;
    bool m_isOpen;
    QStringList m_tables;

};
}
}

#endif // BASEPARSER_H
