//
// Created by gaspar_q on 11/28/16.
//

#include <Network/Core/NativeSocketIOOperationDispatcher.hpp>
#include "baseudp.hpp"

int main()
{
    Network::Core::NativeSocketIOOperationDispatcher    dispatcher;
    BasicUDPClient  client(dispatcher);

    std::cout << "Connecting socket" << std::endl;
    client.Connect("127.0.0.1", 4242);
    client.SendData("La connection\n");
    dispatcher.Watch(client, Network::Core::NativeSocketIOOperationDispatcher::READ);
    std::cout << "Client watched in read mode" << std::endl;
    dispatcher.Run();
    std::cout << "Leaving" << std::endl;
    return 0;
}