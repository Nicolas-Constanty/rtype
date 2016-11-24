//
// Created by gaspar_q on 11/11/16.
//

#ifndef SPIDER_SERVER_ISTREAMHANDLER_HPP
#define SPIDER_SERVER_ISTREAMHANDLER_HPP

//#include "Network/Socket/INativeSocketContainer.hpp"
#include "ISocketContainer.hpp"

namespace Network
{
    namespace Socket
    {
        class INativeSocketStreamHandler : public ISocketContainer
        {
        public:
            virtual ~INativeSocketStreamHandler(){}

        public:
            virtual ISocket &giveSocket() = 0;
            virtual ISocket const &getSocket() const = 0;
            virtual bool OnAllowedToRead() = 0;
            virtual bool OnAllowedToWrite() = 0;
            virtual void OnDataReceived(unsigned int len) = 0;
            virtual void OnDataSent(unsigned int len) = 0;
        };
    }
}

#endif //SPIDER_SERVER_ISTREAMHANDLER_HPP
