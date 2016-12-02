//
// Created by victor on 30/11/16.
//

#include "ServerRoom/ServerGameDispatcher.hpp"


ServerGameDispatcher::~ServerGameDispatcher() {

}

ServerGameDispatcher::ServerGameDispatcher() {

}


void ServerGameDispatcher::Add(RtypeGameServerTCPConnection *serverTCPConnection) {
    serverList.push_back(serverTCPConnection);
}

void ServerGameDispatcher::Remove(RtypeGameServerTCPConnection *serverTCPConnection) {
    serverList.remove(serverTCPConnection);
}

RoomService *ServerGameDispatcher::CreateRoomService(std::string const &name, unsigned short clientMaxNbr,
                                                     unsigned short mapID) {
    std::list<RtypeGameServerTCPConnection *>::iterator it = serverList.begin();
    while (it != serverList.end()) {
        if (!(*it)->isFull()) {
            return ((*it)->AddRoomService(name, clientMaxNbr, mapID));
        }
        ++it;
    }
    return (NULL);
}

RoomService *ServerGameDispatcher::GetRoomServiceFromID(unsigned short id) const {
    std::list<RtypeGameServerTCPConnection *>::const_iterator it = serverList.begin();
    RoomService *roomService = NULL;

    while (it != serverList.end()) {
        roomService = (*it)->GetRoomFromID(id);
        if (roomService) {
            return roomService;
        }
        ++it;
    }
    return (NULL);
}

std::list<RtypeGameServerTCPConnection *> ServerGameDispatcher::GetServerList() const {
    return this->serverList;
}
