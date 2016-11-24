//
// Created by gaspar_q on 11/10/16.
//

#ifndef SPIDER_SERVER_SERVERDISPATCHER_HPP
#define SPIDER_SERVER_SERVERDISPATCHER_HPP

#include <list>
#include <memory>
#include <Common/Singleton.hpp>
#include "Network/Core/IIOOperationDispatcher.hpp"
#include "Network/Socket/UnixSocket.hpp"
#include "Network/Socket/INativeSocketStreamHandler.hpp"

namespace Network
{
    namespace Core
    {
        /**
         * \brief Class that will handle the entire system of Input/Output operations dispatchment through the call of
         * <select> then through the callbacks implemented by INativeSocketStreamHandler
         */
        class NativeSocketIOOperationDispatcher : public IIOOperationDispatcher, public Singleton<NativeSocketIOOperationDispatcher>
        {
        public:
            friend class Singleton<NativeSocketIOOperationDispatcher>;

        private:
            NativeSocketIOOperationDispatcher(struct timeval const &timeout);
            NativeSocketIOOperationDispatcher(struct timeval *timeout = NULL);

            virtual ~NativeSocketIOOperationDispatcher();

            //IIOOperationDispatcher
        public:
            virtual void HandleReadOperations();
            virtual void HandleWriteOperations();
            virtual void HandleOperations();

            virtual void Run();

        public:
                void Watch(Socket::INativeSocketStreamHandler &towatch);

        public:
            void    setTimeout(struct timeval const &timeout);
            void    setTimeout(struct timeval *timeout);

        private:
            SOCKET bindFdsToSet(fd_set &set) const;
            void performReadOperations(fd_set &set);
            void performWriteOperations(fd_set &set);

        private:
            std::list<std::unique_ptr<Socket::INativeSocketStreamHandler>>  m_toWatch;
            std::unique_ptr<struct timeval>                                 m_timeout;
        };
    }
}

#endif //SPIDER_SERVER_SERVERDISPATCHER_HPP
