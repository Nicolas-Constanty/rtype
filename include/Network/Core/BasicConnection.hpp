//
// Created by gaspar_q on 11/26/16.
//

#ifndef RTYPE_BASICCONNECTION_HPP
#define RTYPE_BASICCONNECTION_HPP

#include <Network/Socket/ISockStreamHandlersContainer.hpp>
#include <queue>
#include "IConnection.hpp"
#include "NativeSocketIOOperationDispatcher.hpp"
#include "Timer.hpp"
#include "Protocol/Game/ProtocolGamePackage.hpp"

namespace Network
{
    namespace Core
    {
        /**
         * @brief Class that abstract the Connection concept. It's here for dispatcher and clients container. It also provides some space for messages queue
         */
        class PREF_EXPORT BasicConnection : public IConnection
        {
        public:
            BasicConnection(NativeSocketIOOperationDispatcher &dispatcher);
            virtual ~BasicConnection();

            //IConnection
        public:
            virtual void WantReceive();
            virtual void WantSend();
            virtual void Disconnect();

            virtual Core::NativeSocketIOOperationDispatcher &Dispatcher();
            virtual Core::NativeSocketIOOperationDispatcher const &Dispatcher() const;
            virtual void setClients(Socket::ISockStreamHandlersContainer *clts);

        public:
            virtual void OnReadCheck();
            virtual void OnWriteCheck();
            virtual void OnDisconnect();

        public:
            /**
             * @brief Used for sending any kind of data through socket
             * @tparam T The type of data to send
             * @param towr The data to send
             */
            template <typename T>
            void SendData(T const &towr)
            {
                toWrite.emplace(towr);
                WantSend();
            }

            template <typename T>
            void SendDataNow(T const &towr)
            {
                giveSocket().Send(towr);
            }

            template <typename U = BasicConnection, typename T>
            void Broadcast(T const &towr) {
                if (!clients)
                    return;
                for (Socket::ISockStreamHandler *curr : clients->Streams()) {
                    U *basicConnection;

                    if ((basicConnection = dynamic_cast<U *>(curr))) {
                        basicConnection->SendData(towr);
                    }
                }
            }

            template <typename U = BasicConnection, typename T>
            void BroadcastNow(T const &towr) {
                if (!clients)
                    return;
                for (Socket::ISockStreamHandler *curr : clients->Streams()) {
                    U *basicConnection;

                    if ((basicConnection = dynamic_cast<U *>(curr))) {
                        basicConnection->giveSocket().Send(towr);
                    }
                }
            }


            std::queue<Core::NetBuffer> &Messages();

        private:
            NativeSocketIOOperationDispatcher &dispatcher;

        protected:
            Network::Socket::ISockStreamHandlersContainer *clients; //optional attribute, will be instantiate by another class if need it
            std::queue<Core::NetBuffer> toWrite;
        };
    }
}

#endif //RTYPE_BASICCONNECTION_HPP
