//
// Created by victor on 05/12/16.
//
//

#include "Common/Flags.hpp"
#include "ServerGame/CreateRoomGameServer/ClientGameRooms.hpp"

int main(int ac, char **av) {
    size_t          nbrRooms;
    unsigned short port;
    std::string serverRoomIP;
    std::string actualIP;

    bool help;

    Flags flags;

    flags.Var(actualIP, 'i', "actual_ip", std::string("127.0.0.1"), "The server Game ip.", "Server Game");
    flags.Var(serverRoomIP, 'I', "server_room_ip", std::string("127.0.0.1"), "The server room ip", "Server room");
    flags.Var(port, 'p', "port", ushort(4242), "The server room port", "Server room");
    flags.Var(nbrRooms, 'n', "nbr_rooms", size_t(10), "the number of room that the server game can handle", "Server Game");

    flags.Bool(help, 'h', "help", "show this help and exit", "HELP");

    if (!flags.Parse(ac, av)) {
        flags.PrintHelp(av[0]);
        return 1;
    } else if (help) {
        flags.PrintHelp(av[0]);
        return 0;
    }


    Network::Core::NativeSocketIOOperationDispatcher    dispatcher;
    ClientGameRooms client(dispatcher, actualIP, nbrRooms);

    client.Connect(serverRoomIP, port);
    dispatcher.setTimeout((const struct timeval){0, 0});
    dispatcher.Watch(client, Network::Core::NativeSocketIOOperationDispatcher::READ);

    while (12) {
        dispatcher.Poll();
        usleep(3000);
    }
    return 0;
}