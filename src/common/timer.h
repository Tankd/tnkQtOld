#ifndef TIMER_H
#define TIMER_H

#include "common_global.h"
#include <QElapsedTimer>
#include "singleton.h"


namespace tnk {
class Q_TNK_COMMON_EXPORT Timer : public QElapsedTimer, public Singleton<Timer>
{    
    SINGLETON(Timer)
public:
    explicit Timer();

    void displayElapsed(const QString& text);


};
}

#endif // TIMER_H
