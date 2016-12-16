//
// Created by gaspar_q on 11/28/16.
//

#ifndef RTYPE_RTYPEGAMESERVER_HPP
#define RTYPE_RTYPEGAMESERVER_HPP

#include <Network/UDP/AUDPServer.hpp>
#include <SaltyEngine/SaltyBehaviour.hpp>
#include <SaltyEngine/AAssetManager.hpp>
#include "RtypeServerGameClient.hpp"
#include "Rtype/Game/Common/RtypeGameClient.hpp"

class GameManager;

namespace Rtype
{
    namespace Game
    {
        namespace Server
        {
            class RtypeGameServer : public Network::UDP::AUDPServer<Rtype::Game::Server::RtypeServerGameClient>
            {
            private:
                static const std::chrono::milliseconds   pingtimeout;

            public:
                RtypeGameServer(Network::Core::NativeSocketIOOperationDispatcher &dispatcher, const size_t maxSize = 4, u_int16_t level = 1);
                RtypeGameServer(RtypeGameServer const &ref) = delete;
                virtual ~RtypeGameServer();

            public:
                virtual bool OnDataReceived(unsigned int len);
                virtual bool OnDataSent(unsigned int len);
                virtual bool OnStart();

            public:
                template <typename Package, typename SendFunc, typename ... Args>
                void BroadCastPackage(SendFunc func, Args ... args)
                {
                    if (!clients)
                        return;
                    for (std::unique_ptr<Network::Socket::ISockStreamHandler> &curr : clients->Streams())
                    {
                        Common::RtypeGameClient *client = dynamic_cast<Common::RtypeGameClient *>(curr.get());

                        if (client)
                            client->SendPackage<Package>(func, args...);
                    }
                    WantSend();
                }

            public:
                void OnStartGame();

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

            public:
                size_t GetMaxSize() const;
                void setManager(GameManager *manager);

            private:
                GamePackageFactory factory;
                const size_t maxSize;
                uint32_t  secret;
                bool secure;

            public:
                GameManager *manager;

            private:
                u_int16_t level;
                std::unique_ptr<SaltyEngine::SceneDefault>   monsterMap;
            };
        }
    }
}

#endif //RTYPE_RTYPEGAMESERVER_HPP
