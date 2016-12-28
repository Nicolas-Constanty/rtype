//
// Created by gaspar_q on 11/26/16.
//

#ifndef RTYPE_BASICSOCKSTREAMSCONTAINER_HPP
#define RTYPE_BASICSOCKSTREAMSCONTAINER_HPP

#include <memory>
#include <list>
#include "ISockStreamHandlersContainer.hpp"

namespace Network
{
    namespace Socket
    {
        /**
         * @brief Abstraction of a socket stream handler container
         */
        class PREF_EXPORT BasicSockStreamsContainer : public ISockStreamHandlersContainer
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

            virtual std::list<Socket::ISockStreamHandler *> &Streams();

        private:
            std::list<ISockStreamHandler *> streams;
        };
    }
}

#endif //RTYPE_BASICSOCKSTREAMSCONTAINER_HPP
