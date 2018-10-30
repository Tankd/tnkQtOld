#ifndef CSVPARSER_H
#define CSVPARSER_H

#include "parser_global.h"
#include "baseparser.h"

class QFile;

namespace tnk {
namespace parser {


class Q_TNK_PARSER_EXPORT CsvParser : public BaseParser
{
public:
    CsvParser();

    // baseParser interface
public:
    void open(const QString &path);
    void close();
    RowData nextRow();



private:
      QFile *m_inFile = nullptr;

      // BaseParser interface
public:
      void selectTable(const QString& tableName = QString(), int headerLine = 0);
};

}}
#endif // CSVPARSER_H
