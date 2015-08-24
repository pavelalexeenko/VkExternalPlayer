#ifndef INSTANCEFACTORY_H
#define INSTANCEFACTORY_H

template< class T >
class InstanceFactory
{
    InstanceFactory();
    InstanceFactory(const InstanceFactory<T>&);
    InstanceFactory& operator=(const InstanceFactory<T>&);
    ~InstanceFactory();

    static T* instance;

public:
    static T* getInstance()
    {
        if (!instance)
            instance = new T();

        return instance;
    }
};

template <class T> T* InstanceFactory<T>::instance;

#endif // INSTANCEFACTORY_H
