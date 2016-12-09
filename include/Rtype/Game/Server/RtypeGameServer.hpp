//
// Created by gaspar_q on 11/28/16.
//

#ifndef RTYPE_RTYPEGAMESERVER_HPP
#define RTYPE_RTYPEGAMESERVER_HPP

#include <Network/UDP/AUDPServer.hpp>
#include <SaltyEngine/SaltyBehaviour.hpp>
#include "RtypeServerGameClient.hpp"

namespace Rtype
{
    namespace Game
    {
        namespace Server
        {
            class RtypeGameServer : public Network::UDP::AUDPServer<Rtype::Game::Server::RtypeServerGameClient>
            {
            public:
                RtypeGameServer(Network::Core::NativeSocketIOOperationDispatcher &dispatcher, const size_t maxSize = 4);
                RtypeGameServer(RtypeGameServer const &ref) = delete;
                virtual ~RtypeGameServer();

            public:
                virtual bool OnDataReceived(unsigned int len);
                virtual bool OnDataSent(unsigned int len);
                virtual bool OnStart();

            public:
                virtual void OnReadCheck();

            public:
                void setSecret(uint32_t secret);
                bool Authenticate(uint32_t secret);

            public:
                void setSecure(bool security = true);

            public:
                template <typename T, class ...Args>
                T *create(Args ...args) {
                    return factory.create<T>(args...);
                }

            private:
                GamePackageFactory factory;
                const size_t maxSize;
                uint32_t  secret;
                bool secure;
            };
        }
    }
}

#endif //RTYPE_RTYPEGAMESERVER_HPP
