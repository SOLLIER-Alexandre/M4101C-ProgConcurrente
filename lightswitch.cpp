#include "lightswitch.h"

lightswitch::lightswitch(std::shared_ptr<std::mutex> mutex)
    : m_counter(0)
    , m_mutex(mutex)
{
}

void lightswitch::lock()
{
    std::lock_guard<std::mutex> lockGuard(m_lightswitchMutex);

    if (++m_counter == 1)
    {
        m_mutex->lock();
    }
}

void lightswitch::unlock()
{
    std::lock_guard<std::mutex> lockGuard(m_lightswitchMutex);

    if (--m_counter == 0)
    {
        m_mutex->unlock();
    }
}
