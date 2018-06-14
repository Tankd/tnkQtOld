#include "baseparser.h"

#include <QFile>
#include <QFileInfo>
#include <QTextCodec>
#include <QSqlError>

#include <QDebug>

namespace tnk {
namespace parser {

BaseParser::BaseParser()
    :m_isOpen(false)
{

}

QList<BaseParser::RowData> BaseParser::readAll()
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

QString BaseParser::decodeString(const QByteArray &str, const QByteArray &codecName)
{
    QString s = QTextCodec::codecForName( codecName )->toUnicode(str);
    return decodeString(s);
}

QString BaseParser::decodeString(const QString &str)
{
    QString s = str;
    s.replace(QRegExp("[éèë]"), "e");
    s.replace(QRegExp("[à]"), "a");
    s.replace(QRegExp("[à]"), "a");
    s.replace(QRegExp("°"), "_");
    s.replace( QRegExp("[^A-Za-z0-9.@<>éèë/ ]"), "");
    s.replace("  ", " ");
    return s;
}

QStringList BaseParser::headers() const
{
    return m_headers;
}

bool BaseParser::isOpen() const
{
    return m_isOpen;
}

QStringList BaseParser::tables() const
{
    return m_tables;
}


}
}
