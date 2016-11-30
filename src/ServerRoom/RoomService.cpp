//
// Created by victor on 30/11/16.
//

#include <ServerRoom/RoomService.hpp>

RoomService::RoomService(const std::string &name,
                         unsigned short clientMaxNbr,
                         unsigned short mapID,
                         unsigned short id,
                         RtypeGameServerTCPConnection *gameServerTCPConnection)
        : name(name), clientMaxNbr(clientMaxNbr), mapID(mapID), id(id), gameServerTCPConnection(gameServerTCPConnection), launch(false) {

}

RoomService::~RoomService() {

}

void RoomService::AddPlayer(RtypeRoomTCPConnection *roomTCPConnection) {
    this->clientsList.push_back(roomTCPConnection);
}

void RoomService::RemovePlayer(RtypeRoomTCPConnection *roomTCPConnection) {
    this->clientsList.remove(roomTCPConnection);
}

void RoomService::Launch() {
    launch = true;
}

bool RoomService::isLaunch() const {
    return launch;
}

bool RoomService::isFull() const {
    return (this->clientsList.size() > clientMaxNbr);
}

unsigned short RoomService::getID() const {
    return (this->id);
}

std::string const &RoomService::getName() const {
    return this->name;
}

unsigned short RoomService::getClientMaxNbr() const {
    return this->clientMaxNbr;
}

unsigned short RoomService::getMapID() const {
    return this->mapID;
}

unsigned short RoomService::getClientNbr() const {
    return static_cast<unsigned short>(this->clientsList.size());
}
