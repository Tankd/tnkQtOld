#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "sync/engine.h"
#include "common/jsonobject.h"
#include "sync/model.h"


#include "myobject.h"

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);


    tnk::JSonObject json;
    json.setValue("driver", "QSQLITE");
    json.setValue("database", "demo.sqlite");


   auto syncEngine = new tnk::sync::Engine("demo", json.data());
   syncEngine->registerType<MyObject>();

   tnk::sync::Model<MyObject> *model = new tnk::sync::Model<MyObject>( syncEngine);
   model->setSyncToSql(true);
   model->select();


    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("myModel", model);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
