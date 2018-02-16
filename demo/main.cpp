#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "sync/engine.h"
#include "common/jsonobject.h"
#include "common/timer.h"
#include "sync/model.h"

#include "myobject.h"




int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
QFile::remove("demo.sqlite");




    auto syncEngine = new tnk::sync::Engine();
    syncEngine->setDb( QSqlDatabase::addDatabase("QSQLITE"));
    syncEngine->db().setDatabaseName("demo.sqlite");
    syncEngine->db().open();

    syncEngine->registerType<MySubObject>();
    syncEngine->registerType<MyObject>();

    auto model = new MyObjectModel( syncEngine);
    model->set_syncToSql(true);
    model->generateRoleNames();


    if( !model->count())
    {
        syncEngine->db().transaction();
        tnk::Timer::self()->restart();
        for(int i=0; i<5000; i++)
        {
            auto myObject = new MyObject();
            myObject->set_count(i);
            myObject->set_name0("azerty");
            myObject->set_sub( new MySubObject());
            myObject->get_sub()->set_name("subname");
            model->append( myObject);
        }
        syncEngine->db().commit();
        tnk::Timer::self()->displayElapsed("create object");
    }

    tnk::Timer::self()->restart();
    model->select();
    tnk::Timer::self()->displayElapsed(" model->select();");


    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("myModel", model);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
