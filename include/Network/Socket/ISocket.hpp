//
// Created by gaspar on 21/11/2016.
//

#ifndef NETWORK_ISOCKET_HPP
#define NETWORK_ISOCKET_HPP

#include <string>

#if _WIN32
	#pragma warning( disable : 4290 )  
	#include <cstdint>
	#include <stdexcept>
	typedef uint8_t u_int8_t;
	typedef uint16_t u_int16_t;
	typedef uint32_t u_int32_t;
#else
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <sys/select.h>
	#include <netdb.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <cstdint>
	#include <stdexcept>
#endif

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
