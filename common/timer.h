#ifndef TIMER_H
#define TIMER_H

#include <QElapsedTimer>
#include "singleton.h"

namespace tnk {
class Timer : public QElapsedTimer, public Singleton<Timer>
{    
    SINGLETON(Timer)
public:
    explicit Timer();

    void displayElapsed(const QString& text);


};
}

#endif // TIMER_H
