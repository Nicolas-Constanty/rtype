//
// Created by gaspar_q on 11/28/16.
//

#include <Protocol/Game/ProtocolPrintGamePackage.hpp>
#include <Network/Core/NativeSocketIOOperationDispatcher.hpp>
#include <ServerGame/RtypeGameClient.hpp>

RtypeGameClient::RtypeGameClient(Network::Core::NativeSocketIOOperationDispatcher &dispatcher) :
        Network::UDP::AUDPClient::AUDPClient(this, dispatcher),
        manager(*this)
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
    manager.handleProtocol(buff.buff(), buff.getLength());//todo finish the merge of length
    std::cout << "Receive: " << buff << std::endl;
}

void RtypeGameClient::OnDataSent(unsigned int len)
{
    std::cout << "Sent: " << len << std::endl;
}

void RtypeGameClient::onGetSTATUSPackage(STATUSPackageGame const &pack)
{
    std::cout << pack << std::endl;
}

void RtypeGameClient::onGetPINGPackage(PINGPackageGame const &pack)
{
    std::cout << pack << std::endl;
}

void RtypeGameClient::onGetAUTHENTICATEPackage(AUTHENTICATEPackageGame const &pack)
{
    std::cout << pack << std::endl;
}

void RtypeGameClient::onGetCREATEPackage(CREATEPackageGame const &pack)
{
    std::cout << pack << std::endl;
}

void RtypeGameClient::onGetBEAMPackage(BEAMPackageGame const &pack)
{
    std::cout << pack << std::endl;
}

void RtypeGameClient::onGetSHOTPackage(SHOTPackageGame const &pack)
{
    std::cout << pack << std::endl;
}

void RtypeGameClient::onGetDIEPackage(DIEPackageGame const &pack)
{
    std::cout << pack << std::endl;
}

void RtypeGameClient::onGetTAKEPackage(TAKEPackageGame const &pack)
{
    std::cout << pack << std::endl;
}

void RtypeGameClient::onGetDROPPackage(DROPPackageGame const &pack)
{
    std::cout << pack << std::endl;
}

void RtypeGameClient::onGetMOVEPackage(MOVEPackageGame const &pack)
{
    std::cout << pack << std::endl;
}

void RtypeGameClient::onGetLAUNCHPackage(LAUNCHPackageGame const &pack)
{
    std::cout << pack << std::endl;
}
