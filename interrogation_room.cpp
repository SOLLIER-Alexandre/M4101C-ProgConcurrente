#include "interrogation_room.h"

#include "cop.h"
#include "detective.h"
#include "disruptor.h"

interrogation_room::interrogation_room(unsigned initialSuspectCount, unsigned detectiveCount, unsigned copCount, unsigned disruptorCount)
    : m_culpritFound(new std::atomic_bool(false))
    , m_suspects(new std::vector<suspect>())
    , m_roomMutex(new std::mutex())
    , m_roomSwitch(new lightswitch(m_roomMutex))
    , m_copInsertionMutex(new std::mutex())
{
    // Create the initial pool of suspects
    for (unsigned i = 0; i < initialSuspectCount; ++i)
    {
        m_suspects->push_back({
                                      static_cast<unsigned int>(rand()) % 9000 + 1000,
                                      false
                              });
    }

    // Instantiate detective threads
    for (unsigned i = 0; i < detectiveCount; ++i)
    {
        m_threads.emplace_back(new std::thread(detective(m_suspects, m_roomSwitch, m_culpritFound)));
    }

    // Instantiate cop threads
    for (unsigned i = 0; i < copCount; ++i)
    {
        m_threads.emplace_back(new std::thread(cop(m_suspects, m_copInsertionMutex, m_roomSwitch, m_culpritFound)));
    }

    // Instantiate disruptor threads
    for (unsigned i = 0; i < disruptorCount; ++i)
    {
        m_threads.emplace_back(new std::thread(disruptor(m_suspects, m_roomMutex, m_culpritFound)));
    }
}

void interrogation_room::wait_for_culprit()
{
    // Join every instantiated thread
    for (const std::unique_ptr<std::thread>& thread: m_threads)
    {
        if (thread->joinable())
        {
            thread->join();
        }
    }
}
