//
// Created by victor on 29/11/16.
//

#include <Network/Core/NativeSocketIOOperationDispatcher.hpp>
#include "ServerRoom/DefaultTCPConnection.hpp"
#include "ServerRoom/RtypeRoomServer.hpp"

int main()
{
#ifdef _WIN32
    Network::Socket::WinSocket::Start();
#endif
	struct timeval timeout = { 5, 0 };
    Network::Core::NativeSocketIOOperationDispatcher    dispatcher(timeout);
    RtypeRoomServer    server(dispatcher);

    dispatcher.Watch(server, Network::Core::NativeSocketIOOperationDispatcher::WatchMode::READ);
    dispatcher.Run();
#ifdef _WIN32
    Network::Socket::WinSocket::Stop();
#endif
    return 0;
}