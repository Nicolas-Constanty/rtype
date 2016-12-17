//
// Created by gaspar_q on 11/28/16.
//

#include <Rtype/Game/Server/RtypeGameServer.hpp>
#include "SaltyEngine/SFML.hpp"
#include <Rtype/Game/Server/RtypeServerGameClient.hpp>
#include <Rtype/Game/Common/GameObjectID.hpp>
#include <Rtype/Game/Common/RtypeNetworkFactory.hpp>
#include <Rtype/Game/Client/GameManager.hpp>
#include <Prefabs/Player/PlayerController.hpp>

const std::chrono::milliseconds   Rtype::Game::Server::RtypeGameServer::pingtimeout(15000);

Rtype::Game::Server::RtypeGameServer::RtypeGameServer(Network::Core::NativeSocketIOOperationDispatcher &dispatcher, const size_t maxSize, u_int16_t level) :
        AUDPServer(dispatcher),
        factory(),
        maxSize(maxSize),
        secret(0),
        secure(false),
        level(level)
{
    launch = false;
}

Rtype::Game::Server::RtypeGameServer::~RtypeGameServer()
{
}

bool Rtype::Game::Server::RtypeGameServer::OnDataReceived(unsigned int)
{
    if (clients->Streams().size() > maxSize)
    {
        newclient->setErrorCode(Common::RtypeGameClient::DisconnectionCode::ROOMFULL);
        newclient->Disconnect();
        newclient = NULL;
        return false;
    }

    Rtype::Game::Common::RtypeGameClient    *client = dynamic_cast<Rtype::Game::Common::RtypeGameClient *>(newclient);

    if (client)
        client->setManager(manager);

//    SaltyEngine::GameObject *ship = new SaltyEngine::GameObject("Player " + std::to_string(newclient->getId()));
    //todo add script component to <ship> and set it to <newclient> in order to call script functions in each network callback

    //    Singleton<SaltyEngine::SaltyEngine>::Instance()-> todo add gameobject to scene
//    SendData(*factory.create<CREATEPackageGame>(ship->transform.localPosition.x, ship->transform.localPosition.y, TODEFINE, ship->GetInstanceID())); todo define correspondance id for gameobjects type
    std::cout << "Hey j'ai reçu " << buff << std::endl;
    return true;
}

bool Rtype::Game::Server::RtypeGameServer::OnDataSent(unsigned int)
{
//    std::cout << "On send des choses: " << len << std::endl;
    return true;
}

void Rtype::Game::Server::RtypeGameServer::OnReadCheck()
{
    Network::UDP::AUDPServer<Rtype::Game::Server::RtypeServerGameClient>::OnReadCheck();

    for (std::unique_ptr<Network::Socket::ISockStreamHandler> &curr : clients->Streams())
    {
        TimedUDPClient *client = dynamic_cast<TimedUDPClient *>(curr.get());

        if (client && client->pong() && client->getTimer().timeout(pingtimeout))
        {
            client->ping();
        }
//        else
//        {
//            std::cout << "Checking ping: " << client << std::endl;
//            if (client && client->pong() && pingtimer.default_timeout(pingtimeout))
//            {
//                std::cout << "===\e[32mPING\e[0m===" << std::endl;

//                pingtimer.refresh();
//            }
//            ++it;
//        }
    }
}

void Rtype::Game::Server::RtypeGameServer::setSecret(uint32_t secret)
{
    std::cout << "\x1b[33mSetting secret to\x1b[0m: " << secret << std::endl;
    this->secret = secret;
}

bool Rtype::Game::Server::RtypeGameServer::Authenticate(uint32_t secret)
{
    if (!secure)
        return true;
    return this->secret == secret;
}

void Rtype::Game::Server::RtypeGameServer::setSecure(bool security)
{
    secure = security;
}

bool Rtype::Game::Server::RtypeGameServer::OnStart()
{
    size_t i = 0;
    while (i < this->maxSize) {
        playersConnected[i] = false;
        ++i;
    }
    monsterMap = SaltyEngine::SFML::AssetManager::Instance().LoadScene("scene" + std::to_string(level));

    monsterMap->objects.sort([](std::pair<std::string, SaltyEngine::Vector2f> obj1, std::pair<std::string, SaltyEngine::Vector2f> obj2) {
        return (obj1.second.x < obj2.second.x);
    });
    std::cout << "\x1b[32mServer started\x1b[0m: maximum number of players => " << maxSize << ", secure => " << std::boolalpha << secure << std::endl;
    return true;
}

