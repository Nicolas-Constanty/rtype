//
// Created by gaspar on 23/11/2016.
//

#ifndef RTYPE_ATCPSERVER_HPP
#define RTYPE_ATCPSERVER_HPP

#ifdef __linux__
 #include <vector>
 #include <queue>
#elif _WIN32
 #include <vector>
#include <queue>
#endif

#include "Network/Core/NativeSocketIOOperationDispatcher.hpp"
#include "Network/Socket/BasicSockStreamsContainer.hpp"
#include "ATCPConnection.hpp"

namespace Network
{
    namespace TCP
    {
        template <typename ClientType>
        class LIB_EXPORT ATCPServer : public ATCPConnection
        {
        public:
            /**
             * @brief Basic constructor
             */
            ATCPServer(Core::NativeSocketIOOperationDispatcher &dispatcher) :
                ATCPConnection(dispatcher)
            {
                clients = new Socket::BasicSockStreamsContainer();
            }

            /**
             * @brief Copy constructor
             * @param ref The reference to copy
             */
            ATCPServer(ATCPServer const &ref) :
                    ATCPConnection(ref)
            {
                clients = new Socket::BasicSockStreamsContainer();
            }

            /**
             * @brief Basic destructor
             */
            virtual ~ATCPServer()
            {
                delete(clients);
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
                OnStart();
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
            virtual void OnAllowedToRead()
            {
                newclient = new ClientType(*this);

                try
                {
                    sock.Accept(newclient->giveSocket());
                }
                catch (Network::Socket::SocketException const &err)
                {
                    std::cerr << "Accept failure: " << err.what() << std::endl;
                    delete newclient;
                    throw err;
                }
                newclient->setClients(clients);
                clients->Add(newclient);
                newclient->WantReceive();
                newclient->OnStart();
                WantReceive();
                OnDataReceived(0);
            }

            /**
             * @brief Callback called when data has been received
             */
            virtual bool OnDataReceived(unsigned int)
            {
                WantReceive();
                return (true);
            }

            virtual bool OnStart()
            {
                return (true);
            }

        protected:
            ClientType  *newclient;
        };
    }
}

#endif //RTYPE_ATCPSERVER_HPP
