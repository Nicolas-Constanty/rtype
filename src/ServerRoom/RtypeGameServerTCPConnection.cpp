//
// Created by victor on 29/11/16.
//

#include <ServerRoom/ServerGameDispatcher.hpp>
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

void RtypeGameServerTCPConnection::OnDisconnect() {
    ServerGameDispatcher::Instance().Remove(this);
}

void RtypeGameServerTCPConnection::OnDataSent(unsigned int len) {

}

void RtypeGameServerTCPConnection::OnStart() {
    ServerGameDispatcher::Instance().Add(this);
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

unsigned short RtypeGameServerTCPConnection::getRoomNumberMax() const {
    return roomNumberMax;
}

unsigned int RtypeGameServerTCPConnection::getID() const {
    return id;
}

unsigned long RtypeGameServerTCPConnection::getActualRoomNumber() const {
    return (this->roomServiceList.size());
}

RoomService *RtypeGameServerTCPConnection::AddRoomService(std::string const &name, unsigned short clientMaxNbr,
                                                          unsigned short mapID) {
    static unsigned short id = 0;
    RoomService *roomService = new RoomService(name, clientMaxNbr, mapID, ++id, this);

    this->roomServiceList.emplace_back(roomService);
    return (roomService);
}

bool RtypeGameServerTCPConnection::isFull() const {
    return (this->roomNumberMax <= this->roomServiceList.size());
}

void RtypeGameServerTCPConnection::RemoveRoomService(RoomService *roomService) {
    std::list<std::unique_ptr<RoomService>>::const_iterator it = roomServiceList.begin();

    while (it != roomServiceList.end()) {
        if ((*it).get() == roomService) {
            this->roomServiceList.erase(it);
            return ;
        }
        ++it;
    }
}

RoomService *RtypeGameServerTCPConnection::GetRoomFromID(unsigned short id) const {
    std::list<std::unique_ptr<RoomService>>::const_iterator it = roomServiceList.begin();

    while (it != roomServiceList.end()) {
        if ((*it)->getID() == id) {
            return ((*it).get());
        }
        ++it;
    }
    return (NULL);
}
