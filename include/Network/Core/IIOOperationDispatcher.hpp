//
// Created by gaspar_q on 11/10/16.
//

#ifndef SPIDER_SERVER_ISERVERDISPATCHER_HPP
#define SPIDER_SERVER_ISERVERDISPATCHER_HPP

#include <Network/Socket/ISockStreamHandler.hpp>

namespace Network
{
    namespace Core
    {
        class LIB_EXPORT IIOOperationDispatcher
        {
        public:
            virtual ~IIOOperationDispatcher(){}

        public:
            virtual void HandleReadOperations() = 0;
            virtual void HandleWriteOperations() = 0;
            virtual void HandleOperations() = 0;

        public:
            virtual void Run() = 0;
            virtual void Poll() = 0;
            virtual void Poll(Socket::ISockStreamHandler &handler) = 0;
        };
    }
}

#endif //SPIDER_SERVER_ISERVERDISPATCHER_HPP
