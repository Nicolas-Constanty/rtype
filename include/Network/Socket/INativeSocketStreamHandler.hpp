//
// Created by gaspar_q on 11/11/16.
//

#ifndef SPIDER_SERVER_ISTREAMHANDLER_HPP
#define SPIDER_SERVER_ISTREAMHANDLER_HPP

#include "Network/Socket/INativeSocketContainer.hpp"

namespace Network
{
    namespace Socket
    {
        class INativeSocketStreamHandler : public INativeSocketContainer
        {
        public:
            virtual ~INativeSocketStreamHandler(){}

        public:
            virtual SOCKET Native() const = 0;
            virtual bool OnAllowedToRead() = 0;
            virtual bool OnAllowedToWrite() = 0;
            virtual void OnDataReceived(unsigned int len) = 0;
            virtual void OnDataSent(unsigned int len) = 0;
        };
    }
}

#endif //SPIDER_SERVER_ISTREAMHANDLER_HPP
