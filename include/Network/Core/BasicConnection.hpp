//
// Created by gaspar_q on 11/26/16.
//

#ifndef RTYPE_BASICCONNECTION_HPP
#define RTYPE_BASICCONNECTION_HPP

#include <Network/Socket/ISockStreamHandlersContainer.hpp>
#include <queue>
#include "IConnection.hpp"
#include "NativeSocketIOOperationDispatcher.hpp"

namespace Network
{
    namespace Core
    {
        /**
         * @brief Class that abstract the Connection concept. It's here for dispatcher and clients container. It also provides some space for messages queue
         */
        class BasicConnection : public IConnection
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
