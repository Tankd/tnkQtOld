#include "axxlsparser.h"

#include <QAxObject>
#include <QDebug>

namespace tnk {
namespace parser {


AxXlsParser::AxXlsParser()
    :BaseParser(), excel(0), workbooks(0), workbook(0), sheets(0),
      m_currentRow(0)
{

}

AxXlsParser::~AxXlsParser()
{
    if(excel)
    {
        delete excel;
        excel = 0;
    }
}



void tnk::parser::AxXlsParser::open(const QString &path)
{
    m_isOpen = false;
    m_tables.clear();

    if(excel == 0)
        excel =  new QAxObject("Excel.Application");


    if(workbooks == 0)
        workbooks = excel->querySubObject( "Workbooks" );


    if( workbooks == 0)
    {

        m_isOpen == false;
        if(excel)
        {
            excel->dynamicCall("Quit()");
            delete excel;
            excel = 0;
        }

        return;
    }
    workbook = workbooks->querySubObject( "Open(const QString&)", path);
    sheets = workbook->querySubObject( "Worksheets" );

    int sheetCount = sheets->property("Count").toInt();
    for(int i=1; i<=sheetCount; i++)
    {
        QAxObject * worksheet = workbook->querySubObject("Worksheets(int)", i);
        m_tables.append( worksheet->property("Name").toString());
    }


    m_isOpen = true;
}

char nth_letter(int n)
{
    return static_cast<char>('A' - 1 + n);
}

void AxXlsParser::selectTable(bool withHeaders, const QString &tableName)
{
    m_headers.clear();




    if( m_tables.contains( tableName) == false)
        return;

    sheet = workbook->querySubObject("Worksheets(string)", tableName);

    m_headers.clear();

    if( withHeaders)
    {



        int currentCol = 1;
        while(1)
        {
            QAxObject * range = sheet->querySubObject("Cells(int,int)", 1, currentCol );
            QString str = range->property("Value").toString().trimmed();
            if( str.isEmpty())
                break;


            m_headers.append( str);

            currentCol++;
        }

        m_currentRow = 2;
    }
    else
    {


        int currentCol = 1;
        while(1)
        {
            QAxObject * range = sheet->querySubObject("Cells(int,int)", 1, currentCol );
            QString str = range->property("Value").toString().trimmed();
            if( str.isEmpty())
                break;


            m_headers.append( QString("Colonne %1").arg(nth_letter(currentCol)));
            currentCol++;
        }

        m_currentRow = 1;
    }

}

void tnk::parser::AxXlsParser::close()
{
    if(workbook)
    {

        workbook->dynamicCall("Close()");
        delete workbook;
        workbook = 0;
    }
    if(excel)
    {
        excel->dynamicCall("Quit()");
        delete excel;
        excel = 0;
    }

    /* QAxObject *excel;
            QAxObject *workbooks;
            QAxObject *workbook;
            QAxObject *sheets;
            QAxObject *sheet;*/
}

BaseParser::RowData tnk::parser::AxXlsParser::nextRow()
{
    RowData data;

    for(int i=0; i< m_headers.count(); i++)
    {
        QAxObject *range = sheet->querySubObject("Cells(int,int)", m_currentRow, i+1 );

        data[m_headers.at(i)] = decodeString(  range->property("Value").toString().toLocal8Bit());

    }

    bool empty = true;

    for(int i=0; i< m_headers.count(); i++)
        if(data[m_headers.at(i)].isEmpty() == false )
        {
            empty = false;
            break;
        }

    if( empty == true)
    {
        data.clear();
        return data;
    }



    /*
            QString line = QTextCodec::codecForName( "ISO-8859-15" )->toUnicode( m_inFile->readLine()).remove(0, 2);
            if(line.contains("Nb :")) return data;
            if(line.isEmpty()) return data;


            QStringList split = line.split(";");
            for(int i=0; i< m_headers.count(); i++)
            {
                QString s = split.at(i);
                s = decodeString( s.toLocal8Bit());

                data[m_headers.at(i)] = s;
            }*/

    m_currentRow++;
    return data;
}



}
}

