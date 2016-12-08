//
// Created by gaspar_q on 12/8/16.
//

#include <Common/Flags.hpp>
#include <Rtype/Game/Server/Room.hpp>

int main(int ac, char **av)
{
    Flags   flags;
    uint16_t port;
    size_t max;
    uint32_t secret;
    uint16_t level;
    bool help;
    Rtype::Game::Server::Room   room;

    flags.Var(port, 'p', "port", static_cast<uint16_t >(4242), "The port on which the room server will be binded", "Room port");
    flags.Var(max, 'm', "max", static_cast<size_t >(4), "The maximum amount of players that are allowed to join the room server", "Maximum amount of players");
    flags.Var(secret, 's', "secret", static_cast<uint32_t >(0), "The secret password of the room", "Secret password");
    flags.Var(level, 'l', "level", static_cast<uint16_t >(0), "The ID of the level to load", "Level id");

    flags.Bool(help, 'h', "help", "Show this help message", "Help");

    if (!flags.Parse(ac, av))
        return 1;
    else if (help)
    {
        flags.PrintHelp(av[0]);
        return 1;
    }
    try
    {
        room.Start(port, max, secret, level);
    }
    catch (std::runtime_error const &err)
    {
        std::cerr << "Fail to start room: " << err.what() << std::endl;
        return 1;
    }
    room.Run();
    return 0;
}