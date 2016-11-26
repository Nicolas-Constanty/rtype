//
// Created by gaspar_q on 11/26/16.
//

#ifndef RTYPE_BASICCONNECTION_HPP
#define RTYPE_BASICCONNECTION_HPP

#include <Network/Socket/ISockStreamsContainer.hpp>
#include <queue>
#include "IConnection.hpp"
#include "NativeSocketIOOperationDispatcher.hpp"

namespace Network
{
    namespace Core
    {
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
            virtual void setClients(Socket::ISockStreamsContainer *clts);

        public:
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
            Network::Socket::ISockStreamsContainer *clients; //optional attribute, will be instantiate by another class if need it
            std::queue<Core::NetBuffer> toWrite;
        };
    }
}

#endif //RTYPE_BASICCONNECTION_HPP
