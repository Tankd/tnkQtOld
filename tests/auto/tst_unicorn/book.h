#ifndef BOOK_H
#define BOOK_H

#include <entity.h>

#include "author.h"

class Book : public unicorn::Entity
{
    Q_OBJECT
public:
    explicit Book();

    UC_PROPERTY( QString, title, QString())
    UC_PROPERTY( QString, isbn, QString())
    UC_PROPERTY( int, pageCount, 0)
    UC_PROPERTY( Author*, author, new Author())


};

#endif // BOOK_H
