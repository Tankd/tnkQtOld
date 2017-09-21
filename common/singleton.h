#ifndef SINGLETON_H
#define SINGLETON_H


// http://www.daniweb.com/software-development/cpp/threads/251676/singleton-template-class-magic

#include <iostream>

#define SINGLETON( className)  friend class tnk::Singleton<className>;

namespace tnk {
template <typename T> class Singleton
{
private:
    Singleton(const Singleton<T>&){};

protected:
    static T* _instance;
    Singleton() {}

public:

    static T* self()
    {
        if(_instance == NULL)
            _instance = new T();
        return _instance;
    }
};
template <typename T> T* Singleton<T>::_instance;

}

#endif //MYSINGLETON_H

