#ifndef XLSPARSER_H
#define XLSPARSER_H

#include "baseparser.h"
#include "sql/sqldatabase.h"

namespace tnk {
namespace parser {

class XlsParser : public BaseParser
{
public:
    XlsParser();

    // baseParser interface
public:
    void open(const QString &path);
    void close();
    RowData nextRow();


private:
    QSqlDatabase m_excel;
    QSqlQuery query;
};

}}

#endif // XLSPARSER_H
