#ifndef CSVPARSER_H
#define CSVPARSER_H

#include "baseparser.h"

class QFile;

namespace tnk {
namespace parser {


class CsvParser : public BaseParser
{
public:
    CsvParser();

    // baseParser interface
public:
    void open(const QString &path);
    void close();
    RowData nextRow();



private:
      QFile *m_inFile;
};

}}
#endif // CSVPARSER_H
