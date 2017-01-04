//
// Created by gaspar_q on 12/6/16.
//

#ifndef RTYPE_GAMESERVEROBJECT_HPP
#define RTYPE_GAMESERVEROBJECT_HPP

#include <SaltyEngine/SaltyBehaviour.hpp>
#include "RtypeGameServer.hpp"

class GameManager;

namespace Rtype
{
    namespace Game
    {
        namespace Server
        {
            class PREF_EXPORT GameServerObject : public SaltyEngine::SaltyBehaviour
            {
            public:
                GameServerObject(SaltyEngine::GameObject *obj, const uint16_t port = 4242, const size_t maxClient = 0, const uint32_t secret = 0, const std::string &map = 0);
                ~GameServerObject();

            public:
                void Start();
                void Update();

            public:
                template <typename Package, typename SendFunc, typename ... Args>
                void BroadCastPackage(SendFunc func, Args ... args) {
                    this->server->BroadCastPackage<Package>(func, args...);
                }

//                Rtype::Game::Server::RtypeGameServer    *GetClient

            public:
                Rtype::Game::Server::RtypeGameServer *Server() {
                    return (server);
                }

                const std::string &GetLevel() const {
                    return (map);
                }

                void SetLevel(std::string const &level) {
                    this->map = level;
                }

                SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject *const obj) override;

            private:
                const uint32_t secret;
                const size_t m_maxClient;
                const uint16_t port;
                std::string map;
                Rtype::Game::Server::RtypeGameServer    *server;
                Network::Core::NativeSocketIOOperationDispatcher    dispatcher;
                GameManager *manager;
                bool running;
            };
        }
    }
}

#endif //RTYPE_GAMESERVEROBJECT_HPP
