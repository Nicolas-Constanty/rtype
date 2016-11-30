//
// Created by victor on 30/11/16.
//

#include <Network/Core/NativeSocketIOOperationDispatcher.hpp>
#include "serverGameClient.hpp"

int main()
{
    Network::Core::NativeSocketIOOperationDispatcher    dispatcher;
    BasicClient client(dispatcher);

    client.Connect("127.0.0.1", 4242);
    dispatcher.Watch(client, Network::Core::NativeSocketIOOperationDispatcher::READ);
    dispatcher.Run();
    return 0;
}