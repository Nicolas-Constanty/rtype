//
// Created by gaspar on 21/11/2016.
//

#ifndef NETWORK_ISOCKET_HPP
#define NETWORK_ISOCKET_HPP

#include <string>

extern "C"
{
# ifdef __linux__
#  include <sys/types.h>
#  include <sys/socket.h>
#  include <sys/select.h>
#  include <netdb.h>
#  include <netinet/in.h>
#  include <arpa/inet.h>
#  include <cstdint>
#  include <stdexcept>
# elif _WIN32
#  include <winsock2.h>
#  include <ws2tcpip.h>
#  include <c++/cstdint>
#  include <c++/stdexcept>
# endif
};

#include "INativeSocketContainer.hpp"
#include "ISockStream.hpp"

namespace Network
{
    namespace Socket
    {
        /**
         * @brief Class that defines a socket exception
         */
        class SocketException : public std::runtime_error
        {
        public:
            /**
             * @brief Basic constructor
             * @param err The error message to display
             */
            SocketException(std::string const &err) :
                    std::runtime_error(err)
            {

            }

            /**
             * @brief Basic destructor
             */
            virtual ~SocketException() throw()
            {

            }

            /**
             * @brief Reuse std::runtime_error::what method
             */
            using std::runtime_error::what;
        };

        class ISocket : public INativeSocketContainer, public ISockStream
        {
        public:
            virtual void Open() throw(SocketException) = 0;
            virtual void Close() = 0;

        public:
            virtual void Listen(const uint16_t port, const int nbc = SOMAXCONN) throw(SocketException) = 0;
            virtual void Talk(const std::string &ip, const uint16_t port) throw(SocketException) = 0;

        public:
            virtual void Accept(ISocket &sock) = 0;

        public:
            virtual SOCKET Native() const = 0;

        public:
            virtual bool operator==(ISocket const &ref) const = 0;
            virtual ISocket &operator=(ISocket const &ref) = 0;

        public:
            virtual unsigned int getIP() const = 0;
            virtual unsigned int getPort() const = 0;
        };
    }
}

#endif //NETWORK_ISOCKET_HPP
