#include <thread>
#include <vector>
#include <iostream>

#include "cop.h"
#include "utils.h"

unsigned cop::s_copCount = 0;

cop::cop(std::shared_ptr<std::vector<suspect>> suspects, std::shared_ptr<std::mutex> copInsertionMutex,
         std::shared_ptr<lightswitch> roomSwitch, std::shared_ptr<std::atomic_bool> culpritFound)
    : m_suspects(suspects)
    , m_copInsertionMutex(copInsertionMutex)
    , m_roomSwitch(roomSwitch)
    , m_culpritFound(culpritFound)
{
    m_id = ++s_copCount;
}

void cop::operator()()
{
    while (!(*m_culpritFound))
    {
        m_roomSwitch->lock();

        {
            std::lock_guard<std::mutex> lockGuard(*m_copInsertionMutex);

            suspect addedSuspect = {
                    static_cast<unsigned int>(rand()) % 9000 + 1000,
                    rand() / (float)RAND_MAX <= 0.05
            };

            m_suspects->push_back(addedSuspect);

            {
                std::lock_guard<std::mutex> coutLock(g_coutMutex);
                std::cout << "[+] Cop #" << m_id << " has added the suspect #" << addedSuspect.m_id;
                if (addedSuspect.m_culprit)
                {
                    std::cout << " // CULPRIT";
                }

                std::cout << " [" << m_suspects->size() << "]" << std::endl;
            }

        }

        m_roomSwitch->unlock();

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
