//
// Created by gaspar on 21/11/2016.
//

#ifdef _WIN32
#include <Network/Socket/WinSocket.hpp>

/**
 * @brief Function that will initialize Windows sockets
 */
void Network::Socket::WinSocket::Start()
{
    WSADATA  tofill;

    if (WSAStartup(MAKEWORD(2, 2), &tofill) != 0)
        throw SocketException("Start up fail");
}

/**
 * @brief Function that will stop windows sockets
 */
void Network::Socket::WinSocket::Stop()
{
    WSACleanup();
}

/**
 * @brief Basic constructor of Windows socket
 * @param protocol The communication protocol that will use the socket
 * @param domain The domain of the socket (ipv4/ipv6)
 * @param option A few more options to pass on creation
 */
Network::Socket::WinSocket::WinSocket(const Protocol &protocol, const sa_family_t domain, int option) :
    Network::Socket::ASocket(protocol, domain, option)
{

}

/**
 * @brief Basic destructor that does nothing
 */
Network::Socket::WinSocket::~WinSocket()
{

}

/**
 * @brief Receive function and store bytes received into a buffer
 * @param buff The buffer which will contains data received
 * @return The number of bytes received
 */
int Network::Socket::WinSocket::Receive(Network::Core::NetBuffer &buff)
{
    int ret = recv(fd, buff.buff<char>(), buff.getAvailableSpace(), 0);

    buff.setLength(static_cast<size_t>(ret));
    return ret;
}

/**
 * @brief Function that will send data through the socket
 * @param buff
 * @return
 */
int Network::Socket::WinSocket::Send(Network::Core::NetBuffer const &buff) const
{
    return send(fd, buff.buff<char>(), buff.getLength(), 0);
}

int Network::Socket::WinSocket::ReceiveFrom(Network::Core::NetBuffer &buff, Network::Socket::ISockStream &sender)
{
    Network::Socket::WinSocket *snd = dynamic_cast<Network::Socket::WinSocket *>(&sender);

    if (snd)
    {
        socklen_t len = sizeof(snd->sockaddr);

        int ret = recvfrom(fd, buff.buff<char>(), buff.getAvailableSpace(), 0, (struct sockaddr *)&snd->sockaddr, &len);

        buff.setLength(static_cast<size_t>(ret));

        return ret;
    }
    return 0;
}

int Network::Socket::WinSocket::SendTo(Network::Core::NetBuffer &buff, Network::Socket::ISockStream const &receiver)
{
    Network::Socket::WinSocket const *rcvr = dynamic_cast<Network::Socket::WinSocket const *>(&receiver);

    if (rcvr)
    {
        return sendto(fd, buff.buff<char>(), buff.getLength(), 0, (struct sockaddr *)&rcvr->sockaddr, sizeof(rcvr->sockaddr));
    }
    return 0;
}

void Network::Socket::WinSocket::Open() throw(SocketException)
{
    fd = socket(domain, protocol.type, protocol.proto);
    if (fd == INVALID_SOCKET)
        throw Network::Socket::SocketException(strerror(errno));
}

void Network::Socket::WinSocket::Close()
{
    closesocket(fd);
    fd = Network::Socket::DEFAULT;
}
#endif