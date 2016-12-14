//
// Created by gaspar_q on 12/6/16.
//

#ifndef RTYPE_GAMESERVEROBJECT_HPP
#define RTYPE_GAMESERVEROBJECT_HPP

#include <SaltyEngine/SaltyBehaviour.hpp>
#include "RtypeGameServer.hpp"

namespace Rtype
{
    namespace Game
    {
        namespace Server
        {
            class GameServerObject : public SaltyEngine::SaltyBehaviour
            {
            public:
                GameServerObject(SaltyEngine::GameObject *obj, const uint16_t port = 4242, const size_t maxClient = 0, const uint32_t secret = 0, const uint16_t map = 0);
                ~GameServerObject();

            public:
                void Start();
                void Update();

            public:
                template <typename Package, typename SendFunc, typename ... Args>
                void BroadCastPackage(SendFunc func, Args ... args) {
                    this->server->BroadCastPackage<Package>(func, args...);
                }

            private:
                const uint32_t secret;
                const uint16_t port;
                const uint16_t map;
                Rtype::Game::Server::RtypeGameServer    *server;
                Network::Core::NativeSocketIOOperationDispatcher    dispatcher;
                bool running;
            };
        }
    }
}

#endif //RTYPE_GAMESERVEROBJECT_HPP
