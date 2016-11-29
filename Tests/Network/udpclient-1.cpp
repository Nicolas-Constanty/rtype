//
// Created by gaspar_q on 11/28/16.
//

#include <Network/Core/NativeSocketIOOperationDispatcher.hpp>
#include "baseudp.hpp"

int main()
{
    Network::Core::NativeSocketIOOperationDispatcher    dispatcher;
    BasicUDPClient  client(dispatcher);

    
}