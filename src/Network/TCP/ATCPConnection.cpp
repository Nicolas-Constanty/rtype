//
// Created by gaspar on 23/11/2016.
//

#include "Network/TCP/ATCPConnection.hpp"

/**
 * @brief Basic constructor that will call socket constructor with TCP protocol
 */
Network::TCP::ATCPConnection::ATCPConnection() :
    sock(Network::Socket::TCP)
{

}

/**
 * @brief Basic copy constructor with the reference to copy. Only copy the socket
 * @param ref The reference to copy
 */
Network::TCP::ATCPConnection::ATCPConnection(const Network::TCP::ATCPConnection &ref) :
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
 * @brief Native method that will return the native socket that handle
 * @return The native socket handled
 */
SOCKET Network::TCP::ATCPConnection::Native() const
{
    return sock.Native();
}

/**
 * @brief Function which will write internal data into the socket
 * @return True if it really send data, false either
 */
bool Network::TCP::ATCPConnection::OnAllowedToWrite()
{
    while (!toWrite.empty())
    {
        if (sock.Send(toWrite.front()))
            return false;
        toWrite.pop();
    }
    return true;
}
