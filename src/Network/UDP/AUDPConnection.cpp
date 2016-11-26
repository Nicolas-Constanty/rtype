//
// Created by gaspar_q on 11/25/16.
//

#include <Network/UDP/AUDPConnection.hpp>

/**
 * @brief Basic constructor
 */
Network::UDP::AUDPConnection::AUDPConnection(Core::NativeSocketIOOperationDispatcher &dispatcher) :
    BasicConnection(dispatcher),
    sock(Socket::UDP)
{

}

/**
 * @brief Basic copy constructor
 * @param ref The reference to copy
 */
Network::UDP::AUDPConnection::AUDPConnection(const Network::UDP::AUDPConnection &ref) :
    BasicConnection(ref),
    sock(ref.sock)
{

}

/**
 * @brief Basic destructor
 */
Network::UDP::AUDPConnection::~AUDPConnection()
{

}

/**
 * @brief Allow user to get the internal socket reference
 * @return A reference on the internal socket
 */
Network::Socket::ISocket &Network::UDP::AUDPConnection::giveSocket()
{
    return sock;
}

/**
 * @brief Allow user to get a constant reference on the internal socket
 * @return A constant reference on the internal socket
 */
const Network::Socket::ISocket &Network::UDP::AUDPConnection::getSocket() const
{
    return sock;
}