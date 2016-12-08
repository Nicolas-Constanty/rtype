//
// Created by gaspar_q on 12/1/16.
//

#include <SaltyEngine/SaltyEngine.hpp>
#include <Rtype/Game/Client/RtypeClientGameClient.hpp>

int main()
{
    Network::Core::NativeSocketIOOperationDispatcher    dispatcher;
    Rtype::Game::Client::RtypeClientGameClient          client(dispatcher);

    client.Connect("10.10.253.107", 4242);
    dispatcher.Watch(client, Network::Core::NativeSocketIOOperationDispatcher::READ);
    dispatcher.Run();
    return 0;
}