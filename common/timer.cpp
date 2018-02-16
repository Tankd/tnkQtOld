#include "timer.h"
#include <QDebug>
namespace tnk {
Timer::Timer()
{

}

void Timer::displayElapsed(const QString &text)
{
    qDebug() << "timer" << text << this->elapsed() << "ms";
}

}
