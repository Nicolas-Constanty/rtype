//
// Created by gaspar_q on 11/25/16.
//

#include <Network/Core/NativeSocketIOOperationDispatcher.hpp>
#include "baseudp.hpp"

int main()
{
#ifdef _WIN32
    Network::Socket::WinSocket::Start();
#endif
    Network::Core::NativeSocketIOOperationDispatcher    dispatcher;
    BasicUDPServ    serv(dispatcher);

    dispatcher.setTimeout({1, 0});
    dispatcher.Watch(serv);
    dispatcher.Run();
#ifdef _WIN32
    Network::Socket::WinSocket::Stop();
#endif
    return 0;
}