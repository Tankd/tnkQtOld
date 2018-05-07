#include "csvparser.h"

#include <QFile>
#include <QTextCodec>

namespace tnk {
namespace parser {

CsvParser::CsvParser()
:BaseParser(), m_inFile(0)
{

}

void CsvParser::open(const QString &path)
{
    m_inFile = new QFile(path);
    if(m_inFile->open(QIODevice::Text | QIODevice::ReadOnly) == false)
        return;


    QString line = QTextCodec::codecForName( "ISO-8859-15" )->toUnicode( m_inFile->readLine()).remove(0, 2);

    line.replace(QRegExp("[éèë]"), "e");
    line.replace(QRegExp("[à]"), "a");
    line.replace(QRegExp("[à]"), "a");
    line.replace(QRegExp("°"), "");
    //line.replace(QRegExp("."), "");
    line.replace(QRegExp("  "), " ");


    QStringList TempHeaders;

    TempHeaders = line.split(";");



    foreach(QString h, TempHeaders)
    {
        h = h.trimmed();
        m_headers.push_back(h);
    }

}

void CsvParser::close()
{
    if(m_inFile)
        m_inFile->close();
    m_inFile = 0;
}

BaseParser::RowData CsvParser::nextRow()
{
    RowData data;

    QString line = QTextCodec::codecForName( "ISO-8859-15" )->toUnicode( m_inFile->readLine()).remove(0, 2);
    if(line.contains("Nb :")) return data;
    if(line.isEmpty()) return data;


    QStringList split = line.split(";");
    for(int i=0; i< m_headers.count(); i++)
    {
        QString s = split.at(i);
        s = decodeString( s.toLocal8Bit());

        data[m_headers.at(i)] = s;
    }

    return data;
}


}}
