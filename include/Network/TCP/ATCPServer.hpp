//
// Created by gaspar on 23/11/2016.
//

#ifndef RTYPE_ATCPSERVER_HPP
#define RTYPE_ATCPSERVER_HPP

#ifdef __linux__
 #include <vector>
 #include <queue>
#elif _WIN32
 #include <c++/vector>
#include <c++/queue>
#endif

#include <Network/Core/NativeSocketIOOperationDispatcher.hpp>
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
             * @brief Function which will launch the server and made him listen on a specific port
             * @param port The port to which bind the socket
             */
            void Start(const uint16_t port)
            {
                sock.Open();
                sock.Listen(port);
            }

            /**
             * @brief Function which will stop the server and close the socket
             */
            void Stop()
            {
                sock.Close();
            }

        public:
            /**
             * @brief Callback called when there is data to read on socket
             * @return True if a new client has been accepted, false either
             */
            virtual bool OnAllowedToRead()
            {
                ClientType  *newclient = new ClientType();

                try
                {
                    sock.Accept(newclient->giveSocket());
                }
                catch (Network::Socket::SocketException const &err)
                {
                    std::cerr << "Accept failure: " << err.what() << std::endl;
                    delete newclient;
                    return false;
                }
                Core::NativeSocketIOOperationDispatcher::Instance().Watch(*newclient);
                garbage.emplace_back(newclient);
                OnDataReceived(0);
                return true;
            }

        private:
            std::list<std::unique_ptr<ClientType> >   garbage;
        };
    }
}

#endif //RTYPE_ATCPSERVER_HPP
