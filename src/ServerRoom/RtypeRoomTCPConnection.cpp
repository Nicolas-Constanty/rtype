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

void RtypeRoomTCPConnection::BroadCastGETRoom() {
    if (roomService)
        this->Broadcast<RtypeRoomTCPConnection>(*roomPackageFactory.create<GETPackageRoom>(roomService->getClientNbr(),
                                                                                           roomService->getClientMaxNbr(),
                                                                                           roomService->getName(),
                                                                                           roomService->getID(),
                                                                                           roomService->getMapID()));

}

void RtypeRoomTCPConnection::BroadCastNowGETRoom() {
    if (roomService)
        this->BroadcastNow<RtypeRoomTCPConnection>(*roomPackageFactory.create<GETPackageRoom>(roomService->getClientNbr(),
                                                                                           roomService->getClientMaxNbr(),
                                                                                           roomService->getName(),
                                                                                           roomService->getID(),
                                                                                           roomService->getMapID()));

}

void RtypeRoomTCPConnection::onGetAUTHENTICATEPackage(AUTHENTICATEPackageRoom const &obj) {
    std::cout << obj << std::endl;
}

void RtypeRoomTCPConnection::OnSendGetRooms() {
    std::list<RtypeGameServerTCPConnection *> serverList = ServerGameDispatcher::Instance().GetServerList();
    for (RtypeGameServerTCPConnection *serverGame : serverList) {
        for (RoomService *roomService : serverGame->RoomsService()) {
            this->SendData(*roomPackageFactory.create<GETPackageRoom>(roomService->getClientMaxNbr(),
                                                                      roomService->getClientMaxNbr(),
                                                                      roomService->getName(),
                                                                      roomService->getID(),
                                                                      roomService->getMapID()));
        }
    }
}

bool RtypeRoomTCPConnection::OnJoinRoom() {
    if (!roomService) {
        return false;
    }
    if (!roomService->isFull()) {
        roomService->AddPlayer(this);
        this->SendData(*(roomPackageFactory.create<JOINPackageRoom>(roomService->getID())));
        BroadCastGETRoom();
        std::list<RtypeRoomTCPConnection *> clientsList = roomService->getClients();
        PLUGGEDPackageRoom *pluggedPackageRoom = roomPackageFactory.create<PLUGGEDPackageRoom>(this->pseudo,
                                                                                               this->id,
                                                                                               roomService->getID());
        roomService->Broadcast(*pluggedPackageRoom);

        for (RtypeRoomTCPConnection *client : clientsList) {
            if (client != this)
                this->SendData(*roomPackageFactory.create<PLUGGEDPackageRoom>(client->pseudo,
                                                                              client->id,
                                                                              roomService->getID()));
        }
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
    std::cout << obj << std::endl;
    if (roomService) {
        this->SendData(*roomPackageFactory.create<FAILUREPackageRoom>("already join", RoomPurpose::ROOMJOIN));
        return ;
    }
    roomService = ServerGameDispatcher::Instance().GetRoomServiceFromID(obj.roomID);
    if (!OnJoinRoom()) {
        this->SendData(*roomPackageFactory.create<FAILUREPackageRoom>("joinFail", RoomPurpose::ROOMJOIN));
        roomService = NULL;
    }
}

void RtypeRoomTCPConnection::OnQUITEvent(bool canBroadcastGET) {
    if (!roomService) {
        return ;
    }
    roomService->RemovePlayer(this);
    this->SendData(*roomPackageFactory.create<QUITPackageRoom>(id, roomService->getID()));
    SendQUITToAllClientsInsideTheRoom();
    if (canBroadcastGET)
        BroadCastGETRoom();
    roomService = NULL;
}

void RtypeRoomTCPConnection::onGetQUITPackage(QUITPackageRoom const &obj) {
    std::cout << obj << std::endl;
    if (!roomService) {
        this->SendData(*roomPackageFactory.create<FAILUREPackageRoom>("no room", RoomPurpose::ROOMQUIT));
        return ;
    }
    OnQUITEvent(true);
}

void RtypeRoomTCPConnection::onGetDELETEPackage(DELETEPackageRoom const &obj) {
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
    if (roomService && !roomService->isLaunch()) {
        roomService->Launch();
    } else {
        this->SendData(*roomPackageFactory.create<FAILUREPackageRoom>("no room to launch", RoomPurpose::ROOMLAUNCH));
    }
}

void RtypeRoomTCPConnection::OnStart() {
    this->SendData(*(roomPackageFactory.create<AUTHENTICATEPackageRoom>(pseudo, id)));
    OnSendGetRooms();
}

void RtypeRoomTCPConnection::OnDisconnect() {
    if (roomService) {
        roomService->RemovePlayer(this);
        BroadCastNowGETRoom();
        SendQUITToAllClientsInsideTheRoom();
        roomService = NULL;
    }
}

void RtypeRoomTCPConnection::SendQUITToAllClientsInsideTheRoom() {
    if (!roomService) {
        return ;
    }
    QUITPackageRoom *quitPackageRoom = roomPackageFactory.create<QUITPackageRoom>(this->id,
                                                                                  roomService->getID());
    roomService->Broadcast(*quitPackageRoom);
}

unsigned int RtypeRoomTCPConnection::getID() const {
    return (id);
}

void RtypeRoomTCPConnection::removeOnRoom() {
    roomService = NULL;
}

