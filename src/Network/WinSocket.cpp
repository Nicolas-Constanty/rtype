//
// Created by gaspar on 21/11/2016.
//

#ifdef _WIN32
#include "WinSocket.hpp"

void Network::Socket::WinSocket::Start()
{
    WSADATA  tofill;

    if (WSAStartup(MAKEWORD(2, 2), &tofill) != 0)
        throw SocketException("Start up fail");
}

void Network::Socket::WinSocket::Stop()
{
    WSACleanup();
}

Network::Socket::WinSocket::WinSocket(const Protocol &protocol, const sa_family_t domain, int option) :
    Network::Socket::ASocket(protocol, domain, option)
{

}

Network::Socket::WinSocket::~WinSocket()
{

}

int Network::Socket::WinSocket::Receive(Network::Core::NetBuffer &buff)
{
    return recv(fd, static_cast<char *>(buff.buff()), Core::NetBuffer::size, MSG_NOSIGNAL);
}

int Network::Socket::WinSocket::Send(Network::Core::NetBuffer &buff)
{
    return send(fd, static_cast<char *>(buff.buff()), Core::NetBuffer::size, MSG_NOSIGNAL);
}

int Network::Socket::WinSocket::ReceiveFrom(Network::Core::NetBuffer &buff, Network::Socket::ISockStream &sender)
{
    Network::Socket::WinSocket *snd = dynamic_cast<Network::Socket::WinSocket *>(&sender);

    if (snd)
    {
        socklen_t len = sizeof(snd->sockaddr);

        return recvfrom(fd, static_cast<char *>(buff.buff()), Core::NetBuffer::size, MSG_NOSIGNAL, (struct sockaddr *)&snd->sockaddr, &len);
    }
    return 0;
}

int Network::Socket::WinSocket::SendTo(Network::Core::NetBuffer &buff, Network::Socket::ISockStream const &receiver)
{
    Network::Socket::WinSocket const *rcvr = dynamic_cast<Network::Socket::WinSocket const *>(&receiver);

    if (rcvr)
    {
        return sendto(fd, static_cast<char *>(buff.buff()), Core::NetBuffer::size, MSG_NOSIGNAL, (struct sockaddr *)&rcvr->sockaddr, sizeof(rcvr->sockaddr));
    }
    return 0;
}

void Network::Socket::WinSocket::Open()
{
    fd = socket(domain, protocol.type, protocol.proto);
    if (fd == INVALID_SOCKET)
        throw Network::Socket::SocketException(strerror(errno));
}

void Network::Socket::WinSocket::Close()
{
    closesocket(fd);
    fd = -1;
}
#endif