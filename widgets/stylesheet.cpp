#include "stylesheet.h"

#include "common/utils.h"

#include <QDebug>
#include <QApplication>


namespace tnk {
namespace widgets {


void loadShytesheet(const QString &fileName)
{
    QByteArray stylesheet = utils::fromFile( fileName);
    if( stylesheet.isEmpty())
    {
        qDebug() << "tnk::widgets::loadShytesheet fail :"<< fileName << "not found !";
        return;
    }

    qApp->setStyleSheet(stylesheet);

}


}
}
