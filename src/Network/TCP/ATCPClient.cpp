//
// Created by gaspar on 24/11/2016.
//

#include "Network/TCP/ATCPClient.hpp"

/**
 * @brief Basic constructor
 */
Network::TCP::ATCPClient::ATCPClient() :
    Network::TCP::ATCPConnection()
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
bool Network::TCP::ATCPClient::OnAllowedToRead()
{
    int len = sock.Receive(buff);

    if (len > 0)
    {
        OnDataReceived(static_cast<unsigned int>(len));
        return true;
    }
    return false;
}
