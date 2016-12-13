//
// Created by gaspar_q on 11/28/16.
//

#include <Rtype/Game/Server/RtypeGameServer.hpp>
#include "SaltyEngine/SFML.hpp"
#include <Rtype/Game/Server/RtypeServerGameClient.hpp>
#include <Rtype/Game/Common/GameObjectID.hpp>
#include <Rtype/Game/Common/RtypeNetworkFactory.hpp>

Rtype::Game::Server::RtypeGameServer::RtypeGameServer(Network::Core::NativeSocketIOOperationDispatcher &dispatcher, const size_t maxSize, u_int16_t level) :
        AUDPServer(dispatcher),
        factory(),
        maxSize(maxSize),
        secret(0),
        secure(false),
        gameObjectContainer(),
        level(level)
{

}

Rtype::Game::Server::RtypeGameServer::~RtypeGameServer()
{

}

bool Rtype::Game::Server::RtypeGameServer::OnDataReceived(unsigned int)
{
    if (clients->Streams().size() > maxSize)
    {
        std::cout << "Room full" << std::endl;
        newclient->Disconnect();
        return false;
    }

//    SaltyEngine::GameObject *ship = new SaltyEngine::GameObject("Player " + std::to_string(newclient->getId()));
    //todo add script component to <ship> and set it to <newclient> in order to call script functions in each network callback

    //    Singleton<SaltyEngine::SaltyEngine>::Instance()-> todo add gameobject to scene
//    SendData(*factory.create<CREATEPackageGame>(ship->transform.localPosition.x, ship->transform.localPosition.y, TODEFINE, ship->GetInstanceID())); todo define correspondance id for gameobjects type
    std::cout << "Hey j'ai reçu " << buff << std::endl;
    return true;
}

bool Rtype::Game::Server::RtypeGameServer::OnDataSent(unsigned int len)
{
//    std::cout << "On send des choses: " << len << std::endl;
    return true;
}

void Rtype::Game::Server::RtypeGameServer::OnReadCheck()
{
    Network::UDP::AUDPServer<Rtype::Game::Server::RtypeServerGameClient>::OnReadCheck();
  //  std::cout << "ALOS" << std::endl;
//    for (std::list<std::unique_ptr<Network::Socket::ISockStreamHandler>>::iterator it = clients->Streams().begin(); it != clients->Streams().end();)
//    {
//        Rtype::Game::Server::RtypeServerGameClient *client = dynamic_cast<Rtype::Game::Server::RtypeServerGameClient *>(it->get());

//        if (client && client->timedout())
//        {
//            client->Disconnect();
//            it = clients->Streams().begin();
//        }
//        else
//        {
//            std::cout << "Checking ping: " << client << std::endl;
//            if (client && client->pong())
//            {
//                std::cout << "===\e[32mPING\e[0m===" << std::endl;
//                client->ping();
//            }
//            ++it;
//        }
//    }
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
    monsterMap = SaltyEngine::SFML::AssetManager::Instance().LoadScene("scene" + std::to_string(level));
    monsterMap.sort([](std::pair<std::string, SaltyEngine::Vector2f> obj1, std::pair<std::string, SaltyEngine::Vector2f> obj2) {
        return (obj1.second.x < obj2.second.x);
    });
    std::cout << "\x1b[32mServer started\x1b[0m: maximum number of players => " << maxSize << ", secure => " << std::boolalpha << secure << std::endl;
    return true;
}

size_t Rtype::Game::Server::RtypeGameServer::GetMaxSize() const {
    return (this->maxSize);
}



void Rtype::Game::Server::RtypeGameServer::OnStartGame() {
    for (std::pair<std::string, SaltyEngine::Vector2f> &obj : monsterMap) {
        if (obj.first != "Player") {
            SaltyEngine::GameObject *object = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate(obj.first, obj.second, 0));
            gameObjectContainer.Add(GameObjectID::NewID(), object);

            this->BroadCastPackage<CREATEPackageGame>(&Network::UDP::AUDPConnection::SendReliable<CREATEPackageGame>,
                                                      object->transform.position.x,
                                                      object->transform.position.y,
                                                      RtypeNetworkFactory::GetIDFromName(obj.first),
                                                      gameObjectContainer.GetServerObjectID(object));
            /*this-><CREATEPackageGame>();*/
        }
    }
}

//GameObjectContainer &Rtype::Game::Server::RtypeGameServer::GameObjectContainer() {
//    return gameObjectContainer;
//}
