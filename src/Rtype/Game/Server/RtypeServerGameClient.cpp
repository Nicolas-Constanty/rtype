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
    OnDiscoveringPackage(pack);
    if (!server1->Authenticate(pack.secret))
    {
        //notification de déconnection au client
        connected = false;
    }
    else
    {
        CREATEPackageGame   *player = factory.create<CREATEPackageGame>();
        //todo Instantiate player in engine

        connected = true;
        //todo player->ID = correspondance prefab
        //todo player->objectID = correspondance gameobject engine
        player->objectID = 5;
        BroadcastReliable(*player);
        SendReliable(*factory.create<AUTHENTICATEPackageGame>(pack.secret, player->objectID));
        ping();
        //notification de connection du client à tous les clients
    }
}

void Rtype::Game::Server::RtypeServerGameClient::onGetCREATEPackage(CREATEPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    //todo notification des autres clients
}

void Rtype::Game::Server::RtypeServerGameClient::onGetBEAMPackage(BEAMPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    //todo notification des autres clients
}

void Rtype::Game::Server::RtypeServerGameClient::onGetSHOTPackage(SHOTPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    //todo notification des autres clients
}

void Rtype::Game::Server::RtypeServerGameClient::onGetDIEPackage(DIEPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    //todo notification des autres clients
}

void Rtype::Game::Server::RtypeServerGameClient::onGetTAKEPackage(TAKEPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    //todo notification des autres clients
}

void Rtype::Game::Server::RtypeServerGameClient::onGetDROPPackage(DROPPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    //todo notification des autres clients
}

void Rtype::Game::Server::RtypeServerGameClient::onGetMOVEPackage(MOVEPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    //todo notification des autres clients
}

void Rtype::Game::Server::RtypeServerGameClient::onGetLAUNCHPackage(LAUNCHPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    //todo notification des autres clients
}

void Rtype::Game::Server::RtypeServerGameClient::onGetREBORNPackage(REBORNPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    //todo notification des autres clients
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

const int Rtype::Game::Server::RtypeServerGameClient::getId() const
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
//    std::cout << "Pong: " << std::boolalpha << (pingSecret == -1) << std::endl;
    if (pingSecret == -1)
        std::cout << "\e[32mPong\e[0m" << std::endl;
    return pingSecret == -1;
}
