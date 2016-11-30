//
// Created by victor on 29/11/16.
//

#include "ServerRoom/RtypeGameServerTCPConnection.hpp"
#include "Protocol/Server/ProtocolPrintServerPackage.hpp"

RtypeGameServerTCPConnection::RtypeGameServerTCPConnection(Network::Core::NativeSocketIOOperationDispatcher &dispatcher)
        : ATCPClient(dispatcher), protocolServerManager(*this), id(0), roomNumberMax(0) {

}

RtypeGameServerTCPConnection::RtypeGameServerTCPConnection(const Network::TCP::ATCPClient &ref, unsigned int id,
                                                           unsigned short roomNumberMax)
        : Network::TCP::ATCPClient(ref), protocolServerManager(*this), id(id), roomNumberMax(roomNumberMax) {

}

RtypeGameServerTCPConnection::~RtypeGameServerTCPConnection() {

}

void RtypeGameServerTCPConnection::OnDataReceived(unsigned int len) {
    if (!protocolServerManager.handleProtocol(buff.buff(), buff.getLength())) {
        std::cout << "unknown cmd" << std::endl;
    }
}

void RtypeGameServerTCPConnection::OnDataSent(unsigned int len) {

}

void RtypeGameServerTCPConnection::OnStart() {
    this->SendData(*(serverPackageFactory.create<AUTHENTICATEPackageServer>(id, roomNumberMax)));
}

void RtypeGameServerTCPConnection::onGetAUTHENTICATEPackage(const AUTHENTICATEPackageServer &obj) {
    std::cout << obj << std::endl;
}

void RtypeGameServerTCPConnection::onGetLAUNCHPackage(const LAUNCHPackageServer &obj) {
    std::cout << obj << std::endl;
}

void RtypeGameServerTCPConnection::onGetSTATUSPackage(const STATUSPackageServer &obj) {
    std::cout << obj << std::endl;
}
