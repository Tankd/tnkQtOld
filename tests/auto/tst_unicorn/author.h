#ifndef AUTHOR_H
#define AUTHOR_H

#include <entity.h>

class Author : public unicorn::Entity
{
    Q_OBJECT
public:
    explicit Author(QObject *parent = nullptr);

    UC_PROPERTY(QString, name, QString())

};

#endif // AUTHOR_H
