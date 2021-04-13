#ifndef M4101C_PROJET_DISRUPTOR_H
#define M4101C_PROJET_DISRUPTOR_H

#include <atomic>
#include <memory>
#include <mutex>
#include <vector>

#include "suspect.h"

class disruptor
{

public:
    disruptor(std::shared_ptr<std::vector<suspect>> suspects, std::shared_ptr<std::mutex> roomMutex,
              std::shared_ptr<std::atomic_bool> culpritFound);

    void operator()();

private:
    static unsigned s_disruptorCount;
    unsigned m_id;

    std::shared_ptr<std::vector<suspect>> m_suspects;
    std::shared_ptr<std::mutex> m_roomMutex;

    std::shared_ptr<std::atomic_bool> m_culpritFound;

};

#endif //M4101C_PROJET_DISRUPTOR_H
