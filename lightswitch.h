#ifndef M4101C_PROJET_LIGHTSWITCH_H
#define M4101C_PROJET_LIGHTSWITCH_H

#include <mutex>

class lightswitch
{

public:
    explicit lightswitch(std::shared_ptr<std::mutex> mutex);

    void lock();
    void unlock();

private:
    unsigned m_counter;
    std::mutex m_lightswitchMutex;

    std::shared_ptr<std::mutex> const m_mutex;

}; // class lightswitch

#endif //M4101C_PROJET_LIGHTSWITCH_H
