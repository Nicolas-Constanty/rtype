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
        class ISockStreamHandler : public ISocketContainer
        {
        public:
            virtual ~ISockStreamHandler(){}

            //ISocketContainer
        public:
            virtual ISocket &giveSocket() = 0;
            virtual ISocket const &getSocket() const = 0;

        public:
            virtual void OnStart() = 0;
            virtual void OnReadCheck() = 0;
            virtual void OnWriteCheck() = 0;
            virtual void OnAllowedToRead() = 0;
            virtual void OnAllowedToWrite() = 0;
            virtual void OnDataReceived(unsigned int len) = 0;
            virtual void OnDataSent(unsigned int len) = 0;
        };
    }
}

#endif //SPIDER_SERVER_ISTREAMHANDLER_HPP
