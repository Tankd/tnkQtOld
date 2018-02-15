#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "sync/engine.h"
#include "common/jsonobject.h"

#include "sync/mymodel.h"


#include "myobject.h"

#define SYNCMODEL_GENERATE(T) \
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
    auto typedObjects = (m_dataSync->select<T>());\
    foreach( auto obj, typedObjects)\
{\
    m_objects << obj;\
    }\
    }

class MyObjectModel : public tnk::sync::MyModel {

public:
    MyObjectModel(tnk::sync::Engine *engine, QObject *parent = nullptr)
        :tnk::sync::MyModel( engine, parent)
    { }

    SYNCMODEL_GENERATE(MyObject)
};




int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);





    auto syncEngine = new tnk::sync::Engine();
    syncEngine->setDb( QSqlDatabase::addDatabase("QSQLITE"));
    syncEngine->db().setDatabaseName("demo.sqlite");
    syncEngine->db().open();
    syncEngine->registerType<MyObject>();

    auto model = new MyObjectModel( syncEngine);
    model->set_syncToSql(true);
    model->select();


    if( !model->count())
    {
        for(int i=0; i<10; i++)
        {
            auto myObject = new MyObject();
            myObject->set_count(i);
            myObject->set_name("azerty");
            model->append( myObject);
        }
    }


    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("myModel", model);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
