//
// Created by gaspar_q on 11/28/16.
//

#include <Protocol/Game/ProtocolPrintGamePackage.hpp>
#include <Network/Core/NativeSocketIOOperationDispatcher.hpp>
#include <ServerGame/RtypeGameClient.hpp>
#include <Protocol/Game/ProtocolGamePackage.hpp>
#include <SaltyEngine/SaltyEngine.hpp>

RtypeGameClient::RtypeGameClient(Network::Core::NativeSocketIOOperationDispatcher &dispatcher) :
        Network::UDP::AUDPClient::AUDPClient(dispatcher),
        manager(*this),
        id(0)
{

}

RtypeGameClient::RtypeGameClient(const RtypeGameClient &ref) :
    Network::UDP::AUDPClient(ref),
    manager(*this)
{

}

RtypeGameClient::~RtypeGameClient()
{

}

void RtypeGameClient::OnDataReceived(unsigned int)
{
    if (buff.getLength() < sizeof(PackageGameHeader))
        return;

    PackageGameHeader *head = buff.buff<PackageGameHeader>();

//    buff.deserialize(head);// = buff. buff<PackageGameHeader>();

    if (!status.IsSet(head->sequenceID))
    {
        reply = status.Receiving(head->sequenceID);
        if (reply)
            head->transactionID = status.sliceAt(head->sequenceID).getStatus();
        while (manager.handleProtocol(buff.buff(), buff.getLength()));//todo finish the merge of length
    }
}

void RtypeGameClient::OnDataSent(unsigned int len)
{
    std::cout << "Sent: " << len << std::endl;
}

void RtypeGameClient::onGetSTATUSPackage(STATUSPackageGame const &pack)
{
    std::cout << pack << std::endl;
    OnDiscoveringPackage(pack);
}

void RtypeGameClient::onGetPINGPackage(PINGPackageGame const &pack)
{
    std::cout << pack << std::endl;
    OnDiscoveringPackage(pack);
}

void RtypeGameClient::onGetAUTHENTICATEPackage(AUTHENTICATEPackageGame const &pack)
{
    std::cout << pack << std::endl;
    OnDiscoveringPackage(pack);
}

void RtypeGameClient::onGetCREATEPackage(CREATEPackageGame const &pack)
{
    std::cout << pack << std::endl;
    OnDiscoveringPackage(pack);
}

void RtypeGameClient::onGetBEAMPackage(BEAMPackageGame const &pack)
{
    std::cout << pack << std::endl;
    OnDiscoveringPackage(pack);
}

void RtypeGameClient::onGetSHOTPackage(SHOTPackageGame const &pack)
{
    std::cout << pack << std::endl;
    OnDiscoveringPackage(pack);
}

void RtypeGameClient::onGetDIEPackage(DIEPackageGame const &pack)
{
    std::cout << pack << std::endl;
    OnDiscoveringPackage(pack);
}

void RtypeGameClient::onGetTAKEPackage(TAKEPackageGame const &pack)
{
    std::cout << pack << std::endl;
    OnDiscoveringPackage(pack);
}

void RtypeGameClient::onGetDROPPackage(DROPPackageGame const &pack)
{
    std::cout << pack << std::endl;
    OnDiscoveringPackage(pack);
}

void RtypeGameClient::onGetMOVEPackage(MOVEPackageGame const &pack)
{
    std::cout << pack << std::endl;
    OnDiscoveringPackage(pack);
    buff.reset();
}

void RtypeGameClient::onGetLAUNCHPackage(LAUNCHPackageGame const &pack)
{
    std::cout << pack << std::endl;
    OnDiscoveringPackage(pack);
}

void RtypeGameClient::OnStart()
{
    if (clients)
        id = static_cast<int>(clients->Streams().size() + 1);
}

const int RtypeGameClient::getId() const
{
    return id;
}
