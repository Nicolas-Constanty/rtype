//
// Created by gaspar_q on 11/25/16.
//

#ifndef RTYPE_AUDPCONNECTION_HPP
#define RTYPE_AUDPCONNECTION_HPP

#ifdef __linux__
 #include <queue>
#include <Network/Socket/UnixSocket.hpp>
#elif _WIN32
 #include <c++/queue>
 #include <Network/Socket/WinSocket.hpp>
#endif

#include <Network/Socket/ISockStreamHandler.hpp>
#include <Network/Core/BasicConnection.hpp>

namespace Network
{
    namespace UDP
    {
        /**
         * @brief Abstraction of an UDP connection
         */
        class AUDPConnection : public Core::BasicConnection
        {
        public:
            AUDPConnection(Core::NativeSocketIOOperationDispatcher &dispatcher);
            AUDPConnection(AUDPConnection const &);
            virtual ~AUDPConnection();

            //Socket::ISockStreamHandlers
        public:
            virtual Socket::ISocket &giveSocket();
            virtual Socket::ISocket const &getSocket() const;

        public:
            virtual void OnStart();

        protected:
            Socket::OSSocket sock;
        };
    }
}

#endif //RTYPE_AUDPCONNECTION_HPP
