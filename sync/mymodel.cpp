#include "mymodel.h"

namespace tnk {
namespace sync{


MyModel::MyModel(Engine *engine,QObject *parent) : QAbstractListModel(parent),
    m_dataSync( engine)
{

}

int MyModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED( parent)
    return m_objects.count();
}


QVariant MyModel::data(const QModelIndex &index, int role) const
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

bool MyModel::setData(const QModelIndex &index, const QVariant &value, int role)
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

void MyModel::select() {
    clear();
    subSelect();
    generateRoleNames();
}


}
}
