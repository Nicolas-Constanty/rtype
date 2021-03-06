//
// Created by gaspar on 21/11/2016.
//

#include <Network/Socket/ASocket.hpp>

/**
 * \brief Basic ASocket constructor
 * \param protocol The protocol on which the socket will be create
 * \param domain The domain of the socket <ipv4/ipv6>
 * \param option More options you can pass to socket creation
 */
Network::Socket::ASocket::ASocket(const Protocol &protocol, const sa_family_t domain, int option) :
        protocol(protocol),
        domain(domain),
        option(option),
        sockaddr(),
        fd(Network::Socket::DEFAULT)
{

}

/**
 * \brief Copy constructor
 * \param ref The reference to copy
 */
Network::Socket::ASocket::ASocket(ASocket const &ref) :
    Network::Socket::ASocket::ASocket(ref.protocol, ref.domain, ref.option)
{
    sockaddr = ref.sockaddr;
    fd = ref.fd;
}

/**
 * \brief ASocket basic destructor
 */
Network::Socket::ASocket::~ASocket()
{

}

/**
 * \brief Copy operator
 * \param ref Socket to copy
 * \return A reference on this
 */
Network::Socket::ASocket &Network::Socket::ASocket::operator=(ASocket const &ref)
{
    if (ref.protocol != protocol && ref.domain != domain)
        return *this;
    Close();
    sockaddr = ref.sockaddr;
    fd = ref.fd;
    return *this;
}

/**
 * @brief Copy operator for ISockets copy
 * @param ref The reference to copy
 * @return A reference on this
 */
Network::Socket::ISocket &Network::Socket::ASocket::operator=(const Network::Socket::ISocket &ref)
{
    *this = dynamic_cast<ASocket const &>(ref);
    return *this;
}

/**
 * \brief Comparison operator that compare IP adresses and ports
 * \return True if sockets are on same IP/Port
 */
bool Network::Socket::ASocket::operator==(ISocket const &ref) const
{
    ASocket const *sock = dynamic_cast<ASocket const *>(&ref);

    return sock &&
            sockaddr.sin_addr.s_addr == sock->sockaddr.sin_addr.s_addr &&
            sockaddr.sin_family == sock->sockaddr.sin_family &&
            sockaddr.sin_port == sock->sockaddr.sin_port;
}

/**
 * \brief Function that will allow user to get native socket file descriptor
 * \return Native socket file descriptor
 */
SOCKET Network::Socket::ASocket::Native() const
{
    return fd;
}

/**
 * \brief Turn socket into listen (server) mode on a specific port
 * \param port The port on which bind listen socket
 * \param nbc The maximum amount of client we can handle in connection queue
 */
void Network::Socket::ASocket::Listen(const uint16_t port, const int nbc) throw(SocketException)
{
    socklen_t len = sizeof(sockaddr);

    sockaddr.sin_family = domain;
    sockaddr.sin_port = htons(port);
    sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(fd, (const struct sockaddr *)&sockaddr, len) == -1 || (protocol == Network::Socket::TCP && listen(fd, nbc) == -1))
    {
#ifdef _WIN32
		char err[256];
		strerror_s(err, errno);
		throw SocketException(err);
#else
        throw SocketException(strerror(errno));
#endif
    }
        
}

/**
 * \brief Turn socket into talk (client) mode. Connects to a specific ip:port
 * \param ip The ip to which connect the socket
 * \param port The port to which connect the socket
 */
void Network::Socket::ASocket::Talk(const std::string &ip, const uint16_t port) throw(SocketException)
{
    socklen_t len = sizeof(sockaddr);

    std::cout << "Talk" << std::endl;
    memset(&sockaddr, 0, len);
    sockaddr.sin_family = domain;
    sockaddr.sin_port = htons(port);
    if (protocol == Network::Socket::TCP)
    	sockaddr.sin_addr.s_addr = inet_addr(ip.c_str());
#if _WIN32
	std::cout << fd << std::endl;
	if ((protocol == Network::Socket::TCP && connect(fd, (struct sockaddr *)&sockaddr, len) == -1) ||
		(protocol == Network::Socket::UDP && inet_pton(AF_INET, ip.c_str(), &sockaddr.sin_addr) == 0))
	{
		std::cout << WSAGetLastError() << std::endl;
		char err[256];
		strerror_s(err, errno);
		throw SocketException(err);
	}
#else
	if ((protocol == Network::Socket::TCP && connect(fd, (struct sockaddr *)&sockaddr, len) == -1) ||
		(protocol == Network::Socket::UDP && inet_aton(ip.c_str(), &sockaddr.sin_addr) == 0))
		throw SocketException(strerror(errno));
#endif // _WIN32
    //std::cout << *this << std::endl;
}

/**
 * \brief Function that allows user to accept incomming connection on its socket
 * \param sock A reference on the new client to create
 */
void Network::Socket::ASocket::Accept(ISocket &sock)
{
    ASocket *sck = dynamic_cast<Socket::ASocket *>(&sock);

    if (sck)
    {
        socklen_t len = sizeof(sck->sockaddr);

        if ((sck->fd = accept(fd, (struct sockaddr *)&sck->sockaddr, &len)) == -1 ||
                getsockname(sck->fd, (struct sockaddr *)&sck->sockaddr, &len) == -1)
        {
#ifdef _WIN32
			char err[256];
			strerror_s(err, errno);
			throw Network::Socket::SocketException(err);
#else
            throw Network::Socket::SocketException(strerror(errno));
#endif
        }
    }
}

/**
 * @brief Print the current instance into the output sent
 * @param output The output in which write
 */
void Network::Socket::ASocket::print(std::ostream &output) const
{
    output << inet_ntoa(sockaddr.sin_addr) << ":" << sockaddr.sin_port;
}

unsigned int Network::Socket::ASocket::getIP() const {
    return (sockaddr.sin_addr.s_addr);
}

unsigned int Network::Socket::ASocket::getPort() const {
    return (static_cast<unsigned int>(sockaddr.sin_port));
}

unsigned int Network::Socket::ASocket::getIPFromString(std::string const &ip) {
    struct in_addr addr;

#if _WIN32
    if (inet_pton(AF_INET, ip.c_str(), &addr) == 0) {
        return (0);
    }
#else
	if (inet_aton(ip.c_str(), &addr) == 0) {
		return (0);
	}
#endif
    return addr.s_addr;
}

std::string Network::Socket::ASocket::getIPFromUInt(unsigned int ip) {
    struct in_addr ip_addr;

    ip_addr.s_addr = ip;
    char *stringip = inet_ntoa(ip_addr);
    return std::string(stringip);
}


/**
 * @brief Basic write operator for ASocket that call print() method
 * @param output The output in which write
 * @param ref The reference of the object to dump
 * @return A reference on the output sent
 */
PREF_EXPORT std::ostream    &Network::Socket::operator<<(std::ostream &output, Network::Socket::ASocket const &ref)
{
    ref.print(output);
    return output;
}
