//
// Created by gaspar_q on 11/28/16.
//

#include <Network/Core/NativeSocketIOOperationDispatcher.hpp>
#include <Rtype/Game/Common/RtypeGameClient.hpp>
#include <SaltyEngine/SaltyEngine.hpp>
#include <Rtype/Game/Server/RtypeGameServer.hpp>
#include "Common/Debug.hpp"

const std::chrono::milliseconds    Rtype::Game::Common::RtypeGameClient::timeout = std::chrono::milliseconds(5000);

Rtype::Game::Common::RtypeGameClient::RtypeGameClient(Network::Core::NativeSocketIOOperationDispatcher &dispatcher) :
        Network::UDP::AUDPClient::AUDPClient(dispatcher),
        manager(*this),
        factory(),
        recvstatus(),
        sendstatus(),
        reply(false),
        connected(false),
        playerID(0),
        errcode(DisconnectionCode::NOERROR),
        getDisconnected(false),
        gameManager(NULL)
{

}

Rtype::Game::Common::RtypeGameClient::RtypeGameClient(const RtypeGameClient &ref) :
    Network::UDP::AUDPClient(ref),
    manager(*this),
    factory(),
    recvstatus(),
    sendstatus(),
    reply(false),
    connected(false),
    playerID(0),
    errcode(DisconnectionCode::NOERROR),
    getDisconnected(false),
    gameManager(NULL)
{

}

Rtype::Game::Common::RtypeGameClient::~RtypeGameClient()
{

}

bool Rtype::Game::Common::RtypeGameClient::OnDataReceived(unsigned int)
{
    while (buff.getLength() >= sizeof(PackageGameHeader))
    {
        PackageGameHeader *head = buff.buff<PackageGameHeader>();

        if (head->transactionID != 0)
        {
            //here you can check packet send by server which are lost
            sendstatus.Receiving(head->sequenceID);
            buff += head->length;
        }
        else if (!recvstatus.IsSet(head->sequenceID) && !getDisconnected)
        {
            reply = recvstatus.Receiving(head->sequenceID);
            if (reply)
            {
                head->transactionID = recvstatus.sliceAt(head->sequenceID).getStatus();
            }
            if (!manager.handleProtocol(buff.buff(), buff.getLength()))
            {
                buff.reset();
                break;
            }
            if (!connected)
            {
                Debug::PrintInfo("Disconnected while reading");
                Disconnect();
                return false;
            }
        }
        else
        {
            buff += head->length;
        }
    }
    buff.consume();
    return true;
}

bool Rtype::Game::Common::RtypeGameClient::OnDataSent(unsigned int)
{
    return true;
}

void Rtype::Game::Common::RtypeGameClient::onGetDISCONNECTPackage(DISCONNECTPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    Debug::PrintInfo("Get disconnected");
    if (playerID == pack.playerID)
    {
        getDisconnected = true;
    }
}

void Rtype::Game::Common::RtypeGameClient::OnDisconnect()
{
	Debug::PrintInfo("On Disconnect called");
    if (!getDisconnected)
        BroadCastPackage<DISCONNECTPackageGame>(&Rtype::Game::Common::RtypeGameClient::SendToServerReliablyNow<DISCONNECTPackageGame>, playerID,
                                           static_cast<unsigned int>(errcode));
}

void Rtype::Game::Common::RtypeGameClient::setManager(GameManager *manager1)
{
    gameManager = manager1;
}
