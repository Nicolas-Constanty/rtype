//
// Created by gaspar_q on 11/25/16.
//

#ifndef RTYPE_AUDPSERVER_HPP
#define RTYPE_AUDPSERVER_HPP

#include <list>
#include <chrono>
#include <memory>
#include <Network/Socket/BasicSockStreamsContainer.hpp>
#include <Network/Core/Timer.hpp>
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
        protected:
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
                    timer()
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
                    timer.refresh();
                }

                /**
                 * @brief Check if the internal client is timedout
                 * @return True if the timer hasn't been refreshed for <timeout> duration
                 */
                bool timedout()
                {
                    return timer.timeout(timeout);
                }

                Core::Timer const &getTimer() const
                {
                    return timer;
                }

            private:
                Core::Timer timer;
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
                if (newclient)
                    delete(newclient);
            }

        public:
            /**
             * @brief Function which will launch the server and made him listen on a specific port
             * @param port The port to which bind the socket
             */
            void Start(const uint16_t port)
            {
                std::cout << "\x1b[31mStarting server on port\x1b[0m: " << port << std::endl;
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
             * @brief Callback called after <select> detects the current file descriptor is allowed to read
             * @return True if everything went fine, false either
             */
            virtual void    OnAllowedToRead()
            {
                if (newclient == NULL)
                    newclient = new TimedUDPClient(Dispatcher());
                if (newclient == NULL) {
                    std::cout << "newClient still NULL" << std::endl;
                    return;
                }
                buff.reset();

                int ret;

                buff.reset();
                ret = sock.ReceiveFrom(buff, newclient->giveSocket());
                if (ret > 0)
                {
                    //Check which client send us data
                    for (std::unique_ptr<Socket::ISockStreamHandler> &curr : clients->Streams())
                    {
                        TimedUDPClient *clt = dynamic_cast<TimedUDPClient *>(curr.get());

                        if (clt == NULL)
                            continue;

                        curr->OnReadCheck();
                        //And call the callback in case of matching
                        if (curr->getSocket() == newclient->getSocket())
                        {
                            clt->refresh();
                            clt->setBuffer(buff);
                            WantReceive();
                            clt->OnDataReceived(ret);
                            return ;
                        }
                    }
                    std::cout << "New client joined: " << (Socket::ASocket const &)newclient->getSocket() << std::endl;
                    //Either it mean that it's a new client, so push it in <clients> list
                    clients->Add(newclient);
                    newclient->setServer(this);
                    newclient->setClients(clients);
                    if (newclient->OnStart())
                    {
                        //tells the server a new client join
                        WantReceive();
                        if (OnDataReceived(0))
                        {
                            //And call the callbacks
                            newclient->setBuffer(buff);
                            newclient->OnDataReceived(ret);
                            //reset the pointer in order to reallocate it
                            newclient = NULL;
                        }
                    }
                }
                else
                {
                    delete(newclient);
                    Disconnect();
                }
            }

            /**
             * @brief Callback called juste before checking if the fd is allowed to read
             */
            virtual void OnReadCheck()
            {
                std::list<std::unique_ptr<Socket::ISockStreamHandler>> &streams = clients->Streams();
                for (typename std::list<std::unique_ptr<Socket::ISockStreamHandler> >::iterator it = streams.begin(); it != streams.end();)
                {
                    TimedUDPClient  *clt = dynamic_cast<TimedUDPClient *>(it->get());

                    clt->OnReadCheck();
                    if (clt->timedout())
                    {
                        clt->Disconnect();
                        it = streams.begin();
                    }
                    else
                        ++it;
                }
            }

            /**
             * @brief Callback called when we are checking
             */
            virtual void OnWriteCheck()
            {
                for (std::unique_ptr<Socket::ISockStreamHandler> &curr : clients->Streams())
                {
                    curr->OnWriteCheck();
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
//                    std::cout << "====>Checking client" << std::endl;
                    std::queue<Core::NetBuffer> &msgs = dynamic_cast<Core::BasicConnection *>(curr.get())->Messages();

                    while (!msgs.empty())
                    {
//                        std::cout << "Sending: " << msgs.front() << std::endl;
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