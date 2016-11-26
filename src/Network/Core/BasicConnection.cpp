//
// Created by gaspar_q on 11/26/16.
//

#include <Network/Core/BasicConnection.hpp>

Network::Core::BasicConnection::BasicConnection(Network::Core::NativeSocketIOOperationDispatcher &dispatcher) :
    dispatcher(dispatcher)
{

}

Network::Core::BasicConnection::~BasicConnection()
{
    dispatcher.Remove(this);
}

void Network::Core::BasicConnection::WantReceive()
{
    if (!dispatcher.IsBinded(this, NativeSocketIOOperationDispatcher::READ))
        dispatcher.Watch(this, NativeSocketIOOperationDispatcher::READ);
}

void Network::Core::BasicConnection::WantSend()
{
    if (!dispatcher.IsBinded(this, NativeSocketIOOperationDispatcher::WRITE))
        dispatcher.Watch(this, NativeSocketIOOperationDispatcher::WRITE);
}

Network::Core::NativeSocketIOOperationDispatcher &Network::Core::BasicConnection::Dispatcher()
{
    return dispatcher;
}

void Network::Core::BasicConnection::setClients(Network::Socket::ISockStreamsContainer *clts)
{
    clients = clts;
}

void Network::Core::BasicConnection::Disconnect()
{
    std::cout << "\x1b[31mClient disconnected\x1b[0m: " << this << std::endl;
    giveSocket().Close();
    if (clients)
        clients->Remove(this);
    else
        delete(this);
}

std::queue<Network::Core::NetBuffer> &Network::Core::BasicConnection::Messages()
{
    return toWrite;
}

const Network::Core::NativeSocketIOOperationDispatcher &Network::Core::BasicConnection::Dispatcher() const
{
    return dispatcher;
}
