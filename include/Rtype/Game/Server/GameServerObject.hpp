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
                GameServerObject(SaltyEngine::GameObject *obj, const uint16_t port = 4242, const int maxClient = 0, const uint32_t secret = 0);
                ~GameServerObject();

            public:
                void Start();
                void Update();

            private:
                const uint32_t secret;
                const uint16_t port;
                Rtype::Game::Server::RtypeGameServer    *server;
                Network::Core::NativeSocketIOOperationDispatcher    dispatcher;
            };
        }
    }
}

#endif //RTYPE_GAMESERVEROBJECT_HPP
