//
// Created by gaspar_q on 12/6/16.
//

#include <Protocol/Game/ProtocolPrintGamePackage.hpp>
#include <Rtype/Game/Server/RtypeServerGameClient.hpp>
#include <Rtype/Game/Server/RtypeGameServer.hpp>
#include <Rtype/Game/Client/SpaceShipController.hpp>
#include <Rtype/Game/Common/GameObjectID.hpp>
#include <Prefabs/Player/PlayerController.hpp>
#include <Rtype/Game/Client/GameManager.hpp>
#include <Rtype/Game/Common/RtypeNetworkFactory.hpp>
#include "SaltyEngine/Vector2.hpp"
#include "Rtype/Game/Common/GameObjectContainer.hpp"
#include <Prefabs/Pod/PodController.hpp>
#include <Prefabs/Missile/Laser/LaserController.hpp>

Rtype::Game::Server::RtypeServerGameClient::RtypeServerGameClient(Network::Core::NativeSocketIOOperationDispatcher &dispatcher) :
        RtypeGameClient(dispatcher),
        server1(NULL),
        pingSecret(-1),
        id(0),
        power(0),
        __playerID(0)
{

}

Rtype::Game::Server::RtypeServerGameClient::RtypeServerGameClient(const Rtype::Game::Server::RtypeServerGameClient &ref) :
    RtypeGameClient(ref),
    server1(NULL),
    pingSecret(-1),
    id(0),
    power(0),
    __playerID(0)
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
	Debug::PrintSuccess("Ponged");
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
//    std::cout << "pack: " << pack << std::endl;
    OnDiscoveringPackage(pack);
    if (!server1->Authenticate(pack.secret))
    {
        //notification de déconnection au client
        connected = false;
    }
    else
    {
        bool check = false;
        connected = true;

        __playerID = server1->PlayerID();
        if (__playerID == -1) {
            __playerID = 0;
        }
        playerID = static_cast<unsigned char>(__playerID);
//        std::cout << "PLAYERID== " << __playerID << std::endl;

        SendPackage<AUTHENTICATEPackageGame>(&Network::UDP::AUDPConnection::SendReliable<AUTHENTICATEPackageGame>, pack.secret, __playerID);

        // create a new player on the engine
        if (clients->Streams().size() == this->server1->GetMaxSize()) {
            if (!server1->IsLaunch()) {
                for (std::unique_ptr<Network::Socket::ISockStreamHandler> &curr : clients->Streams()) {
                    RtypeServerGameClient *client = dynamic_cast<RtypeServerGameClient *>(curr.get());
                    client->StartDisplayInformation();
                }
            }

            if (!server1->IsLaunch()) {
                server1->OnStartGame();
                gameManager->StartTheGame();
                check = true;
            }
//            else
//                server1->OnStartGame(this, __playerID);
//            std::cout << "oui oui oui" << std::endl;
        }
        if (server1->IsLaunch() && !check) {
            server1->OnStartGame(this, __playerID);
        }

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
    std::cout << pack << std::endl;
    OnDiscoveringPackage(pack);
}

void Rtype::Game::Server::RtypeServerGameClient::onGetBEAMPackage(BEAMPackageGame const &pack)
{
    std::cout << pack << std::endl;
    OnDiscoveringPackage(pack);

    SaltyEngine::GameObject *gameObject;

    if ((gameObject = gameManager->gameObjectContainer[pack.objectID])) {
        SaltyEngine::PlayerController *playerController = gameObject->GetComponent<SaltyEngine::PlayerController>();
        if (playerController) {

            SaltyEngine::Vector pos = gameObject->transform.position;
            pos.x += 30;
            SaltyEngine::GameObject *beam = dynamic_cast<SaltyEngine::GameObject*>(SaltyEngine::Object::Instantiate("Beam", pos));

            playerController->beamServerID = gameManager->gameObjectContainer.Add(GameObjectID::NewID(), beam);

//            std::cout << "ID SERVER ==" << gameManager->gameObjectContainer.GetServerObjectID(gameObject) << std::endl;

            for (std::unique_ptr<Network::Socket::ISockStreamHandler> &curr : clients->Streams())
            {
                if (curr.get() != this)
                {
                    Rtype::Game::Server::RtypeServerGameClient *receiver = dynamic_cast<Rtype::Game::Server::RtypeServerGameClient *>(curr.get());

                    if (receiver)
                        receiver->SendPackage<BEAMPackageGame>(&Network::UDP::AUDPConnection::SendReliable<BEAMPackageGame>,
                                                               pack.objectID);
                }
            }

//            this->BroadCastPackage<CREATEPackageGame>(
//                    &Network::UDP::AUDPConnection::SendReliable<CREATEPackageGame>,
//                    gameObject->transform.position.x,
//                    gameObject->transform.position.y,
//                    RtypeNetworkFactory::GetIDFromName("Beam"),
//                    playerController->beamServerID);
            playerController->beamShot = beam;
            playerController->OnBeamAction();

        }

    }
}

