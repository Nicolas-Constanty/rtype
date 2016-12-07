//
// Created by gaspar_q on 11/24/16.
//

#include <Network/Core/NativeSocketIOOperationDispatcher.hpp>
#include "ClientRoomConnectionToServerRoom/basetcp.hpp"

int main()
{
#ifdef _WIN32
    Network::Socket::WinSocket::Start();
#endif
    Network::Core::NativeSocketIOOperationDispatcher    dispatcher((struct timeval){5, 0});
    BasicTCPServ    server(dispatcher, 4242);

    dispatcher.Watch(server, Network::Core::NativeSocketIOOperationDispatcher::WatchMode::READ);
    dispatcher.Run();
#ifdef _WIN32
    Network::Socket::WinSocket::Stop();
#endif
    return 0;
}