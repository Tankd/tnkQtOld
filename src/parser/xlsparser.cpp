#include "xlsparser.h"

#include <QDebug>
#include <QFileInfo>
#include <QProcess>


namespace tnk {
namespace parser {


XlsParser::XlsParser()
    :BaseParser()
{

}

void XlsParser::open(const QString &path)
{
    m_isOpen = false;

    QProcess p;
    p.setProgram("pyxls.exe");
    QStringList args;
    args << "list";
    args <<  path;
    p.setArguments( args);
    p.start();
    p.waitForStarted();
    p.waitForFinished();

    auto result = QString( p.readAll()).split("\r\n");
    result.removeAll("");
    QString line = result.last();
    line.remove("[");
    line.remove("]");
    line.remove("'");
    m_tables = line.split(",");

    m_isOpen = true;
    m_filePath = path;
}

void XlsParser::close()
{
    /*if(m_excel)
    {
        delete m_excel;
        m_excel = 0;
    }*/
}

BaseParser::RowData XlsParser::nextRow()
{

    RowData data;

    if( m_currentRow >= m_lines.count())
        return data;

    QStringList line = m_lines.at( m_currentRow).split(";");

    for(int i=0; i< line.count(); i++)
    {
        data[m_headers.at(i)] =  line.at(i).trimmed();
    }

    m_currentRow++;
    return data;
}




void XlsParser::selectTable(const QString &tableName, int headerLine)
{


    if( m_tables.contains( tableName) == false)
        return;


    QProcess p;
    p.setProgram("pyxls.exe");
    QStringList args;
    args << "get";
    args <<  m_filePath;
    args << tableName;
    p.setArguments( args);
    p.start();
    p.waitForStarted();
    p.waitForFinished();


    m_lines = QString::fromUtf8( p.readAll()).split("\r\n");
    if( m_lines.isEmpty())
        return;

    if(m_lines.first().contains("WARNING "))
        m_lines.removeFirst();



    for(int i=0; i<headerLine; i++)
    {
        m_lines.removeFirst();
    }



    m_headers.clear();

    QStringList TempHeaders;

    m_headers.clear();

    TempHeaders = m_lines.first().split(";");

    TempHeaders.removeAll("");

    int currentCol = 1;

    foreach(QString h, TempHeaders)
    {
        if( headerLine >= 0)
        {
            h = decodeString( h.trimmed());
            m_headers.push_back(h);
        }
        else
        {
            m_headers.append( QString("Colonne %1").arg(nth_letter(currentCol)));
            currentCol++;
        }
    }


    m_currentRow = (headerLine>=0) ? 1 : 0;

}

}}
