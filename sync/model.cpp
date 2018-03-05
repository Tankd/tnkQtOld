#include "model.h"

namespace tnk {
namespace sync{


Model::Model(Engine *engine,QObject *parent) : QAbstractListModel(parent),
    m_dataSync( engine), m_syncToSql(false)
{

}

int Model::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED( parent)
    return m_objects.count();
}


QVariant Model::data(const QModelIndex &index, int role) const
{
    if(index.row() >= rowCount()) {
        return QString("");
    }
    else if(role < Qt::UserRole)
    {
        return QString("");
    }
    else {
        return customData(index, role);
        return "1";
    }
}

bool Model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    qDebug() << "setdata";
    bool ret = false;

    if(index.row() >= rowCount()) {
        ret = false;
    }
    else if(role < Qt::UserRole)
    {
        ret = false;
    }
    else {
        QMetaProperty prop = getDataProperty(role);

        ret = prop.write( m_objects.at(index.row()), value);
        if( m_syncToSql)
            m_dataSync->update( m_objects.at(index.row()));
    }

    return ret;
}

void Model::select() {
    clear();
    subSelect();
    generateRoleNames();
}


}
}
