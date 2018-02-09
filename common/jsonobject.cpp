#include "jsonobject.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#include <QDebug>

namespace tnk {

JSonObject::JSonObject()
{

}

QByteArray JSonObject::toString() const
{
    return QJsonDocument(m_data).toJson();
}


void JSonObject::load(const QString &fileName)
{
    QFile in( fileName);
    in.open(QFile::ReadOnly);

    m_data = QJsonDocument::fromJson( in.readAll()).object();
    in.close();
}

void JSonObject::save(const QString &fileName)
{

}

QJsonValue JSonObject::value(QString path)
{
    QStringList paths = path.split("/");

    QJsonValue val = QJsonValue(m_data);

    while( paths.count())
    {
        val = val.toObject().value(paths.at(0));
        paths.removeFirst();
    }

    return val;
}

void JSonObject::setValue(QString path, QJsonValue value)
{
    setValue(&m_data, path, value);
}


void JSonObject::setValue(QJsonObject* object, QString path, QJsonValue value)
{
    QStringList paths = path.split("/");
    if( paths.count()>1) // CREATE CHILD
    {
        QString path0 = paths.at(0);
        paths.removeFirst();
        QJsonObject obj;
        if( object->keys().contains(path0))
            obj = object->value(path0).toObject();

        setValue( &obj, paths.join("/"), value);
        object->insert( path0, obj);
    }
    else //SET VALUE
    {
        object->insert(path, value);
    }
}

bool JSonObject::isValid() const {
    return m_data.isEmpty() == false;
}

QJsonObject JSonObject::data() const
{
    return m_data;
}

}
