//
// Created by gaspar_q on 6/6/16.
//

#ifdef __linux__
#include <unistd.h>
#include <Network/Socket/UnixSocket.hpp>

/**
 * \brief Basic socket constructor
 * \param protocol The protocol on which the socket will be create
 * \param domain The domain of the socket <ipv4/ipv6>
 * \param option More options you can pass to socket creation
 */
Network::Socket::UnixSocket::UnixSocket(const Protocol &protocol, const sa_family_t domain, int option) :
        Network::Socket::ASocket(protocol, domain, option)
{

}

/**
 * \brief Socket destructor that does nothing
 */
Network::Socket::UnixSocket::~UnixSocket()
{

}

/**
 * \brief Open function that create socket fd with parameters passed in constructor
 */
void Network::Socket::UnixSocket::Open() throw(SocketException)
{
    fd = socket(domain, protocol.type, protocol.proto);
    if (fd == static_cast<SOCKET>(-1))
        throw Network::Socket::SocketException(strerror(errno));
    if (setsockopt(fd, SOL_SOCKET, (SO_REUSEPORT | SO_REUSEADDR), (char *)&option, sizeof(option)) == -1)
        throw Network::Socket::SocketException(strerror(errno));
}

/**
 * \brief Close the the socket previously created by Open
 */
void Network::Socket::UnixSocket::Close()
{
    if (fd > 2)
        close(fd);
    fd = Network::Socket::DEFAULT;
}

/**
 * \brief Function that will receive data and put what it receives into <data> parameter. Basic <recv> call
 * \param data The buffer which will contains received data
 * \param length The maximum length of data to receive
 * \return The number of bytes that has been received
 */
int Network::Socket::UnixSocket::Receive(Network::Core::NetBuffer &buff)
{
    int ret = static_cast<int>(recv(fd, buff.buff(), buff.getAvailableSpace(), MSG_NOSIGNAL));

    buff.addLength(static_cast<size_t>(ret));
    return ret;
}

/**
 * \brief Function that will send data contained into <data> parameter. Basic <send> call
 * \param data The buffer which contains data to send
 * \param length The length of data to send
 * \return The length of data that was really send
 */
int Network::Socket::UnixSocket::Send(Network::Core::NetBuffer const &buff) const
{
    return static_cast<int>(send(fd, buff.buff(), buff.getLength(), MSG_NOSIGNAL));
}

/**
 * \brief Function that will receive data and tells over <sender.sockaddr> argument which client sent us data
 * \param data The buffer that will contain data
 * \param length The maximum amount of data to receive
 * \param sender A reference on Socket which in which <sockaddr> attribute will be modified in order to identify sender ip
 * \return The amount of data received
 */
int Network::Socket::UnixSocket::ReceiveFrom(Network::Core::NetBuffer &buff, ISockStream &sender)
{
    Network::Socket::UnixSocket *snd = dynamic_cast<Network::Socket::UnixSocket *>(&sender);

    if (snd)
    {
        socklen_t len = sizeof(snd->sockaddr);
        int ret = static_cast<int>(recvfrom(fd, buff.buff(), buff.getAvailableSpace(), MSG_NOSIGNAL, (struct sockaddr *)&snd->sockaddr, &len));

        buff.addLength(static_cast<size_t >(ret));
        return ret;
    }
    return 0;
}

/**
 * \brief Function that will send data to a specific receiver over <receiver.sockaddr> argument
 * \param data The buffer that contains data to send
 * \param length The length of data to send
 * \param receiver The client to which send data
 * \return The amount of data send
 */
int Network::Socket::UnixSocket::SendTo(Network::Core::NetBuffer &buff, ISockStream const &receiver)
{
    Network::Socket::UnixSocket const *rcvr = dynamic_cast<Network::Socket::UnixSocket const *>(&receiver);

    if (rcvr)
    {
//        std::cout << "Sending data: " << buff << " to: " << *rcvr << std::endl;
        return static_cast<int>(sendto(fd, buff.buff(), buff.getLength(), MSG_NOSIGNAL, (struct sockaddr *)&rcvr->sockaddr, sizeof(rcvr->sockaddr)));
    }
    return 0;
}

unsigned short Network::Socket::UnixSocket::GetAvailablePort() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        throw std::runtime_error("socket failed !");
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 1, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = 0;
    if (bind(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        if (errno == EADDRINUSE) {
            throw std::runtime_error("the port is not available. already to other process");
        } else {
            throw std::runtime_error("could not bind to process");
        }
    }

    socklen_t len = sizeof(serv_addr);
    if (getsockname(sock, (struct sockaddr *)&serv_addr, &len) == -1) {
        throw std::runtime_error("getsockname failed !");
    }

    unsigned short port = ntohs(serv_addr.sin_port);

    if (close(sock) < 0 ) {
        throw std::runtime_error("close has failed !");
    }
    return (port);
}

int Network::Socket::UnixSocket::SendTo(char *arr, size_t towr, const Network::Socket::ISockStream &receiver)
{
    Network::Socket::UnixSocket const *rcvr = dynamic_cast<Network::Socket::UnixSocket const *>(&receiver);

    if (rcvr)
    {
        //        std::cout << "Sending data: " << buff << " to: " << *rcvr << std::endl;
        return static_cast<int>(sendto(fd, arr, towr, MSG_NOSIGNAL, (struct sockaddr *)&rcvr->sockaddr, sizeof(rcvr->sockaddr)));
    }
    return 0;
}

int Network::Socket::UnixSocket::ReceiveFrom(char *arr, size_t n, Network::Socket::ISockStream &sender)
{
    Network::Socket::UnixSocket *snd = dynamic_cast<Network::Socket::UnixSocket *>(&sender);

    if (snd)
    {
        socklen_t len = sizeof(snd->sockaddr);
        int ret = static_cast<int>(recvfrom(fd, arr, n, MSG_NOSIGNAL, (struct sockaddr *)&snd->sockaddr, &len));
        return ret;
    }
    return 0;
}

#endif