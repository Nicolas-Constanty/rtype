//
// Created by victor on 29/11/16.
//

#include <Protocol/Room/RoomPackageFactory.hpp>
#include "ServerRoom/RtypeRoomTCPConnection.hpp"
#include "Protocol/Room/ProtocolPrintRoomPackage.hpp"

RtypeRoomTCPConnection::RtypeRoomTCPConnection(Network::Core::NativeSocketIOOperationDispatcher &dispatcher)
        : ATCPClient(dispatcher), protocolRoomManager(*this) {

}

RtypeRoomTCPConnection::RtypeRoomTCPConnection(Network::TCP::ATCPClient const &ref, std::string const &pseudo, unsigned int id)
        : Network::TCP::ATCPClient(ref), protocolRoomManager(*this), pseudo(pseudo), id(id) {

}

RtypeRoomTCPConnection::~RtypeRoomTCPConnection() {

}

void RtypeRoomTCPConnection::OnDataReceived(unsigned int) {
    if (!protocolRoomManager.handleProtocol(buff.buff(), buff.getLength())) {
        std::cout << "unknown command" << std::endl;
    }
}

void RtypeRoomTCPConnection::OnDataSent(unsigned int len) {
    std::cout << "data sent : len" << len << std::endl;
}

void RtypeRoomTCPConnection::onGetAUTHENTICATEPackage(AUTHENTICATEPackageRoom const &obj) {
    std::cout << obj << std::endl;
}

void RtypeRoomTCPConnection::onGetCREATEPackage(CREATEPackageRoom const &obj) {
    std::cout << obj << std::endl;
}

void RtypeRoomTCPConnection::onGetJOINPackage(JOINPackageRoom const &obj) {
    std::cout << obj << std::endl;
}

void RtypeRoomTCPConnection::onGetQUITPackage(QUITPackageRoom const &obj) {
    std::cout << obj << std::endl;
}

void RtypeRoomTCPConnection::onGetPLUGGEDPackage(PLUGGEDPackageRoom const &obj) {
    std::cout << obj << std::endl;
}

void RtypeRoomTCPConnection::onGetSWAPPackage(SWAPPackageRoom const &obj) {
    std::cout << obj << std::endl;
}

void RtypeRoomTCPConnection::onGetGETPackage(GETPackageRoom const &obj) {
    std::cout << obj << std::endl;
}

void RtypeRoomTCPConnection::onGetFAILUREPackage(FAILUREPackageRoom const &obj) {
    std::cout << obj << std::endl;
}

void RtypeRoomTCPConnection::onGetLAUNCHPackage(LAUNCHPackageRoom const &obj) {
    std::cout << obj << std::endl;
}

void RtypeRoomTCPConnection::OnStart() {
    this->SendData(*(RoomPackageFactory().create<AUTHENTICATEPackageRoom>(pseudo, id)));

    // TODO donné toute les rooms du server
    this->SendData(*(RoomPackageFactory().create<GETPackageRoom>(100, 123, "MABITE", 1, 1)));
}