void Rtype::Game::Server::RtypeServerGameClient::onGetSHOTPackage(SHOTPackageGame const &pack)
{
//    std::cout << "ENTER" << std::endl;
    OnDiscoveringPackage(pack);

    SaltyEngine::GameObject *gameObject;

    std::cout << pack << std::endl;

    if ((gameObject = gameManager->gameObjectContainer[pack.objectID])) {

        SaltyEngine::PlayerController *playerController = gameObject->GetComponent<SaltyEngine::PlayerController>();

        if (playerController) {
            int power = playerController->OnShotAction();
            SaltyEngine::GameObject *laser = dynamic_cast<SaltyEngine::GameObject *>(::SaltyEngine::Instantiate("Laser", gameObject->transform.position));
//            int serverid = gameManager->gameObjectContainer.Add(GameObjectID::NewID(), laser);
            LaserController *laserController;

//            this->BroadCastPackage<SHOTPackageGame>(
//                    &Network::UDP::AUDPConnection::SendReliable<SHOTPackageGame>,
//                    serverid, power,
//                    pack.objectID);

            for (std::unique_ptr<Network::Socket::ISockStreamHandler> &curr : clients->Streams())
            {
                if (curr.get() != this)
                {
                    Rtype::Game::Server::RtypeServerGameClient *receiver = dynamic_cast<Rtype::Game::Server::RtypeServerGameClient *>(curr.get());

                    if (receiver)
                        receiver->SendPackage<SHOTPackageGame>(&Network::UDP::AUDPConnection::SendReliable<SHOTPackageGame>,
                                                                pack.objectID, power,
                                                                0, gameObject->transform.position.x, gameObject->transform.position.y);
                }
            }

//            for (std::unique_ptr<Network::Socket::ISockStreamHandler> &curr : clients->Streams())
//            {
//                RtypeGameClient *client = dynamic_cast<Rtype::Game::Client::RtypeGameClient *>(curr.get());
//
//                if (client)
//                    client->SendPackage<SHOTPackageGame>(&Network::UDP::AUDPConnection::SendReliable<SHOTPackageGame>,
//                                                         serverid, power,
//                                                         pack.objectID);
//            }

            if ((laserController = laser->GetComponent<LaserController>())) {
                laserController->Power(power);

                laserController->AddPlayerController(playerController);
                if (playerController->beamShot) {
                    this->BroadCastPackage<DIEPackageGame>(&Network::UDP::AUDPConnection::SendReliable<DIEPackageGame>,
                                                           playerController->beamServerID);
//                    BroadcastPackage<DIEPackageGame>(getManager()->gameObjectContainer.GetServerObjectID(beamShot));
                    SaltyEngine::Object::Destroy(playerController->beamShot);
                    playerController->beamShot = NULL;
                }
            }
            playerController->IncIdShot();
        }
    }
//    std::cout << "JE SORS" << std::endl;
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

void Rtype::Game::Server::RtypeServerGameClient::onGetCALLPackage(CALLPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    if (gameManager->gameObjectContainer[pack.playerObjectID] == gameManager->GetPlayer(playerID))
    {
        SaltyEngine::GameObject *object = gameManager->gameObjectContainer[pack.objectID];

        if (object)
        {
            PodController   *podController = object->GetComponent<PodController>();

            if (podController && podController->isAttachedTo(gameManager->GetPlayer(playerID)))
            {
                podController->Call(podController->getAttachedPlayer());
            }
        }
    }
//    todo if (okay on gameside)
//    {
//        BroadcastReliable(*server1->create<CALLPackageGame>(pack.objectID));
//    }
//    else
//    {
//        SendReliable(*server1->create<FAILUREPackageGame>(pack.purpose, pack.sequenceID));
//    }
}

void Rtype::Game::Server::RtypeServerGameClient::onGetMOVEPackage(MOVEPackageGame const &pack)
{
//    std::cout << pack << std::endl;
    OnDiscoveringPackage(pack);

    SaltyEngine::GameObject *gameObject;

    if ((gameObject = gameManager->gameObjectContainer[pack.objectID])) {
        gameObject->transform.SetPosition(SaltyEngine::Vector(pack.posX, pack.posY));
    }

    for (std::unique_ptr<Network::Socket::ISockStreamHandler> &curr : clients->Streams())
    {
        if (curr.get() != this)
        {
            Rtype::Game::Server::RtypeServerGameClient *receiver = dynamic_cast<Rtype::Game::Server::RtypeServerGameClient *>(curr.get());

            if (receiver) {
//                std::cout << " Rtype::Game::Server::RtypeServerGameClient::onGetMOVEPackage(MOVEPackageGame const &pack) OBJECTID IS == " << pack.objectID << std::endl;
                receiver->SendPackage<MOVEPackageGame>(&Network::Core::BasicConnection::SendData<MOVEPackageGame>,
                                                       pack.posX, pack.posY, pack.objectID);
            }
        }
    }
//    if (serverStream)
//        serverStream->WantSend();


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

    std::cout << "Receiving launch: " << pack << std::endl;
    if (gameManager->gameObjectContainer[pack.playerObjectID] == gameManager->GetPlayer(playerID))
    {
        SaltyEngine::GameObject *object = gameManager->gameObjectContainer[pack.objectID];
        PodController   *controller;

        std::cout << "Right player: obj: " << object << std::endl;
        if (object)
        {
            controller = object->GetComponent<PodController>();
            std::cout << "controller:  " << controller << std::endl;
            if (controller && controller->isAttachedTo(gameManager->GetPlayer(playerID)))
            {
                std::cout << "Attached" << std::endl;
                controller->getAttachedPlayer()->Launch();
            }
        }
    }
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
//    SaltyEngine::Input::VirtualInputManager::SetAxis(pack.axes, pack.value);
}

void Rtype::Game::Server::RtypeServerGameClient::onGetDISCONNECTPackage(DISCONNECTPackageGame const &pack)
{
    Rtype::Game::Common::RtypeGameClient::onGetDISCONNECTPackage(pack);
    connected = false;
}


void Rtype::Game::Server::RtypeServerGameClient::onGetENEMYSHOTPackage(ENEMYSHOTPackageGame const &pack) {
    std::cout << pack << std::endl;
}


void Rtype::Game::Server::RtypeServerGameClient::onGetUPGRADEPackage(UPGRADEPackageGame const &pack)
{
    //client can't say to server when upgrade pod
    OnDiscoveringPackage(pack);
}

void Rtype::Game::Server::RtypeServerGameClient::onGetGAMEOVERPackage(GAMEOVERPackageGame const &game) {

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

void Rtype::Game::Server::RtypeServerGameClient::ping()
{
    pingSecret = rand();
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

    int x = 100;
    int y = 100;

    if ((player = dynamic_cast<SaltyEngine::GameObject*>(SaltyEngine::Object::Instantiate("Player", SaltyEngine::Vector(x, y)))) == NULL)
    {
        throw std::runtime_error("player is NULL / pb Asset");
    }
    SaltyEngine::PlayerController *playerController = player->GetComponent<SaltyEngine::PlayerController>();
    if (playerController) {
        playerController->SetPlayerID(__playerID);
        gameManager->addPlayer(player, static_cast<unsigned char>(__playerID));
    }

    gameManager->gameObjectContainer.Add(GameObjectID::NewID(), player);

    this->SendPackage<CREATEPackageGame>(&Network::UDP::AUDPConnection::SendReliable<CREATEPackageGame>,
                                         player->transform.position.x, player->transform.position.y, 0, gameManager->gameObjectContainer.GetServerObjectID(player));

    for (std::unique_ptr<Network::Socket::ISockStreamHandler> &curr : clients->Streams())
    {
        Rtype::Game::Server::RtypeServerGameClient *client = dynamic_cast<Rtype::Game::Server::RtypeServerGameClient *>(curr.get());

        if (client && client != this)
        {
            client->SendPackage<MATEPackageGame>(&Network::UDP::AUDPConnection::SendReliable<MATEPackageGame>,
                                                 player->transform.position.x, player->transform.position.y, __playerID,
                                                 gameManager->gameObjectContainer.GetServerObjectID(player));
        }
    }
}

void Rtype::Game::Server::RtypeServerGameClient::OnDisconnect() {
    Rtype::Game::Common::RtypeGameClient::OnDisconnect();
    server1->DisconnectConnectedPlayer(__playerID);
	Debug::PrintInfo("Diconnected RtypeServerGameClient");
}

void Rtype::Game::Server::RtypeServerGameClient::onGetMATEPackage(MATEPackageGame const &matePackageGame) {

}

void Rtype::Game::Server::RtypeServerGameClient::onGetDEATHPackage(DEATHPackage const &pack)
{
    OnDiscoveringPackage(pack);
}