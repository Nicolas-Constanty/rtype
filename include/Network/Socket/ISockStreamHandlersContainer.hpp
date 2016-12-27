//
// Created by gaspar_q on 11/26/16.
//

#ifndef RTYPE_ISOCKSTREAMSCONTAINER_HPP
#define RTYPE_ISOCKSTREAMSCONTAINER_HPP

#include <memory>
#include <list>
#include "ISockStream.hpp"
#include "ISockStreamHandler.hpp"

namespace Network
{
    namespace Socket
    {
        class LIB_EXPORT ISockStreamHandlersContainer
        {
        public:
            virtual ~ISockStreamHandlersContainer(){}

        public:
            virtual void Add(ISockStreamHandler *toAdd) = 0;
            virtual void Remove(ISockStreamHandler *torm) = 0;
            virtual void Move(ISockStreamHandler *curr, ISockStreamHandler *newone) = 0;

        public:
            virtual void Broadcast(Core::NetBuffer &tosnd, Socket::ISockStream &sender) = 0;

        public:
            virtual std::list<std::unique_ptr<Socket::ISockStreamHandler>> &Streams() = 0;
        };
    }
}

#endif //RTYPE_ISOCKSTREAMSCONTAINER_HPP
