#include <iostream>
#include <thread>
#include <vector>

#include "detective.h"
#include "utils.h"

unsigned detective::s_detectiveCount = 0;

detective::detective(std::shared_ptr<std::vector<suspect>> suspects, std::shared_ptr<lightswitch> roomSwitch,
                     std::shared_ptr<std::atomic_bool> culpritFound)
    : m_suspects(suspects)
    , m_roomSwitch(roomSwitch)
    , m_culpritFound(culpritFound)
{
    m_id = ++s_detectiveCount;
}

void detective::operator()()
{
    while (!(*m_culpritFound))
    {
        m_roomSwitch->lock();

        if (!m_suspects->empty())
        {
            const unsigned chosenIndex = rand() % m_suspects->size();
            if ((*m_suspects)[chosenIndex].m_culprit)
            {
                *m_culpritFound = true;

                {
                    std::lock_guard<std::mutex> coutLock(g_coutMutex);
                    std::cout << "Detective #" << m_id
                              << " found a culprit: Suspect #" << (*m_suspects)[chosenIndex].m_id << std::endl;
                }
            }
        }

        m_roomSwitch->unlock();

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
