#ifndef MYMODEL_H
#define MYMODEL_H

#include <QAbstractListModel>

#include "engine.h"
#include "object.h"
#include "common/easyproperty.h"
namespace tnk {
namespace sync{

#define SYNCMODEL(T) \
    public:\
    virtual void generateRoleNames()\
{\
    m_roles.clear();\
    int nbCols = T::staticMetaObject.propertyCount();\
    for (int i = 0; i < nbCols; i++) m_roles[Qt::UserRole + i + 1] = T::staticMetaObject.property(i).name();\
}\
    virtual  QVariant customData(const QModelIndex &index, int role) const\
{\
    return  T::staticMetaObject.property(role - Qt::UserRole - 1).read( m_objects.at( index.row()));\
}\
    virtual  QMetaProperty getDataProperty(int role)\
{\
    return T::staticMetaObject.property(role - Qt::UserRole - 1);\
}\
    virtual void subSelect() {\
   m_objects = (m_dataSync->selectObjects<T>());\
}


class Model : public QAbstractListModel
{
    Q_OBJECT

    PROPERTY(bool, syncToSql)
    public:
        explicit Model(Engine *engine, QObject *parent = nullptr);

    virtual int rowCount(const QModelIndex &parent  = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    void select();

    virtual QHash<int, QByteArray> roleNames() const{return m_roles;}
    virtual void generateRoleNames() = 0;

public slots:
    virtual int count (void) const
    {
        return m_objects.count();
    }

    virtual bool isEmpty (void) const
    {
        return (m_objects.count() == 0);
    }

    virtual bool contains (Object * item) const
    {
        return m_objects.contains( item);
    }
    virtual int indexOf (Object * item) const
    {
        return m_objects.indexOf( item);
    }
    virtual void clear (void){
        beginResetModel();
        m_objects.clear();
        endResetModel();
    }
    virtual void append (Object * item){
        int i=rowCount();
        if( m_syncToSql)
            m_dataSync->update(item);
        beginInsertRows(QModelIndex(), i, i);
        m_objects.append( item);
        endInsertRows();
    }
    virtual void prepend (Object * item)
    {
        if( m_syncToSql)
            m_dataSync->update(item);
        beginInsertRows(QModelIndex(), 0, 0);
        m_objects.prepend( item);
        endInsertRows();
    }



    virtual void remove (int idx){
        if( m_syncToSql)
            m_dataSync->remove(m_objects.at(idx));

        beginRemoveRows(QModelIndex(), idx, idx);
        m_objects.removeAt( idx);
        endRemoveRows();
    }

    virtual Object * get (int idx) const{
        if( idx > count())
            return NULL;
        return m_objects.at(idx);
    }

protected:
    virtual  QVariant customData(const QModelIndex &index, int role) const = 0;
    virtual QMetaProperty getDataProperty(int role) = 0;
    virtual void subSelect() = 0;

    tnk::sync::Engine *m_dataSync;
    QList<Object*> m_objects;
    QHash<int, QByteArray> m_roles;
};

}}

#endif // MYMODEL_H
