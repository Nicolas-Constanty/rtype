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
        class ATCPClient : public ATCPConnection
        {
        public:
            ATCPClient();
            ATCPClient(ATCPClient const &ref);
            virtual ~ATCPClient();

        public:
            virtual bool OnAllowedToRead();
        };
    }
}

#endif //RTYPE_ATCPCLIENT_HPP
