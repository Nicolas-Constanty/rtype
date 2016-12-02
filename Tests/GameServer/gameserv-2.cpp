//
// Created by gaspar_q on 11/30/16.
//

#include <ServerGame/Room.hpp>

int main(int ac, char **av)
{
    Rtype::Room room;
    uint16_t port;

    if (ac > 1 && (port = static_cast<uint16_t >(atoi(av[1]))) != 0)
        room.Start(port);
    else
        room.Start();
    room.Run();
    room.Stop();
    return 0;
}