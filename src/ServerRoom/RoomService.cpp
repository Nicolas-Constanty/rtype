//
// Created by victor on 30/11/16.
//

#include <ServerRoom/RoomService.hpp>
#include <ServerRoom/SecretGeneration.hpp>
#include "ServerRoom/RtypeGameServerTCPConnection.hpp"
#include "Protocol/Server/ServerPackageFactory.hpp"

RoomService::RoomService(const std::string &name,
                         unsigned short clientMaxNbr,
                         unsigned short mapID,
                         unsigned short id,
                         RtypeGameServerTCPConnection *gameServerTCPConnection)
        : name(name), clientMaxNbr(clientMaxNbr), mapID(mapID), id(id),
          gameServerTCPConnection(gameServerTCPConnection), clientsList(), launch(false), secret(0) {

}

RoomService::~RoomService() {
    std::cout << "\e[31m RoomService deleted name: " << name << "id:" << id << "\e[0m" << std::endl;
}

void RoomService::AddPlayer(RtypeRoomTCPConnection *roomTCPConnection) {
    this->clientsList.push_back(roomTCPConnection);
}

void RoomService::RemovePlayer(RtypeRoomTCPConnection *roomTCPConnection) {
    this->clientsList.remove(roomTCPConnection);
}

void RoomService::Launch() {
    launch = true;
    secret = SecretGeneration::Instance().generateSecret();
    this->gameServerTCPConnection->SendData(*ServerPackageFactory().create<LAUNCHPackageServer>(static_cast<unsigned short>(this->clientsList.size()),
                                                                                                this->mapID,
                                                                                                secret));
}

bool RoomService::isLaunch() const {
    return launch;
}

bool RoomService::isFull() const {
    return (this->clientsList.size() >= clientMaxNbr);
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

std::list<RtypeRoomTCPConnection *> RoomService::getClients() const {
    return this->clientsList;
}

void RoomService::Abort() {
    while (!this->clientsList.empty()) {
        this->clientsList.front()->OnQUITEvent(false);
    }
}

unsigned int RoomService::getSecret() const {
    return (this->secret);
}

void RoomService::Close() {
    for (RtypeRoomTCPConnection *roomTCPConnection : this->clientsList) {
        roomTCPConnection->removeOnRoom();
    }
}

bool RoomService::getLaunch() const {
    return launch;
}