size_t Rtype::Game::Server::RtypeGameServer::GetMaxSize() const {
    return (this->maxSize);
}

void Rtype::Game::Server::RtypeGameServer::OnStartGame(Rtype::Game::Common::RtypeGameClient *client, int playerID) {
    std::vector<SaltyEngine::GameObject *> const &list = SaltyEngine::Engine::Instance().GetCurrentScene()->GetAllGameObject();
    for (SaltyEngine::GameObject *gameObject : list) {

        bool alreadySend = false;
            std::string name = gameObject->GetName();
            std::string::size_type size = name.find("(Clone)");
            if (size != std::string::npos) {
                name.erase(size, sizeof("(Clone)"));
            }
            if (gameObject->GetTag() != SaltyEngine::Layer::Tag::Untagged) {

                if (gameObject->GetTag() == SaltyEngine::Layer::Tag::Player) {
                    name = "Mate";
                    SaltyEngine::PlayerController *playerController;
                    playerController = gameObject->GetComponent<SaltyEngine::PlayerController>();
                    if (playerController) {
                        if (playerID == playerController->GetPlayerID()) {
                            name = "Player";
                        }

                        if (name == "Mate") {
                            client->SendPackage<MATEPackageGame>(&Network::UDP::AUDPConnection::SendReliable<MATEPackageGame>,
                                                                 gameObject->transform.position.x, gameObject->transform.position.y, playerController->GetPlayerID(),
                                                                 manager->gameObjectContainer.GetServerObjectID(gameObject));
                            alreadySend = true;
                        }
                    }
                }

                if (!alreadySend) {
                    client->SendPackage<CREATEPackageGame>(
                            &Network::UDP::AUDPConnection::SendReliable<CREATEPackageGame>,
                            gameObject->transform.position.x,
                            gameObject->transform.position.y,
                            RtypeNetworkFactory::GetIDFromName(name),
                            manager->gameObjectContainer.GetServerObjectID(gameObject));
                }
        }
    }


}

void Rtype::Game::Server::RtypeGameServer::OnStartGame() {
    launch = true;
    for (std::pair<std::string, SaltyEngine::Vector2f> &obj : monsterMap->objects) {
        if (obj.first != "Player") {
            SaltyEngine::GameObject *object = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate(obj.first, obj.second, 0));
            manager->gameObjectContainer.Add(GameObjectID::NewID(), object);

            this->BroadCastPackage<CREATEPackageGame>(&Network::UDP::AUDPConnection::SendReliable<CREATEPackageGame>,
                                                      object->transform.position.x,
                                                      object->transform.position.y,
                                                      RtypeNetworkFactory::GetIDFromName(obj.first),
                                                      manager->gameObjectContainer.GetServerObjectID(object));
        }
    }
}

void Rtype::Game::Server::RtypeGameServer::setManager(GameManager *manager)
{
    std::cout << "=====> Setting manager in RtypeGameServer" << std::endl;
    this->manager = manager;
}

std::map<int, bool> const &Rtype::Game::Server::RtypeGameServer::GetConnectedPlayers() const {
    return (playersConnected);
}

int Rtype::Game::Server::RtypeGameServer::PlayerID() {
    size_t i = 0;
    while (i < GetMaxSize()) {
        std::map<int, bool>::iterator it = playersConnected.find(static_cast<int>(i));
        if (it != playersConnected.end()) {
            if (!it->second) {
                it->second = true;
                return (it->first);
            }
        }
        ++i;
    }
    return (-1);
}

void Rtype::Game::Server::RtypeGameServer::DisconnectConnectedPlayer(int playerID) {
    std::cout << "DISCONNECT player ID == " << playerID << std::endl;
    std::map<int, bool>::iterator it = playersConnected.find(playerID);
    if (it != playersConnected.end()) {
        it->second = false;
    }
}

bool Rtype::Game::Server::RtypeGameServer::IsLaunch() const {
    return launch;
}

//GameObjectContainer &Rtype::Game::Server::RtypeGameServer::GameObjectContainer() {
//    return gameObjectContainer;
//}
