//
// Created by gaspar_q on 11/25/16.
//

#ifndef RTYPE_INETBUFFERCONTAINER_HPP
#define RTYPE_INETBUFFERCONTAINER_HPP

#include "NetBuffer.hpp"

namespace Network
{
    namespace Core
    {
        class LIB_EXPORT INetBufferContainer
        {
        public:
            virtual ~INetBufferContainer(){}

        public:
            virtual NetBuffer const &getBuffer() const = 0;
            virtual NetBuffer &giveBuffer() = 0;
            virtual void setBuffer(NetBuffer const &buff) = 0;
        };
    }
}

#endif //RTYPE_INETBUFFERCONTAINER_HPP
