//
// Created by gaspar_q on 12/8/16.
//

#include <Common/Flags.hpp>
#include <Rtype/Game/Server/Room.hpp>
#include "SaltyEngine/SFML.hpp"
#if _WIN32
#include "Network/Socket/WinSocket.hpp"
#endif

int main(int ac, char **av)
{
    Flags   flags;
    uint16_t port;
    size_t max;
    uint32_t secret;
    uint16_t level;
    bool help;
    Rtype::Game::Server::Room   room;

    flags.Var(port, 'p', "port", uint16_t(4242), "The port on which the room server will be binded", "Room port");
    flags.Var(max, 'm', "max", size_t(2), "The maximum amount of players that are allowed to join the room server", "Maximum amount of players");
    flags.Var(secret, 's', "secret", uint32_t(0), "The secret password of the room", "Secret password");
    flags.Var(level, 'l', "level", uint16_t(2), "The ID of the level to load", "Level id");

    flags.Bool(help, 'h', "help", "Show this help message", "Help");

    if (!flags.Parse(ac, av))
        return 1;
    else if (help)
    {
        flags.PrintHelp(av[0]);
        return 1;
    }
#if _WIN32
	Network::Socket::WinSocket::Start();
#endif
    try
    {
        //SaltyEngine::SFML::AssetManager::Instance().LoadScene("scene" + level);
       // SaltyEngine::SFML::AssetManager::Instance().LoadAssets();
        room.Start(port, max, secret, level);
    }
    catch (std::runtime_error const &err)
    {
        std::cerr << "Fail to start room: " << err.what() << std::endl;
        return 1;
    }
    room.Run();
#if _WIN32
	Network::Socket::WinSocket::Stop();
#endif
    return 0;
}