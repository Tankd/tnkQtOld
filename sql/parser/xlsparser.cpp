#include "xlsparser.h"
#include <QDebug>
#include <QFileInfo>
#include <QSqlDriver>
#include <QSqlField>

namespace tnk {
namespace parser {


XlsParser::XlsParser()
    :BaseParser()
{

}

void XlsParser::open(const QString &path)
{
    m_excel = QSqlDatabase::addDatabase("QODBC", "xlsx_connection");
    m_excel.setDatabaseName("DRIVER={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};DBQ=" + QFileInfo(path).absoluteFilePath());
    m_excel.open();
    if( m_excel.isOpen() == false)
    {
        sql::showSqlDebug( &m_excel);
        return;
    }

    QStringList tables = m_excel.driver()->tables(QSql::AllTables);
    if( tables.isEmpty())
    {
        close();
        return;
    }
    qDebug() << tables.at(0);

    query = QSqlQuery("select * from [" + tables.at(0) + "]", m_excel); // Select range, place A1:B5 after $
    /*while (query.next())
    {
        QString column1= query.value(0).toString();
        qDebug() << column1;
    }
    */

    for( int i=0; i<query.record().count(); i++)
       m_headers << decodeString( query.record().field(i).name().toLocal8Bit());
}

void XlsParser::close()
{
    m_excel.close();
   // QSqlDatabase::removeDatabase("xlsx_connection");
}

BaseParser::RowData XlsParser::nextRow()
{
    RowData data;
    if( query.next())
    {

       for(int i=0; i<query.record().count(); i++)
       {
            data[m_headers.at(i)] = query.value(i).toString();
       }
    }
    return data;
}

}}
