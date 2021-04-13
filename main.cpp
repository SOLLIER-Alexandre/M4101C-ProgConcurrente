#include <iostream>
#include <string>

#include "interrogation_room.h"

int main(int argc, char* argv[])
{
    if (argc < 5)
    {
        std::cout << "Usage: " << argv[0] << " <initialSuspectCount> <detectiveCount> <copCount> <disruptorCount>" << std::endl;
        return -1;
    }

    srand(time(nullptr));

    interrogation_room interrogationRoom(std::stoul(argv[1]), std::stoul(argv[2]),
                                         std::stoul(argv[3]), std::stoul(argv[4]));

    interrogationRoom.wait_for_culprit();

    return 0;
}