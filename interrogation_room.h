#ifndef M4101C_PROJET_INTERROGATION_ROOM_H
#define M4101C_PROJET_INTERROGATION_ROOM_H

#include <atomic>
#include <memory>
#include <vector>
#include <thread>

#include "lightswitch.h"
#include "suspect.h"

class interrogation_room
{

public:
    interrogation_room(unsigned initialSuspectCount, unsigned detectiveCount, unsigned copCount, unsigned disruptorCount);

    void wait_for_culprit();

private:
    std::shared_ptr<std::atomic_bool> m_culpritFound;
    std::vector<std::unique_ptr<std::thread>> m_threads;

    // Room
    std::shared_ptr<std::vector<suspect>> m_suspects;

    std::shared_ptr<std::mutex> m_roomMutex;
    std::shared_ptr<lightswitch> m_roomSwitch;

    // Cops (Inserters)
    std::shared_ptr<std::mutex> m_copInsertionMutex;

}; // class interrogation_room

#endif //M4101C_PROJET_INTERROGATION_ROOM_H
