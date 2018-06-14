#ifndef AXXLSPARSER_H
#define AXXLSPARSER_H
#include "baseparser.h"

class QAxObject;


namespace tnk {
namespace parser {


class AxXlsParser : public BaseParser
{
public:
    AxXlsParser();
    virtual ~AxXlsParser();

private:
    QAxObject *excel;
    QAxObject *workbooks;
    QAxObject *workbook;
    QAxObject *sheets;
    QAxObject *sheet;

    int m_currentRow;

    // BaseParser interface
public:
    void open(const QString &path);
    void close();
    RowData nextRow();    
    void selectTable(bool withHeaders,const QString &tableName);


};
}
}

#endif // AXXLSPARSER_H
