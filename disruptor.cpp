#include "disruptor.h"
#include <thread>
#include <iostream>
#include <vector>

#include "utils.h"

unsigned disruptor::s_disruptorCount = 0;

disruptor::disruptor(std::shared_ptr<std::vector<suspect>> suspects, std::shared_ptr<std::mutex> roomMutex,
                     std::shared_ptr<std::atomic_bool> culpritFound)
    : m_suspects(suspects)
    , m_roomMutex(roomMutex)
    , m_culpritFound(culpritFound)
{
    m_id = ++s_disruptorCount;
}

void disruptor::operator()()
{
    while (!(*m_culpritFound))
    {
        {
            std::lock_guard<std::mutex> detectiveLock(*m_roomMutex);

            if (!m_suspects->empty())
            {
                const unsigned chosenIndex = rand() % m_suspects->size();
                const suspect removedSuspect = (*m_suspects)[chosenIndex];
                m_suspects->erase(m_suspects->begin() + chosenIndex);

                {
                    std::lock_guard<std::mutex> coutLock(g_coutMutex);
                    std::cout << "[-] Disruptor #" << m_id << " Removed: Suspect #" << removedSuspect.m_id
                              << " [" << m_suspects->size() << "]"
                              << std::endl;
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
