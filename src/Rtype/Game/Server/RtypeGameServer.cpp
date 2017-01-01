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

const std::chrono::milliseconds   Rtype::Game::Server::RtypeGameServer::pingtimeout(2500);

Rtype::Game::Server::RtypeGameServer::RtypeGameServer(Network::Core::NativeSocketIOOperationDispatcher &dispatcher, const size_t maxSize, const std::string &level) :
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
    return true;
}

bool Rtype::Game::Server::RtypeGameServer::OnDataSent(unsigned int)
{
    return true;
}

void Rtype::Game::Server::RtypeGameServer::OnReadCheck()
{
    Network::UDP::AUDPServer<Rtype::Game::Server::RtypeServerGameClient>::OnReadCheck();

    for (Network::Socket::ISockStreamHandler *curr : clients->Streams())
    {
        TimedUDPClient *client = dynamic_cast<TimedUDPClient *>(curr);

        if (client && client->pong() && client->getTimer().timeout(pingtimeout))
        {
            client->ping();
        }
    }
}

void Rtype::Game::Server::RtypeGameServer::setSecret(uint32_t secret)
{
    Debug::PrintSuccess("Setting secret to: " + std::to_string(secret));
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
        playersConnected[(int)i] = false;
        ++i;
    }
    Debug::PrintSuccess("Server started: maximum number of players => " + std::to_string(maxSize) + ", secure => " + (secure ? "true" : "false"));
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
        if (gameObject->GetTag() != SaltyEngine::Layer::Tag::Untagged
            && gameObject->GetTag() != SaltyEngine::Layer::Tag::BulletPlayer) {

            if (gameObject->GetTag() == SaltyEngine::Layer::Tag::Player) {
                name = "Mate";
                SaltyEngine::PlayerController *playerController;
                playerController = gameObject->GetComponent<SaltyEngine::PlayerController>();
                if (playerController) {
                    if (playerID == playerController->GetPlayerID()) {
                        name = "Player";
                        this->BroadCastPackage<RECONNECTPackageGame>(&Network::UDP::AUDPConnection::SendReliable<RECONNECTPackageGame>,
                                                                     static_cast<unsigned short>(playerID));
                    }

                    if (name == "Mate") {
                        client->SendPackage<MATEPackageGame>(
                                &Network::UDP::AUDPConnection::SendReliable<MATEPackageGame>,
                                gameObject->transform.GetPosition().x, gameObject->transform.GetPosition().y,
                                playerController->GetPlayerID(),
                                manager->gameObjectContainer.GetServerObjectID(gameObject));
                        alreadySend = true;
                    }
                }
            }

            if (!alreadySend) {
                client->SendPackage<CREATEPackageGame>(
                        &Network::UDP::AUDPConnection::SendReliable<CREATEPackageGame>,
                        gameObject->transform.GetPosition().x,
                        gameObject->transform.GetPosition().y,
                        RtypeNetworkFactory::GetIDFromName(name),
                        manager->gameObjectContainer.GetServerObjectID(gameObject));
            }
        }
    }
}


//}

void Rtype::Game::Server::RtypeGameServer::OnStartGame() {
//    launch = true;
//    for (std::pair<std::string, SaltyEngine::Vector2f> &obj : monsterMap->objects) {
//        std::cout << obj.first << std::endl;
//        if (obj.first != "Player") {
//            SaltyEngine::GameObject *object = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate(obj.first, obj.second, 0));
//            manager->gameObjectContainer.Add(GameObjectID::NewID(), object);
//        }
//    }
}

void Rtype::Game::Server::RtypeGameServer::setManager(GameManager *manager)
{
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
    Debug::Print("DISCONNECT player ID == " + std::to_string(playerID));
    std::map<int, bool>::iterator it = playersConnected.find(playerID);
    if (it != playersConnected.end()) {
        it->second = false;
    }
}

bool Rtype::Game::Server::RtypeGameServer::IsLaunch() const {
    return launch;
}

void Rtype::Game::Server::RtypeGameServer::SetLaunch(bool lau) {
    this->launch = lau;
}

//GameObjectContainer &Rtype::Game::Server::RtypeGameServer::GameObjectContainer() {
//    return gameObjectContainer;
//}
