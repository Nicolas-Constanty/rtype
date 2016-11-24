//
// Created by gaspar on 23/11/2016.
//

#ifndef RTYPE_ATCPSERVER_HPP
#define RTYPE_ATCPSERVER_HPP

#ifdef __linux__
 #include <vector>
#elif _WIN32
 #include <c++/vector>
#endif

#include <Network/Core/NativeSocketIOOperationDispatcher.hpp>
#include <c++/queue>
#include "ATCPConnection.hpp"

namespace Network
{
    namespace TCP
    {
        template <typename ClientType>
        class ATCPServer : public ATCPConnection
        {
        public:
            /**
             * @brief Basic constructor
             */
            ATCPServer() :
                ATCPConnection()
            {

            }

            /**
             * @brief Copy constructor
             * @param ref The reference to copy
             */
            ATCPServer(ATCPServer const &ref) :
                    ATCPConnection(ref)
            {

            }

            /**
             * @brief Basic destructor
             */
            virtual ~ATCPServer()
            {

            }

        public:
            /**
             * @brief Callback called when there is data to read on socket
             * @return True if a new client has been accepted, false either
             */
            virtual bool OnAllowedToRead()
            {
                ClientType  *newclient = new ClientType(Socket::TCP);

                try
                {
                    sock.Accept(newclient->sock);
                }
                catch (Network::Socket::SocketException const &err)
                {
                    std::cerr << "Accept failure: " << err.what() << std::endl;
                    delete newclient;
                    return false;
                }
                Core::NativeSocketIOOperationDispatcher::Instance().Watch(*newclient);
                garbage.emplace_back(newclient);
                return true;
            }

        private:
            std::list<std::unique_ptr<ClientType> >   garbage;
        };
    }
}

#endif //RTYPE_ATCPSERVER_HPP
