#ifndef JSONCONFIG_H
#define JSONCONFIG_H

#include <QJsonValue>
#include <QJsonObject>

#include "common_global.h"

namespace tnk {

class Q_TNK_COMMON_EXPORT JsonObject
{
public:
    JsonObject();
    JsonObject( const QJsonValue& value);


    QByteArray toString() const;
    void load( const QString& fileName);
    void save( const QString& fileName);

    QJsonValue value( QString path);


    void setValue(QString path, QJsonValue value);

    bool isValid() const;
    QJsonObject data() const;



private:
    QJsonObject m_data;

    void setValue(QJsonObject *object, QString path, QJsonValue value); //no array
};

}
#endif // JSONCONFIG_H
