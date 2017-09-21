#ifndef MYCONFIG_H
#define MYCONFIG_H

#include <QCoreApplication>
#include <QSettings>
#include "singleton.h"
#include <QDebug>

namespace tnk {

class Config : public QSettings, public Singleton< Config>
{
    Q_OBJECT

    SINGLETON(Config)
private:
    explicit Config(QObject *parent = 0) : QSettings(QCoreApplication::applicationDirPath()+"/config.ini", QSettings::IniFormat, parent)
    {
    }

signals:

public slots:
};

}


#endif // MYCONFIG_H
