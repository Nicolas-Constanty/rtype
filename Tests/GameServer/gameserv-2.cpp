//
// Created by gaspar_q on 11/30/16.
//

#include <Rtype/Game/Server/RtypeGameServer.hpp>
#include <SaltyEngine/SaltyEngine.hpp>
#include <Rtype/Game/Server/Room.hpp>

void catchbreak(int)
{
    Singleton<SaltyEngine::SaltyEngine>::Instance().Stop();
}


int main(int ac, char **av)
{
    Rtype::Game::Server::Room room;
    uint16_t port;

    signal(SIGINT, &catchbreak);
    if (ac > 1 && (port = static_cast<uint16_t >(atoi(av[1]))) != 0)
        room.Start(port, 4, 42);
    else
        room.Start();
    room.Run();
    return 0;
}