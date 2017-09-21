#ifndef MYMODEL_H
#define MYMODEL_H

#include <QAbstractListModel>
#include "engine.h"

namespace tnk{
namespace sync{

class ModelBase : public QAbstractListModel { // abstract Qt base class
    Q_OBJECT
    Q_PROPERTY (int count READ count NOTIFY countChanged)

public:
    explicit ModelBase (Engine * parent) : QAbstractListModel (parent) { }

public slots: // virtual methods API for QML
    virtual void select() = 0;
    virtual int count (void) const = 0;
    virtual bool isEmpty (void) const = 0;
    virtual bool contains (QObject * item) const = 0;
    virtual int indexOf (QObject * item) const = 0;
    virtual void clear (void) = 0;
    virtual void append (QObject * item) = 0;
    virtual void prepend (QObject * item) = 0;

    virtual void remove (QObject * item) = 0;
    virtual void remove (int idx) = 0;
    virtual QObject * get (int idx) const = 0;


protected slots: // internal callback
   //virtual void onItemPropertyChanged (int row) = 0;

signals: // notifier
    void countChanged (void);
};


/***********************************************/

template< class T>
class Model : public ModelBase
{

public:
    explicit Model(Engine *parent) : ModelBase(parent)
    {
        m_dataSync = parent;
        generateRoleNames();
m_syncToSql = false;

    }



    // QAbstractItemModel interface

    virtual int rowCount(const QModelIndex &parent  = QModelIndex()) const override
    {
        return m_objects.count();
    }

    virtual QVariant data(const QModelIndex &index, int role) const override
    {
        if(index.row() >= rowCount()) {
            return QString("");
        }
        else if(role < Qt::UserRole)
        {
            return QString("");
        }
        else {
            return  T::staticMetaObject.property(role - Qt::UserRole - 1).read( m_objects.at( index.row()));
        }
    }

    virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override
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
            QMetaProperty prop = T::staticMetaObject.property(role - Qt::UserRole - 1);
            ret = prop.write( m_objects.at(index.row()), value);
            if( m_syncToSql)
                m_dataSync->update( m_objects.at(index.row()));
        }

        return ret;
    }

    // MyModelBase interface

    virtual void select()
    {
        m_objects = m_dataSync->select<T>();
    }

    virtual QHash<int, QByteArray> roleNames() const{return m_roles;}

    void generateRoleNames()
    {

        m_roles.clear();
        int nbCols = T::staticMetaObject.propertyCount();

        for (int i = 0; i < nbCols; i++) {
            m_roles[Qt::UserRole + i + 1] = T::staticMetaObject.property(i).name();
        }
    }

    virtual int count() const override
    {
        return m_objects.count();
    }
    virtual bool isEmpty() const override
    {
        return (m_objects.count() == 0);
    }
    bool contains(T *item) const
    {
        return m_objects.contains( item);
    }
    int indexOf(T *item) const
    {
        return m_objects.indexOf( item);
    }
    virtual void clear() override
    {
        beginResetModel();
        m_objects.clear();
        endResetModel();
    }
    void append(T *item)
    {
        int i=rowCount();
        if( m_syncToSql)
            m_dataSync->update(item);
        beginInsertRows(QModelIndex(), i, i);        
        m_objects.append( item);        
        endInsertRows();
    }
    void prepend(T *item)
    {
        if( m_syncToSql)
            m_dataSync->update(item);
        beginInsertRows(QModelIndex(), 0, 0);        
        m_objects.prepend( item);
        endInsertRows();

    }
    void remove(T *item)
    {
        remove(indexOf( item));

    }

    void remove(int idx)
    {
        if( m_syncToSql)
            m_dataSync->remove(m_objects.at(idx));

        beginRemoveRows(QModelIndex(), idx, idx);
        m_objects.removeAt( idx);
        endRemoveRows();

    }
    QObject *get(int idx) const
    {
        if( idx > count())
            return NULL;
        return m_objects.at(idx);
    }


private:
    Engine *m_dataSync;
    QHash<int, QByteArray> m_roles;
    QList<T*> m_objects;

    bool m_syncToSql;


public:
    // QML Interface
    virtual bool contains(QObject *item) const override
    {
        return contains (qobject_cast<T *> (item));
    }
    virtual int indexOf(QObject *item) const override
    {
        return indexOf (qobject_cast<T *> (item));
    }
    virtual void append(QObject *item) override
    {
        append (qobject_cast<T *> (item));
    }
    virtual void prepend(QObject *item) override
    {
        prepend (qobject_cast<T *> (item));
    }
    virtual void remove(QObject *item) override
    {
        remove (qobject_cast<T *> (item));
    }


    bool getSyncToSql() const
    {
        return m_syncToSql;
    }
    void setSyncToSql(bool syncToSql)
    {
        m_syncToSql = syncToSql;
    }
};

}
}

#endif // MYMODEL_H
