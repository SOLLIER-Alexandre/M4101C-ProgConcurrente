#ifndef M4101C_PROJET_DETECTIVE_H
#define M4101C_PROJET_DETECTIVE_H

#include "lightswitch.h"
#include "suspect.h"

class detective
{

public:
    detective(std::shared_ptr<std::vector<suspect>> suspects, std::shared_ptr<lightswitch> roomSwitch,
              std::shared_ptr<std::atomic_bool> culpritFound);

    void operator()();

private:
    static unsigned s_detectiveCount;
    unsigned m_id;

    std::shared_ptr<std::vector<suspect>> m_suspects;
    std::shared_ptr<lightswitch> m_roomSwitch;

    std::shared_ptr<std::atomic_bool> m_culpritFound;

}; // class detective

#endif //M4101C_PROJET_DETECTIVE_H
