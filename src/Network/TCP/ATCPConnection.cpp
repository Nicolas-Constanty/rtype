//
// Created by gaspar on 23/11/2016.
//

#include "Network/TCP/ATCPConnection.hpp"

/**
 * @brief Basic constructor that will call socket constructor with TCP protocol
 */
Network::TCP::ATCPConnection::ATCPConnection(Core::NativeSocketIOOperationDispatcher &dispatcher) :
    BasicConnection(dispatcher),
    sock(Network::Socket::TCP)
{

}

/**
 * @brief Basic copy constructor with the reference to copy. Only copy the socket
 * @param ref The reference to copy
 */
Network::TCP::ATCPConnection::ATCPConnection(const Network::TCP::ATCPConnection &ref) :
    BasicConnection(ref),
    sock(ref.sock)
{

}

/**
 * @brief Basic destructor that does nothing
 */
Network::TCP::ATCPConnection::~ATCPConnection()
{

}

/**
 * @brief Function which will write internal data into the socket
 * @return True if it really send data, false either
 */
void Network::TCP::ATCPConnection::OnAllowedToWrite()
{
    unsigned int sent = 0;

    while (!toWrite.empty())
    {
        std::cout << "Sending data: " << toWrite.front() << std::endl;
        int len = sock.Send(toWrite.front());
        if (len > 0)
            sent += len;
        toWrite.pop();
    }
    if (sent > 0)
        OnDataSent(sent);
}

/**
 * @brief Allow user to get a reference on the internal socket handled
 * @return A reference on the internal socket
 */
Network::Socket::ISocket &Network::TCP::ATCPConnection::giveSocket()
{
    return sock;
}

/**
 * @brief Constant getter on the internal socket
 * @return A constant reference on the internal socket
 */
const Network::Socket::ISocket &Network::TCP::ATCPConnection::getSocket() const
{
    return sock;
}
