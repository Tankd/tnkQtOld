#include "baseparser.h"

#include <QFile>
#include <QFileInfo>
#include <QTextCodec>
#include <QSqlError>

#include <QDebug>

namespace tnk {
namespace parser {

BaseParser::BaseParser()
{

}

QString BaseParser::decodeString(const QByteArray &str, const QByteArray &codecName)
{
    QString s = QTextCodec::codecForName( codecName )->toUnicode(str);
    s.replace(QRegExp("[éèë]"), "e");
    s.replace(QRegExp("[à]"), "a");
    s.replace(QRegExp("[à]"), "a");
    s.replace(QRegExp("°"), "_");
    s.replace( QRegExp("[^A-Za-z0-9éèë/ ]"), "");
    s.replace("  ", " ");
    return s;
}

QStringList BaseParser::headers() const
{
    return m_headers;
}


}
}
