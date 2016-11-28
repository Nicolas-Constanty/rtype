//
// Created by gaspar on 24/11/2016.
//

#include "Network/TCP/ATCPClient.hpp"

/**
 * @brief Basic constructor
 */
Network::TCP::ATCPClient::ATCPClient(Network::Core::NativeSocketIOOperationDispatcher &dispatcher) :
    Network::TCP::ATCPConnection(dispatcher)
{

}

/**
 * @brief Copy constructor
 * @param ref The reference to copy
 */
Network::TCP::ATCPClient::ATCPClient(const Network::TCP::ATCPClient &ref) :
    Network::TCP::ATCPConnection(ref)
{

}

/**
 * @brief Basic destructor
 */
Network::TCP::ATCPClient::~ATCPClient()
{

}

/**
 * @brief Callback called when client is allowed to read
 * @return True if socket actually read, false either
 */
void Network::TCP::ATCPClient::OnAllowedToRead()
{
    buff.reset();
    int len = sock.Receive(buff);

    if (len > 0)
    {
        WantReceive();
        OnDataReceived(static_cast<unsigned int>(len));
    }
    else
        Disconnect();
}