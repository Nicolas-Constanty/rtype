//
// Created by gaspar_q on 11/26/16.
//

#include <Network/Core/BasicConnection.hpp>

/**
 * @brief Basic constructor that initialize the internal dispatcher reference
 * @param dispatcher The reference on the dispatcher to work with
 */
Network::Core::BasicConnection::BasicConnection(Network::Core::NativeSocketIOOperationDispatcher &dispatcher) :
    dispatcher(dispatcher),
    clients(NULL),
    toWrite()
{

}

/**
 * @brief Basic destructor that removes any king of reference on <this> inside the dispatcher
 */
Network::Core::BasicConnection::~BasicConnection()
{
    dispatcher.Remove(this);
}

/**
 * @brief Tells to the dispatcher that we want receive data in <this> socket. Dispatcher will then put the native fd into <select> read fd_set
 */
void Network::Core::BasicConnection::WantReceive()
{
    if (!dispatcher.IsBinded(this, NativeSocketIOOperationDispatcher::READ))
        dispatcher.Watch(this, NativeSocketIOOperationDispatcher::READ);
}

/**
 * @brief Tells to the dispatcher that we want to send data from <this> socket. Dispatcher will then put the native fd into <select> write fd_set
 */
void Network::Core::BasicConnection::WantSend()
{
    if (!dispatcher.IsBinded(this, NativeSocketIOOperationDispatcher::WRITE))
        dispatcher.Watch(this, NativeSocketIOOperationDispatcher::WRITE);
}

/**
 * @brief Allow user to get a reference on the internal dispatcher. Usefull when you want to instantiate a new client.
 * @return A reference on the internal dispatcher
 */
Network::Core::NativeSocketIOOperationDispatcher &Network::Core::BasicConnection::Dispatcher()
{
    return dispatcher;
}

/**
 * @brief Constant getter on the internal dispatcher
 * @return A constant reference on the internal dispatcher
 */
const Network::Core::NativeSocketIOOperationDispatcher &Network::Core::BasicConnection::Dispatcher() const
{
    return dispatcher;
}

/**
 * @brief Allow user to set the internal pointer of <clients>. Usefull for UDP when a client connects/disconnects
 * @param clts The clients pointer to set
 */
void Network::Core::BasicConnection::setClients(Network::Socket::ISockStreamHandlersContainer *clts)
{
    clients = clts;
}

/**
 * @brief Disconnects the cient. Will remove any king of reference from clients and dispatcher and will close the socket.
 */
void Network::Core::BasicConnection::Disconnect()
{
    std::cout << "\x1b[31mClient disconnected\x1b[0m: " << this << std::endl;
    giveSocket().Close();
    dispatcher.Remove(this);
    if (clients)
        clients->Remove(this);
}

/**
 * @brief Allow user to get a reference on the internal message queue. Usefull for UDP when the server needs to send clients messages
 * @return A reference on internal messages queue
 */
std::queue<Network::Core::NetBuffer> &Network::Core::BasicConnection::Messages()
{
    return toWrite;
}