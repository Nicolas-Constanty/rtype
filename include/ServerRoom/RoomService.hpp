//
// Created by victor on 30/11/16.
//

#ifndef RTYPE_ROOMSERVICE_HPP
#define RTYPE_ROOMSERVICE_HPP

#include "ServerRoom/RtypeRoomTCPConnection.hpp"

class RtypeGameServerTCPConnection;
class RtypeRoomTCPConnection;

class RoomService {
public:
    RoomService(std::string const &name, unsigned short clientMaxNbr,
                unsigned short mapID, unsigned short id, RtypeGameServerTCPConnection *gameServerTCPConnection);
    ~RoomService();

public:
    void AddPlayer(RtypeRoomTCPConnection *);
    bool isFull() const;
    void RemovePlayer(RtypeRoomTCPConnection *);
    void Launch();
    bool isLaunch() const;
    unsigned short getID() const;
    std::string const &getName() const;
    unsigned short getClientMaxNbr() const;
    unsigned short getMapID() const;
    unsigned short getClientNbr() const;

private:
    std::string                             name;
    unsigned short                          clientMaxNbr;
    unsigned short                          mapID;
    unsigned short                          id;
    std::list<RtypeRoomTCPConnection *>     clientsList;
    RtypeGameServerTCPConnection            *gameServerTCPConnection;
    bool                                    launch;
};

#endif //RTYPE_ROOMSERVICE_HPP
