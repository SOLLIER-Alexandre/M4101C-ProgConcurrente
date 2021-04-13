#ifndef M4101C_PROJET_COP_H
#define M4101C_PROJET_COP_H

#include <mutex>

#include "lightswitch.h"
#include "suspect.h"

class cop
{

public:
    cop(std::shared_ptr<std::vector<suspect>> suspects, std::shared_ptr<std::mutex> copInsertionMutex,
        std::shared_ptr<lightswitch> roomSwitch, std::shared_ptr<std::atomic_bool> culpritFound);

    void operator()();

private:
    static unsigned s_copCount;
    unsigned m_id;

    std::shared_ptr<std::vector<suspect>> m_suspects;
    std::shared_ptr<std::mutex> m_copInsertionMutex;
    std::shared_ptr<lightswitch> m_roomSwitch;

    std::shared_ptr<std::atomic_bool> m_culpritFound;

}; // class cop

#endif //M4101C_PROJET_COP_H
