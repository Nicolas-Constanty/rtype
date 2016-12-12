//
// Created by gaspar_q on 12/6/16.
//

#include <Protocol/Game/ProtocolPrintGamePackage.hpp>
#include <Rtype/Game/Server/RtypeServerGameClient.hpp>
#include <Rtype/Game/Server/RtypeGameServer.hpp>
#include <SaltyEngine/Input/VirtualInutManager.hpp>
#include <Rtype/Game/Client/SpaceShipController.hpp>
#include <Rtype/Game/Server/GameObjectID.hpp>
#include "Rtype/Game/Common/GameObjectContainer.hpp"

Rtype::Game::Server::RtypeServerGameClient::RtypeServerGameClient(Network::Core::NativeSocketIOOperationDispatcher &dispatcher) :
        RtypeGameClient(dispatcher),
        server1(NULL),
        pingSecret(-1),
        pingTime(),
        id(0)
{

}

Rtype::Game::Server::RtypeServerGameClient::RtypeServerGameClient(const Rtype::Game::Server::RtypeServerGameClient &ref) :
    RtypeGameClient(ref),
    server1(NULL),
    pingSecret(-1),
    pingTime(),
    id(0)
{

}

Rtype::Game::Server::RtypeServerGameClient::~RtypeServerGameClient()
{

}

void Rtype::Game::Server::RtypeServerGameClient::onGetSTATUSPackage(STATUSPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    //todo packet coffee resolve at the end
}

void Rtype::Game::Server::RtypeServerGameClient::onGetPINGPackage(PINGPackageGame const &pack)
{
//    std::cout << pack << std::endl;
    reply = false;
    OnDiscoveringPackage(pack);
//    std::cout << "pingSecret == " << pingSecret << " pack.secret == " << pack.secret << " pingSecret == " << pingSecret << std::endl;
    if (pingSecret != -1 && pack.secret != pingSecret)
    {
        connected = false;
//        std::cout << "Disconnection" << std::endl;
    }
    else
    {
        pingSecret = -1;
//        std::cout << "\e[32mYou have been ponged\e[0m: " << pingSecret << std::endl;
    }
}

void Rtype::Game::Server::RtypeServerGameClient::onGetAUTHENTICATEPackage(AUTHENTICATEPackageGame const &pack)
{
    reply = false;
    std::cout << "pack: " << pack << std::endl;
    OnDiscoveringPackage(pack);
    if (!server1->Authenticate(pack.secret))
    {
        //notification de déconnection au client
        connected = false;
    }
    else
    {
        connected = true;

        //creation of a new player
//        CREATEPackageGame   *player = server1->create<CREATEPackageGame>();
        //todo Instantiate player in engine with an object id
        //todo player->ID = correspondance prefab
        //todo player->objectID = correspondance gameobject engine
//        player->objectID = 5;

        //notify to <this> player that he is authenticated
        SendPackage<AUTHENTICATEPackageGame>(&Network::UDP::AUDPConnection::SendReliable<AUTHENTICATEPackageGame>, pack.secret, 5);


        // create a new player on the engine
        if (clients->Streams().size() == this->server1->GetMaxSize()) {
            for (std::unique_ptr<Network::Socket::ISockStreamHandler> &curr : clients->Streams()) {
                RtypeServerGameClient *client = dynamic_cast<RtypeServerGameClient *>(curr.get());
                client->StartDisplayInformation();
            }
        }

        //ping <this> player in order to made him survive
        ping();
        if (serverStream)
            serverStream->WantSend();
    }
}

/**
 * @brief Called when client send Create Package. We don't even answer him because don't have to send this packet
 * @param pack The packet received
 */
void Rtype::Game::Server::RtypeServerGameClient::onGetCREATEPackage(CREATEPackageGame const &pack)
{
    //client can't create an object
    reply = false;
    OnDiscoveringPackage(pack);
}

void Rtype::Game::Server::RtypeServerGameClient::onGetBEAMPackage(BEAMPackageGame const &pack)
{
    OnDiscoveringPackage(pack);

//    todo if (okay on gameside)
//    {
//        BroadcastReliable(*server1->create<BEAMPackageGame>(pack.objectID));
//    }
//    else
//    {
//        SendReliable(*server1->create<FAILUREPackageGame>(pack.purpose, pack.sequenceID));
//    }
}

void Rtype::Game::Server::RtypeServerGameClient::onGetSHOTPackage(SHOTPackageGame const &pack)
{
    OnDiscoveringPackage(pack);

//    todo if (okay on gameside)
//    {
//        BroadcastReliable(*server1->create<SHOTPackageGame>(pack.objectID));
//    }
//    else
//    {
//        SendReliable(*server1->create<FAILUREPackageGame>(pack.purpose, pack.sequenceID));
//    }
}

void Rtype::Game::Server::RtypeServerGameClient::onGetDIEPackage(DIEPackageGame const &pack)
{
    reply = false;
    OnDiscoveringPackage(pack);
}

void Rtype::Game::Server::RtypeServerGameClient::onGetTAKEPackage(TAKEPackageGame const &pack)
{
    OnDiscoveringPackage(pack);

//    todo if (okay on gameside)
//    {
//        BroadcastReliable(*server1->create<TAKEPackageGame>(pack.objectID));
//    }
//    else
//    {
//        SendReliable(*server1->create<FAILUREPackageGame>(pack.purpose, pack.sequenceID));
//    }
}

