//
// Created by victor on 05/12/16.
//
//

#include "Common/Flags.hpp"
#include "ServerGame/CreateRoomGameServer/ClientGameRooms.hpp"

int main(int ac, char **av) {

    size_t          nbrRooms;
    uint16_t port;
    std::string serverRoomIP;
    std::string actualIP;

    bool help;

    Flags flags;

    flags.Var(actualIP, 'i', "actual_ip", std::string("127.0.0.1"), "The server Game ip.", "Server Game");
    flags.Var(serverRoomIP, 'I', "server_room_ip", std::string("127.0.0.1"), "The server room ip", "Server room");
    flags.Var(port, 'p', "port", uint16_t(4242), "The server room port", "Server room");
    flags.Var(nbrRooms, 'n', "nbr_rooms", size_t(10), "the number of room that the server game can handle", "Server Game");

    flags.Bool(help, 'h', "help", "show this help and exit", "HELP");

    if (!flags.Parse(ac, av)) {
        flags.PrintHelp(av[0]);
        return 1;
    } else if (help) {
        flags.PrintHelp(av[0]);
        return 0;
    }

#if _WIN32
	Network::Socket::WinSocket::Start();
#endif

    Network::Core::NativeSocketIOOperationDispatcher    dispatcher;
	std::unique_ptr<ClientGameRooms> client;

	try
	{
		client.reset(new ClientGameRooms(dispatcher, actualIP, nbrRooms));
		client->Connect(serverRoomIP, port);
	}
	catch (Network::Socket::SocketException const &err)
	{
		std::cerr << "Connection: " << err.what() << std::endl;
		return (1);
	}

	const struct timeval timeout = { 0, 0 };

    dispatcher.setTimeout(timeout);
    dispatcher.Watch(*client, Network::Core::NativeSocketIOOperationDispatcher::READ);

    while (12) {
        dispatcher.Poll();
#ifdef _WIN32
		Sleep(5000);
#else
		usleep(5000);
#endif // _WIN32
    }

#ifdef _WIN32
	Network::Socket::WinSocket::Stop();
#endif // _WIN32

    return 0;
}