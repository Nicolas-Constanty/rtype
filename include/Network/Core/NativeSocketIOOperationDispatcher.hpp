//
// Created by gaspar_q on 11/10/16.
//

#ifndef SPIDER_SERVER_SERVERDISPATCHER_HPP
#define SPIDER_SERVER_SERVERDISPATCHER_HPP

#include <list>
#include <memory>
#include "Network/Core/IIOOperationDispatcher.hpp"
#include "Network/Socket/UnixSocket.hpp"
#include "Network/Socket/ISockStreamHandler.hpp"

namespace Network
{
    namespace Core
    {
        /**
         * \brief Class that will handle the entire system of Input/Output operations dispatchment through the call of
         * <select> then through the callbacks implemented by INativeSocketStreamHandler
         */
        class NativeSocketIOOperationDispatcher : public IIOOperationDispatcher
        {
        private:
            struct IOOperation
            {
                std::string name;
                std::list<Socket::ISockStreamHandler *> NativeSocketIOOperationDispatcher::*watched;
                void (Socket::ISockStreamHandler::*callback)();
            };

            static const IOOperation  read;
            static const IOOperation  write;

        public:
            enum WatchMode
            {
                READ = 1,
                WRITE = 2,
                BOTH = 3
            };

        public:
            NativeSocketIOOperationDispatcher(struct timeval const &timeout);
            NativeSocketIOOperationDispatcher(struct timeval *timeout = NULL);

            virtual ~NativeSocketIOOperationDispatcher();

            //IIOOperationDispatcher
        public:
            virtual void HandleReadOperations();
            virtual void HandleWriteOperations();
            virtual void HandleOperations();

            virtual void Run();
            virtual void Poll();
            virtual void Poll(Socket::ISockStreamHandler &handler);

        public:
            void Watch(Socket::ISockStreamHandler &towatch, WatchMode mode = WatchMode::BOTH);
            void Watch(Socket::ISockStreamHandler *towatch, WatchMode mode = WatchMode::BOTH);
            bool IsBinded(Socket::ISockStreamHandler *tocheck, WatchMode mode = WatchMode::BOTH);

        public:
            void Remove(Socket::ISockStreamHandler *torm, WatchMode mode = WatchMode::BOTH);

        public:
            void    setTimeout(struct timeval const &timeout);
            void    setTimeout(struct timeval *timeout);

        private:
            SOCKET bindFdsToSet(fd_set &set, std::list<Socket::ISockStreamHandler *> &tobind) const;
            void performOperations(fd_set &set, IOOperation const &operation);

        private:
            std::list<Socket::ISockStreamHandler *>  m_readWatch;
            std::list<Socket::ISockStreamHandler *>  m_writeWatch;
            std::unique_ptr<struct timeval>                         m_timeout;
        };
    }
}

#endif //SPIDER_SERVER_SERVERDISPATCHER_HPP
