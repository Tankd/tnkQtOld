#include "csvparser.h"

#include <QFile>
#include <QTextCodec>

namespace tnk {
namespace parser {

CsvParser::CsvParser()
    :BaseParser()
{

}

void CsvParser::open(const QString &path)
{
    m_inFile = new QFile(path);
    if(m_inFile->open(QIODevice::Text | QIODevice::ReadOnly) == false)
        return;

    m_isOpen = true;
    m_tables << "sheet";
}

void CsvParser::close()
{
    if(m_inFile)
        m_inFile->close();
    m_inFile = nullptr;
}

BaseParser::RowData CsvParser::nextRow()
{
    RowData data;

    QString line = QTextCodec::codecForName( "ISO-8859-15" )->toUnicode( m_inFile->readLine());
    if(line.contains("Nb :")) return data;
    if(line.isEmpty()) return data;


    QStringList split = line.split(";");
    if( split.count()< m_headers.count())
        return data;
    for(int i=0; i< m_headers.count(); i++)
    {
        QString s = split.at(i);


        data[m_headers.at(i)] = s.trimmed();
    }

    return data;
}


}}


void tnk::parser::CsvParser::selectTable(const QString &tableName, int headerLine)
{


    for(int i=0; i<headerLine; i++)
    {
        m_inFile->readLine();
    }

    QString line = QTextCodec::codecForName( "ISO-8859-15" )->toUnicode( m_inFile->readLine());

    line = decodeString( line.toLocal8Bit());

    QStringList TempHeaders;
    m_headers.clear();

    TempHeaders = line.split(";");

    int currentCol = 1;

    foreach(QString h, TempHeaders)
    {
        if( headerLine >= 0)
        {
            h = h.trimmed();
            m_headers.push_back(h);
        }
        else
        {
            m_headers.append( QString("Colonne %1").arg(nth_letter(currentCol)));
            currentCol++;
        }
    }

    if( headerLine < 0)
        m_inFile->seek(0);

}
