//
// Created by gaspar_q on 11/25/16.
//

#ifndef RTYPE_AUDPSERVER_HPP
#define RTYPE_AUDPSERVER_HPP

#include <list>
#include <chrono>
#include <bits/unique_ptr.h>
#include <Network/Socket/BasicSockStreamsContainer.hpp>
#include "AUDPConnection.hpp"

namespace Network
{
    namespace UDP
    {
        /**
         * @brief The timeout after which disconnet user
         */
        constexpr static const std::chrono::milliseconds    timeout = std::chrono::milliseconds(30000);

        /**
         * @brief Class that corresponds to an UDP server
         * @tparam ClientType The type of the client to instaciate when receiving a new connection
         */
        template <typename ClientType>
        class AUDPServer : public AUDPConnection
        {
            /**
             * @brief Nested private class that associates a timer to a client
             */
            class TimedUDPClient : public ClientType
            {
            public:
                /**
                 * @brief Basic constructor
                 * @param c A pointer on a new client
                 */
                TimedUDPClient(ClientType const &ref) :
                    ClientType(ref),
                    lastmsg(std::chrono::steady_clock::now())
                {

                }

                /**
                 * @brief Basic destructor
                 */
                ~TimedUDPClient()
                {

                }

            public:
                /**
                 * @brief Refresh the internal timer to current time
                 */
                void refresh()
                {
                    if (timedout())
                        std::cout << "Was timed out" << std::endl;
                    lastmsg = std::chrono::steady_clock::now();
                }

                /**
                 * @brief Check if the internal client is timedout
                 * @return True if the timer hasn't been refreshed for <timeout> duration
                 */
                bool timedout()
                {
                    return std::chrono::steady_clock::now() - lastmsg > timeout;
                }

            private:
                std::chrono::time_point<std::chrono::steady_clock>  lastmsg;
            };

        public:
            /**
             * @brief Basic constructor
             */
            AUDPServer(Core::NativeSocketIOOperationDispatcher &dispatcher) :
                    AUDPConnection(dispatcher),
                    buff(),
                    newclient(NULL)
            {
                clients = new Socket::BasicSockStreamsContainer();
            }

            /**
             * @brief Basic copy constructor
             * @param ref The reference to copy
             */
            AUDPServer(AUDPServer const &ref) :
                    AUDPConnection(ref),
                    buff(),
                    newclient(NULL)
            {
                clients = new Socket::BasicSockStreamsContainer();
            }

            /**
             * @brief Basic destructor
             */
            virtual ~AUDPServer()
            {
                delete(clients);
            }

        public:
            /**
             * @brief Callback called after <select> detects the current file descriptor is allowed to read
             * @return True if everything went fine, false either
             */
            virtual void    OnAllowedToRead()
            {
                newclient = new TimedUDPClient(Dispatcher());
                buff.reset();

                int ret;

                buff.reset();
                ret = sock.ReceiveFrom(buff, newclient->giveSocket());
                if (ret > 0)
                {
                    //Check which client send us data
                    for (typename std::list<std::unique_ptr<Socket::ISockStreamHandler>>::iterator it = clients->Streams().begin(); it != clients->Streams().end(); ++it)
                    {
                        TimedUDPClient *clt = dynamic_cast<TimedUDPClient *>(it->get());

                        if (clt == NULL)
                            continue;

                        //And call the callback in case of matching
                        if ((*it)->getSocket() == newclient->getSocket())
                        {
                            clt->refresh();
                            clt->setBuffer(buff);
                            WantReceive();
                            clt->OnDataReceived(ret);
                            std::cout << "Client found" << std::endl;
                            return ;
                        }
//                        else if (clt->timedout()) //todo replace it in another callback #disconnectionClientTimeout
//                        {
//                            std::cout << "Disconnecting client" << std::endl;
//                            clt->Disconnect();
//                        }
                    }
                    std::cout << "New client joined: " << (Socket::ASocket const &)newclient->getSocket() << std::endl;
                    //Either it mean that it's a new client, so push it in <clients> list
                    clients->Add(newclient);
                    //And call the callbacks
                    newclient->setBuffer(buff);
                    newclient->OnDataReceived(ret);
                    WantReceive();
                    OnDataReceived(0);
                }
                else
                {
                    delete(newclient);
                    Disconnect();
                }
            }

            /**
             * @brief Callback called after <select> detects the current file discriptor is allowed to write
             * @return True if everything went fine, false either
             */
            virtual void    OnAllowedToWrite()
            {
                unsigned int final = 0;

                //Send messages that are in the server to all clients
                while (!toWrite.empty())
                {
                    clients->Broadcast(toWrite.front(), sock);
                    toWrite.pop();
                }

                //Send messages that are in each client, to the specified client
                for (std::unique_ptr<Socket::ISockStreamHandler> &curr : clients->Streams())
                {
                    std::cout << "====>Checking client" << std::endl;
                    std::queue<Core::NetBuffer> &msgs = dynamic_cast<Core::BasicConnection *>(curr.get())->Messages();

                    while (!msgs.empty())
                    {
                        std::cout << "Sending: " << msgs.front() << std::endl;
                        int ret = sock.SendTo(msgs.front(), curr->giveSocket());

                        if (ret < 0)
                            return ;
                        final += ret;
                        curr->OnDataSent(static_cast<unsigned int>(ret));
                        msgs.pop();
                    }
                }

                if (final > 0)
                    OnDataSent(final);
            }

        protected:
            Core::NetBuffer             buff;
            ClientType                  *newclient;
        };
    }
}

#endif //RTYPE_AUDPSERVER_HPP
