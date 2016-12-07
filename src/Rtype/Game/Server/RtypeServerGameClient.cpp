//
// Created by gaspar_q on 12/6/16.
//

#include <Protocol/Game/ProtocolPrintGamePackage.hpp>
#include <Rtype/Game/Server/RtypeServerGameClient.hpp>
#include <Rtype/Game/Server/RtypeGameServer.hpp>

Rtype::Game::Server::RtypeServerGameClient::RtypeServerGameClient(Network::Core::NativeSocketIOOperationDispatcher &dispatcher) :
        RtypeGameClient(dispatcher),
        factory(),
        server1(NULL),
        pingSecret(-1),
        pingTime(),
        id(0)
{

}

Rtype::Game::Server::RtypeServerGameClient::RtypeServerGameClient(const Rtype::Game::Server::RtypeServerGameClient &ref) :
    RtypeGameClient(ref)
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
    reply = false;
    OnDiscoveringPackage(pack);
    if (pingSecret != -1 && pack.secret != pingSecret)
    {
        connected = false;
        std::cout << "Disconnection" << std::endl;
    }
    else
    {
        pingSecret = -1;
        std::cout << "\e[32mYou have been ponged\e[0m: " << pingSecret << std::endl;
    }
}

void Rtype::Game::Server::RtypeServerGameClient::onGetAUTHENTICATEPackage(AUTHENTICATEPackageGame const &pack)
{
    reply = false;
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
        CREATEPackageGame   *player = factory.create<CREATEPackageGame>();
        //todo Instantiate player in engine with an object id
        //todo player->ID = correspondance prefab
        //todo player->objectID = correspondance gameobject engine
        player->objectID = 5;

        //notify to all players the creation of a player
        BroadcastReliable(*player);

        //notify to <this> player that he is authenticated
        SendReliable(*factory.create<AUTHENTICATEPackageGame>(pack.secret, player->objectID));

        //notify to <this> player to create existing players
        for (std::unique_ptr<Network::Socket::ISockStreamHandler> &curr : clients->Streams())
        {
            if (static_cast<void *>(&curr) != this)
            {
                //todo same shit as above for existing players
                SendReliable(*factory.create<CREATEPackageGame>());
            }
        }

        //ping <this> player in order to made him survive
        ping();
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
//        BroadcastReliable(*factory.create<BEAMPackageGame>(pack.objectID));
//    }
//    else
//    {
//        SendReliable(*factory.create<FAILUREPackageGame>(pack.purpose, pack.sequenceID));
//    }
}

void Rtype::Game::Server::RtypeServerGameClient::onGetSHOTPackage(SHOTPackageGame const &pack)
{
    OnDiscoveringPackage(pack);

//    todo if (okay on gameside)
//    {
//        BroadcastReliable(*factory.create<SHOTPackageGame>(pack.objectID));
//    }
//    else
//    {
//        SendReliable(*factory.create<FAILUREPackageGame>(pack.purpose, pack.sequenceID));
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
//        BroadcastReliable(*factory.create<TAKEPackageGame>(pack.objectID));
//    }
//    else
//    {
//        SendReliable(*factory.create<FAILUREPackageGame>(pack.purpose, pack.sequenceID));
//    }
}

void Rtype::Game::Server::RtypeServerGameClient::onGetDROPPackage(DROPPackageGame const &pack)
{
    OnDiscoveringPackage(pack);

//    todo if (okay on gameside)
//    {
//        BroadcastReliable(*factory.create<DROPPackageGame>(pack.objectID));
//    }
//    else
//    {
//        SendReliable(*factory.create<FAILUREPackageGame>(pack.purpose, pack.sequenceID));
//    }
}

void Rtype::Game::Server::RtypeServerGameClient::onGetMOVEPackage(MOVEPackageGame const &pack)
{
    OnDiscoveringPackage(pack);

//    todo if (okay on gameside)
//    {
//        Broadcast(*factory.create<MOVEPackageGame>(pack.posX, pack.posY, pack.objectID));
//    }
//    else
//    {
//        SendReliable(*factory.create<FAILUREPackageGame>(pack.purpose, pack.sequenceID));
//    }
}

void Rtype::Game::Server::RtypeServerGameClient::onGetLAUNCHPackage(LAUNCHPackageGame const &pack)
{
    OnDiscoveringPackage(pack);

//    todo if (okay on gameside)
//    {
//        BroadcastReliable(*factory.create<LAUNCHPackageGame>(pack.objectID));
//    }
//    else
//    {
//        SendReliable(*factory.create<FAILUREPackageGame>(pack.purpose, pack.sequenceID));
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
    SendReliable(*factory.create<PINGPackageGame>(pingSecret));
    if (serverStream)
        serverStream->WantSend();
}

bool Rtype::Game::Server::RtypeServerGameClient::pong() const
{
    return pingSecret == -1;
}
