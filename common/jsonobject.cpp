#include "jsonobject.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#include <QDebug>

namespace tnk {

JsonObject::JsonObject()
{

}

JsonObject::JsonObject(const QJsonValue &value)
{
    m_data = value.toObject();
}

QByteArray JsonObject::toString() const
{
    return QJsonDocument(m_data).toJson();
}


void JsonObject::load(const QString &fileName)
{
    QFile in( fileName);
    in.open(QFile::ReadOnly);

    m_data = QJsonDocument::fromJson( in.readAll()).object();
    in.close();
}

void JsonObject::save(const QString &fileName)
{
    QFile out( fileName);
    out.open( QFile::WriteOnly);
    out.write(QJsonDocument(m_data).toJson());
    out.close();
}

QJsonValue JsonObject::value(QString path)
{
    QStringList paths = path.split("/");

    QJsonValue val = QJsonValue(m_data);

    while( paths.count())
    {
        QString path = paths.at(0);
        if( path.contains("["))
        {
            QRegExp exp("\\[(.*)\\]");
            exp.indexIn(path);
            uint index = exp.cap(1).toUInt();
            path = path.remove( path.indexOf("["), path.count());
            val = val.toObject().value(path).toArray().at( index);
        }
        else
        {
            val = val.toObject().value(paths.at(0));
        }
        paths.removeFirst();
    }

    return val;
}

void JsonObject::setValue(QString path, QJsonValue value)
{
    if( path.contains("["))
        qDebug() << "JsonObject::setValue don't manage arrays";
    setValue(&m_data, path, value);
}


void JsonObject::setValue(QJsonObject* object, QString path, QJsonValue value)
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

bool JsonObject::isValid() const {
    return m_data.isEmpty() == false;
}

QJsonObject JsonObject::data() const
{
    return m_data;
}

}
