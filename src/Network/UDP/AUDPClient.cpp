//
// Created by gaspar_q on 11/25/16.
//

#include <Network/UDP/AUDPClient.hpp>

/**
 * @brief Copy constructor
 * @param ref The reference to copy
 */
Network::UDP::AUDPClient::AUDPClient(const Network::UDP::AUDPClient &ref) :
        AUDPConnection(ref),
        buff(ref.buff),
        model(nullptr),
        server(Network::Socket::UDP)
{

}

/**
 * @brief Basic destructor
 */
Network::UDP::AUDPClient::~AUDPClient()
{

}

/**
 * @brief Callback called when <select> function say that there is data to read on socket
 * @return True if everything is fine, false either
 */
void Network::UDP::AUDPClient::OnAllowedToRead()
{
    Network::Socket::ISockStream    *stream = dynamic_cast<Network::Socket::ISockStream *>(&model->giveSocket());

    if (stream)
    {
        int ret = sock.ReceiveFrom(buff, *stream);

        if (ret > 0)
        {
            OnDataReceived(static_cast<unsigned int>(ret));
            return ;
        }
    }
}

/**
 * @brief Constant getter for the internal buffer
 * @return The internal buffer
 */
const Network::Core::NetBuffer &Network::UDP::AUDPClient::getBuffer() const
{
    return buff;
}

/**
 * @brief Returns a reference on the internal buffer
 * @return A reference on the internal buffer
 */
Network::Core::NetBuffer &Network::UDP::AUDPClient::giveBuffer()
{
    return buff;
}

/**
 * @brief Setter for the internal buffer
 * @param buff The reference to set internally
 */
void Network::UDP::AUDPClient::setBuffer(const Network::Core::NetBuffer &buff)
{
    this->buff = buff;
}

/**
 * @brief Callback called when <select> detects that the file descriptor is allowed to read
 * @return True if everything went fine, false either
 */
void Network::UDP::AUDPClient::OnAllowedToWrite()
{
    while (!toWrite.empty())
    {
        int ret = sock.SendTo(toWrite.front(), server);

        if (ret < 0)
            return ;
        OnDataSent(static_cast<unsigned int>(ret));
    }
}

/**
 * @brief Connects the socket to the server
 * @param ip The ip of the server
 * @param port The server port
 */
void Network::UDP::AUDPClient::Connect(std::string const &ip, const uint16_t port)
{
    server.Talk(ip, port);
}
