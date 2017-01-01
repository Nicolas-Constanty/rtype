//
// Created by gaspar on 23/11/2016.
//

#ifndef RTYPE_ATCPCONNECTION_HPP
#define RTYPE_ATCPCONNECTION_HPP

#ifdef __linux__
#include <queue>
#include "Network/Socket/UnixSocket.hpp"
#elif _WIN32
#include <queue>
#include "Network/Socket/WinSocket.hpp"
#endif

#include "Network/Socket/ISockStreamHandler.hpp"
#include "Network/Socket/ASocket.hpp"
#include "Network/Core/NativeSocketIOOperationDispatcher.hpp"
#include "Network/Core/BasicConnection.hpp"

namespace Network
{
    namespace TCP
    {
        /**
         * @brief Abstraction of a TCP connection
         */
        class PREF_EXPORT ATCPConnection : public Core::BasicConnection
        {
        public:
            ATCPConnection(Core::NativeSocketIOOperationDispatcher &dispatcher);
            ATCPConnection(ATCPConnection const &ref);
            virtual ~ATCPConnection();

        public:
            virtual void OnAllowedToWrite();

        public:
            virtual Socket::ISocket &giveSocket();
            virtual Socket::ISocket const &getSocket() const;

        protected:
            Socket::OSSocket                        sock;
            Core::NetBuffer                         buff;
        };
    }
}

#endif //RTYPE_ATCPCONNECTION_HPP
