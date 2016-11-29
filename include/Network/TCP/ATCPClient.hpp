//
// Created by gaspar on 24/11/2016.
//

#ifndef RTYPE_ATCPCLIENT_HPP
#define RTYPE_ATCPCLIENT_HPP

#include "ATCPConnection.hpp"

namespace Network
{
    namespace TCP
    {
        /**
         * @brief Abstraction of a TCP Client
         */
        class ATCPClient : public ATCPConnection
        {
        public:
            ATCPClient(Core::NativeSocketIOOperationDispatcher &dispatcher);
            ATCPClient(ATCPClient const &ref);
            virtual ~ATCPClient();

        public:
            virtual void OnAllowedToRead();

        public:
            void Connect(std::string const &ip, const uint16_t port);
            virtual void OnStart();
        };
    }
}

#endif //RTYPE_ATCPCLIENT_HPP
