//
// Created by gaspar_q on 12/6/16.
//

#include <Protocol/Game/ProtocolPrintGamePackage.hpp>
#include <ServerGame/RtypeServerGameClient.hpp>
#include <ServerGame/RtypeGameServer.hpp>

Rtype::RtypeServerGameClient::RtypeServerGameClient(Network::Core::NativeSocketIOOperationDispatcher &dispatcher) :
        RtypeGameClient(dispatcher),
        factory(),
        server1(NULL),
        pingSecret(-1),
        pingTime(),
        id(0)
{

}

Rtype::RtypeServerGameClient::RtypeServerGameClient(const Rtype::RtypeServerGameClient &ref) :
    RtypeGameClient(ref)
{

}

Rtype::RtypeServerGameClient::~RtypeServerGameClient()
{

}

void Rtype::RtypeServerGameClient::onGetSTATUSPackage(STATUSPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
}

void Rtype::RtypeServerGameClient::onGetPINGPackage(PINGPackageGame const &pack)
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

void Rtype::RtypeServerGameClient::onGetAUTHENTICATEPackage(AUTHENTICATEPackageGame const &pack)
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

void Rtype::RtypeServerGameClient::onGetCREATEPackage(CREATEPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    //todo notification des autres clients
}

void Rtype::RtypeServerGameClient::onGetBEAMPackage(BEAMPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    //todo notification des autres clients
}

void Rtype::RtypeServerGameClient::onGetSHOTPackage(SHOTPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    //todo notification des autres clients
}

void Rtype::RtypeServerGameClient::onGetDIEPackage(DIEPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    //todo notification des autres clients
}

void Rtype::RtypeServerGameClient::onGetTAKEPackage(TAKEPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    //todo notification des autres clients
}

void Rtype::RtypeServerGameClient::onGetDROPPackage(DROPPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    //todo notification des autres clients
}

void Rtype::RtypeServerGameClient::onGetMOVEPackage(MOVEPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    //todo notification des autres clients
}

void Rtype::RtypeServerGameClient::onGetLAUNCHPackage(LAUNCHPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    //todo notification des autres clients
}

void Rtype::RtypeServerGameClient::onGetREBORNPackage(REBORNPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    //todo notification des autres clients
}

bool Rtype::RtypeServerGameClient::OnStart()
{
    server1 = dynamic_cast<Rtype::RtypeGameServer *>(serverStream);
    if (!server1)
    {
        Disconnect();
        return false;
    }
    if (clients)
        id = static_cast<int>(clients->Streams().size() + 1);
    return true;
}

const int Rtype::RtypeServerGameClient::getId() const
{
    return id;
}

bool Rtype::RtypeServerGameClient::timedout() const
{
    return std::chrono::steady_clock::now() - pingTime > Rtype::RtypeServerGameClient::timeout;
}

void Rtype::RtypeServerGameClient::ping()
{
    pingSecret = rand();
    pingTime = std::chrono::steady_clock::now();
    SendReliable(*factory.create<PINGPackageGame>(pingSecret));
    if (serverStream)
        serverStream->WantSend();
}

bool Rtype::RtypeServerGameClient::pong() const
{
//    std::cout << "Pong: " << std::boolalpha << (pingSecret == -1) << std::endl;
    if (pingSecret == -1)
        std::cout << "\e[32mPong\e[0m" << std::endl;
    return pingSecret == -1;
}
