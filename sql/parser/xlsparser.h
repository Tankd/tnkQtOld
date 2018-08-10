#ifndef XLSPARSER_H
#define XLSPARSER_H

#include "csvparser.h"

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
    QString m_filePath;
     int m_currentRow;


     QStringList m_lines;




    // BaseParser interface
public:
    void selectTable(const QString& tableName = QString(), int headerLine = 0);
};

}}

#endif // XLSPARSER_H
