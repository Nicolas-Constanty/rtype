//
// Created by victor on 05/12/16.
//
//
//#include <ServerGame/CreateRoomGameServer/RtypeGameClient.hpp>
#include "ServerGame/CreateRoomGameServer/ClientGameRooms.hpp"

int main() {
//    unsigned short port = Network::Socket::OSSocket::GetAvailablePort();
//    std::cout << port << std::endl;

    Network::Core::NativeSocketIOOperationDispatcher    dispatcher;
    ClientGameRooms client(dispatcher, "167.56.231.233", 40);

    client.Connect("127.0.0.1", 4242);
    dispatcher.setTimeout((const struct timeval){0, 0});
    dispatcher.Watch(client, Network::Core::NativeSocketIOOperationDispatcher::READ);

    while (12) {
        dispatcher.Poll();
        usleep(3000);
    }

//    ThreadPool<StdThread>  threadPool;
//    Lobby       lobby;
//
//    threadPool.AddThread(std::bind(&Lobby::test, lobby));
//    threadPool.AddThread(std::bind(&Lobby::test, lobby));
//    threadPool.AddThread(std::bind(&Lobby::test, lobby));
//    threadPool.AddThread(std::bind(&Lobby::test, lobby));
//    threadPool.AddThread(std::bind(&Lobby::test, lobby));
//    threadPool.JoinThreads();
    return 0;
}