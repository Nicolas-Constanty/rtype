//
// Created by gaspar on 23/11/2016.
//

#ifndef RTYPE_ATCPCONNECTION_HPP
#define RTYPE_ATCPCONNECTION_HPP

#ifdef __linux__
#include <queue>
#elif _WIN32
#include <c++/queue>
#endif

#include <Network/Socket/INativeSocketStreamHandler.hpp>
#include <Network/Socket/ASocket.hpp>
#include <Network/Socket/WinSocket.hpp>

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
                toWrite.push(buff);
            }

        protected:
            Socket::OSSocket                        sock;
            Core::NetBuffer                         buff;
            std::queue<Network::Core::NetBuffer>    toWrite;
        };
    }
}

#endif //RTYPE_ATCPCONNECTION_HPP
