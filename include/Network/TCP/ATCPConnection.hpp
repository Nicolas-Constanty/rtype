//
// Created by gaspar on 23/11/2016.
//

#ifndef RTYPE_ATCPCONNECTION_HPP
#define RTYPE_ATCPCONNECTION_HPP

#ifdef __linux__
#include <queue>
#include <Network/Socket/UnixSocket.hpp>
#elif _WIN32
#include <c++/queue>
#include <Network/Socket/WinSocket.hpp>
#endif

#include <Network/Socket/INativeSocketStreamHandler.hpp>
#include <Network/Socket/ASocket.hpp>

namespace Network
{
    namespace TCP
    {
        class ATCPConnection : public Socket::INativeSocketStreamHandler
        {
        public:
            ATCPConnection();
            ATCPConnection(ATCPConnection const &ref);
            virtual ~ATCPConnection();

        public:
            virtual SOCKET Native() const;
            virtual bool OnAllowedToWrite();

        public:
            /**
             * @brief Function that send data into socket (in fact it stores data internally in prevision of writing it later)
             * @tparam T
             * @param tosend
             */
            template <typename T>
            void sendData(T const &tosend)
            {
                Core::NetBuffer buff;

                buff.serialize(tosend);
                pushBuffer(buff);
            }

            void pushBuffer(Network::Core::NetBuffer const &topush);

        public:
            virtual Socket::ISocket &giveSocket();
            virtual Socket::ISocket const &getSocket() const;

        protected:
            Socket::OSSocket                        sock;
            Core::NetBuffer                         buff;
            std::queue<Network::Core::NetBuffer>    toWrite;
        };
    }
}

#endif //RTYPE_ATCPCONNECTION_HPP
