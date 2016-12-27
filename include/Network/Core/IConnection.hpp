//
// Created by gaspar_q on 11/26/16.
//

#ifndef RTYPE_ICONNECTION_HPP
#define RTYPE_ICONNECTION_HPP

#include "Network/Socket/ISockStreamHandler.hpp"
#include "Network/Socket/ISockStreamHandlersContainer.hpp"
#include "NativeSocketIOOperationDispatcher.hpp"
#include "Common/DLLexport.hpp"

namespace Network
{
    namespace Core
    {
        class LIB_EXPORT IConnection : public Socket::ISockStreamHandler
        {
        public:
            virtual ~IConnection(){}

        public:
            virtual void WantReceive() = 0;
            virtual void WantSend() = 0;
            virtual void Disconnect() = 0;

        public:
            virtual Core::NativeSocketIOOperationDispatcher &Dispatcher() = 0;
            virtual Core::NativeSocketIOOperationDispatcher const &Dispatcher() const = 0;
            virtual void setClients(Socket::ISockStreamHandlersContainer *clts) = 0;
        };
    }
}

#endif //RTYPE_ICONNECTION_HPP
