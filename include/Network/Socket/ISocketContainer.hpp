//
// Created by gaspar_q on 11/24/16.
//

#ifndef RTYPE_ISOCKETCONTAINER_HPP
#define RTYPE_ISOCKETCONTAINER_HPP

#include "Network/Socket/ISocket.hpp"

namespace Network
{
    namespace Socket
    {
        class LIB_EXPORT ISocketContainer
        {
        public:
            virtual ~ISocketContainer(){}

        public:
            virtual ISocket &giveSocket() = 0;
            virtual ISocket const &getSocket() const = 0;
        };
    }
}

#endif //RTYPE_ISOCKETCONTAINER_HPP