void Rtype::Game::Server::RtypeServerGameClient::onGetDROPPackage(DROPPackageGame const &pack)
{
    OnDiscoveringPackage(pack);

//    todo if (okay on gameside)
//    {
//        BroadcastReliable(*server1->create<DROPPackageGame>(pack.objectID));
//    }
//    else
//    {
//        SendReliable(*server1->create<FAILUREPackageGame>(pack.purpose, pack.sequenceID));
//    }
}

void Rtype::Game::Server::RtypeServerGameClient::onGetMOVEPackage(MOVEPackageGame const &pack)
{
    std::cout << pack << std::endl;
    OnDiscoveringPackage(pack);
    for (std::unique_ptr<Network::Socket::ISockStreamHandler> &curr : clients->Streams())
    {
        if (curr.get() != this)
        {
            Rtype::Game::Server::RtypeServerGameClient *receiver = dynamic_cast<Rtype::Game::Server::RtypeServerGameClient *>(curr.get());

            if (receiver)
                receiver->SendPackage<MOVEPackageGame>(&Network::Core::BasicConnection::SendData<MOVEPackageGame>, pack.posX, pack.posY, pack.objectID);
        }
    }
    if (serverStream)
        serverStream->WantSend();
//    todo if (okay on gameside)
//    {
//        Broadcast(*server1->create<MOVEPackageGame>(pack.posX, pack.posY, pack.objectID));
//    }
//    else
//    {
//        SendReliable(*server1->create<FAILUREPackageGame>(pack.purpose, pack.sequenceID));
//    }
}

void Rtype::Game::Server::RtypeServerGameClient::onGetLAUNCHPackage(LAUNCHPackageGame const &pack)
{
    OnDiscoveringPackage(pack);

//    todo if (okay on gameside)
//    {
//        BroadcastReliable(*server1->create<LAUNCHPackageGame>(pack.objectID));
//    }
//    else
//    {
//        SendReliable(*server1->create<FAILUREPackageGame>(pack.purpose, pack.sequenceID));
//    }
}

void Rtype::Game::Server::RtypeServerGameClient::onGetREBORNPackage(REBORNPackageGame const &pack)
{
    reply = false;
    OnDiscoveringPackage(pack);
}

void Rtype::Game::Server::RtypeServerGameClient::onGetFAILUREPackage(FAILUREPackageGame const &pack)
{
    reply = false;
    OnDiscoveringPackage(pack);
}

void Rtype::Game::Server::RtypeServerGameClient::onGetINPUTPackage(INPUTPackageGame const &pack)
{
//    std::cout << pack << std::endl;
    OnDiscoveringPackage(pack);
    for (std::unique_ptr<Network::Socket::ISockStreamHandler> &curr : clients->Streams())
    {
        if (curr.get() != this)
        {
            Rtype::Game::Server::RtypeServerGameClient *receiver = dynamic_cast<Rtype::Game::Server::RtypeServerGameClient *>(curr.get());

            if (receiver)
                receiver->SendPackage<INPUTPackageGame>(&Network::Core::BasicConnection::SendData<INPUTPackageGame>, pack.axes, pack.value);
        }
    }
    if (serverStream)
        serverStream->WantSend();
    SaltyEngine::Input::VirtualInputManager::SetAxis(pack.axes, pack.value);
}

bool Rtype::Game::Server::RtypeServerGameClient::OnStart()
{
    server1 = dynamic_cast<Rtype::Game::Server::RtypeGameServer *>(serverStream);
    if (!server1)
    {
        Disconnect();
        return false;
    }
    if (clients)
        id = static_cast<int>(clients->Streams().size() + 1);
    return true;
}

int Rtype::Game::Server::RtypeServerGameClient::getId() const
{
    return id;
}

bool Rtype::Game::Server::RtypeServerGameClient::timedout() const
{
    return std::chrono::steady_clock::now() - pingTime > Rtype::Game::Server::RtypeServerGameClient::timeout;
}

void Rtype::Game::Server::RtypeServerGameClient::ping()
{
    pingSecret = rand();
    pingTime = std::chrono::steady_clock::now();
//    SendReliable(*server1->create<PINGPackageGame>(pingSecret));
    SendPackage<PINGPackageGame>(&Network::UDP::AUDPConnection::SendReliable<PINGPackageGame>, pingSecret);
    if (serverStream)
        serverStream->WantSend();
}

bool Rtype::Game::Server::RtypeServerGameClient::pong() const
{
    return pingSecret == -1;
}

void Rtype::Game::Server::RtypeServerGameClient::StartDisplayInformation() {
    SaltyEngine::GameObject	*player;

    player = dynamic_cast<SaltyEngine::GameObject*>(SaltyEngine::Object::Instantiate());
    // player->AddComponent<SaltyEngine::SpaceShipController>();

    *SaltyEngine::SaltyEngine::Instance().GetCurrentScene() << player;

    server1->gameObjectContainer.Add(GameObjectID::NewID(), player);

    //notify to all players the creation of a player
    this->SendPackage<CREATEPackageGame>(&Network::UDP::AUDPConnection::SendReliable<CREATEPackageGame>, 100, 100, 0, server1->gameObjectContainer.GetServerObjectID(player));

    //notify to <this> player to create existing players
    for (std::unique_ptr<Network::Socket::ISockStreamHandler> &curr : clients->Streams())
    {
        Rtype::Game::Common::RtypeGameClient *client = dynamic_cast<Rtype::Game::Common::RtypeGameClient *>(curr.get());

        if (client && client != this)
        {
            client->SendPackage<CREATEPackageGame>(&Network::UDP::AUDPConnection::SendReliable<CREATEPackageGame>, 100, 100, 1, server1->gameObjectContainer.GetServerObjectID(player));
//                SendReliable(*server1->create<CREATEPackageGame>());
        }
    }
}
