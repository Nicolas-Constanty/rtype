//
// Created by victor on 05/12/16.
//

#include <ServerGame/RtypeGameClient.hpp>
#include <Thread/ThreadPool.hpp>
#include "Thread/StdThread.hpp"
#include "ServerGame/CreateRoomGameServer/Lobby.hpp"
#include "ServerGame/CreateRoomGameServer/ClientGameRooms.hpp"


int main() {
//    unsigned short port = Network::Socket::OSSocket::GetAvailablePort();
//    std::cout << port << std::endl;
//
//    Network::Core::NativeSocketIOOperationDispatcher    dispatcher;
//    ClientGameRooms client(dispatcher);
//
//    client.Connect("127.0.0.1", 4242);
//    dispatcher.setTimeout((const struct timeval){0, 0});
//    dispatcher.Watch(client, Network::Core::NativeSocketIOOperationDispatcher::READ);
    ThreadPool<StdThread>  threadPool;
    Lobby       lobby;

    threadPool.AddThread(std::bind(&Lobby::test, lobby));
    threadPool.AddThread(std::bind(&Lobby::test, lobby));
    threadPool.AddThread(std::bind(&Lobby::test, lobby));
    threadPool.AddThread(std::bind(&Lobby::test, lobby));
    threadPool.AddThread(std::bind(&Lobby::test, lobby));
    threadPool.JoinThreads();
    return 0;
}