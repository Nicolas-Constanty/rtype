//
// Created by victor on 29/11/16.
//

#include <Protocol/Room/RoomPackageFactory.hpp>
#include "ServerRoom/RtypeRoomTCPConnection.hpp"
#include "Protocol/Room/ProtocolPrintRoomPackage.hpp"
#include "ServerRoom/ServerGameDispatcher.hpp"

RtypeRoomTCPConnection::RtypeRoomTCPConnection(Network::Core::NativeSocketIOOperationDispatcher &dispatcher)
        : ATCPClient(dispatcher), protocolRoomManager(*this), pseudo(""), id(0), roomService(NULL) {

}

RtypeRoomTCPConnection::RtypeRoomTCPConnection(Network::TCP::ATCPClient const &ref, std::string const &pseudo, unsigned int id)
        : Network::TCP::ATCPClient(ref), protocolRoomManager(*this), pseudo(pseudo), id(id), roomService(NULL) {

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

bool RtypeRoomTCPConnection::OnJoinRoom() {
    if (!roomService) {
        return false;
    }
    if (!roomService->isFull()) {
        roomService->AddPlayer(this);
        this->SendData(*(roomPackageFactory.create<JOINPackageRoom>(roomService->getID())));
        this->Broadcast<RtypeRoomTCPConnection>(*roomPackageFactory.create<GETPackageRoom>(roomService->getClientNbr(),
                                                                                           roomService->getClientMaxNbr(),
                                                                                           roomService->getName(),
                                                                                           roomService->getID(),
                                                                                           roomService->getMapID()));
        ///TODO BROADCAST GET packet
        ///TODO SEND PLUGGED packet au client à l'interieur de la room
    } else {
        return (false);
    }
    return (true);
}

void RtypeRoomTCPConnection::onGetCREATEPackage(CREATEPackageRoom const &obj) {
    std::cout << obj << std::endl;
    roomService = ServerGameDispatcher::Instance().CreateRoomService(obj.name, obj.roomPlayerMax, obj.mapID);
    if (roomService) {
        // La room a bien été créée par le ServerGameDispatcher.
        this->SendData(*roomPackageFactory.create<CREATEPackageRoom>(roomService->getClientNbr(),
                                                                    roomService->getClientMaxNbr(),
                                                                    roomService->getName(),
                                                                    roomService->getID(),
                                                                    roomService->getMapID()));
        if (!OnJoinRoom()) {
            this->SendData(*roomPackageFactory.create<FAILUREPackageRoom>("roomFailOnJoin", RoomPurpose::ROOMCREATE));
        }
    } else {
        // La room n'a pas été créée par le ServerGameDispatcher.
        this->SendData(*roomPackageFactory.create<FAILUREPackageRoom>("roomFailOnCreate", RoomPurpose::ROOMCREATE));
    }
}

void RtypeRoomTCPConnection::onGetJOINPackage(JOINPackageRoom const &obj) {
    roomService = ServerGameDispatcher::Instance().GetRoomServiceFromID(obj.roomID);
    if (!OnJoinRoom()) {
        this->SendData(*roomPackageFactory.create<FAILUREPackageRoom>("joinFail", RoomPurpose::ROOMJOIN));
    }
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
    this->SendData(*(roomPackageFactory.create<AUTHENTICATEPackageRoom>(pseudo, id)));

    // TODO donné toute les rooms du server
//    this->SendData(*(roomPackageFactory.create<GETPackageRoom>(100, 123, "MABITE", 1, 1)));
}

