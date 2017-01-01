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
        class PREF_EXPORT ISockStreamHandler : public ISocketContainer
        {
        public:
			ISockStreamHandler() {}
            virtual ~ISockStreamHandler(){}

            //ISocketContainer
        public:
            virtual ISocket &giveSocket() = 0;
            virtual ISocket const &getSocket() const = 0;

        public:
            virtual bool OnStart() = 0;
            virtual void OnReadCheck() = 0;
            virtual void OnWriteCheck() = 0;
            virtual void OnAllowedToRead() = 0;
            virtual void OnAllowedToWrite() = 0;
            virtual bool OnDataReceived(unsigned int len) = 0;
            virtual bool OnDataSent(unsigned int len) = 0;
            virtual void OnDisconnect() = 0;
        };
    }
}

#endif //SPIDER_SERVER_ISTREAMHANDLER_HPP
