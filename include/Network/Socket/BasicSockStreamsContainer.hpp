//
// Created by gaspar_q on 11/26/16.
//

#ifndef RTYPE_BASICSOCKSTREAMSCONTAINER_HPP
#define RTYPE_BASICSOCKSTREAMSCONTAINER_HPP

#include <memory>
#include <list>
#include "ISockStreamsContainer.hpp"

namespace Network
{
    namespace Socket
    {
        class BasicSockStreamsContainer : public ISockStreamsContainer
        {
        public:
            BasicSockStreamsContainer();
            BasicSockStreamsContainer(BasicSockStreamsContainer &ref) = delete;
            virtual ~BasicSockStreamsContainer();

        public:
            virtual void Add(ISockStreamHandler *toadd);
            virtual void Remove(ISockStreamHandler *torm);
            virtual void Move(ISockStreamHandler *old, ISockStreamHandler *newone);

            virtual void Broadcast(Core::NetBuffer &tosnd, Socket::ISockStream &sender);

            virtual std::list<std::unique_ptr<Socket::ISockStreamHandler>> &Streams();

        private:
            std::list<std::unique_ptr<ISockStreamHandler>> streams;
        };
    }
}

#endif //RTYPE_BASICSOCKSTREAMSCONTAINER_HPP