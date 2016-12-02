//
// Created by victor on 30/11/16.
//

#ifndef RTYPE_ROOMSERVICE_HPP
#define RTYPE_ROOMSERVICE_HPP

#include "ServerRoom/RtypeRoomTCPConnection.hpp"

class RtypeGameServerTCPConnection;
//class RtypeRoomTCPConnection;

class RoomService {
public:
    RoomService(std::string const &name, unsigned short clientMaxNbr,
                unsigned short mapID, unsigned short id, RtypeGameServerTCPConnection *gameServerTCPConnection);
    ~RoomService();

public:
    void AddPlayer(RtypeRoomTCPConnection *);
    void Launch();
    void RemovePlayer(RtypeRoomTCPConnection *);

public:
    template <typename T>
    void Broadcast(T const &obj) {
        for (RtypeRoomTCPConnection *roomTCPConnection : clientsList) {
            roomTCPConnection->SendData(obj);
        }
    }

public:
    void Abort();
    void Close();

public:
    bool isLaunch() const;
    bool isFull() const;
    unsigned short getID() const;
    std::string const &getName() const;
    unsigned short getClientMaxNbr() const;
    unsigned short getMapID() const;
    unsigned short getClientNbr() const;
    bool getLaunch() const;
    std::list<RtypeRoomTCPConnection *> getClients() const;
    unsigned int getSecret() const;

private:
    std::string                             name;
    unsigned short                          clientMaxNbr;
    unsigned short                          mapID;
    unsigned short                          id;
    std::list<RtypeRoomTCPConnection *>     clientsList;
    RtypeGameServerTCPConnection            *gameServerTCPConnection;
    bool                                    launch;
    unsigned int                            secret;
};

#endif //RTYPE_ROOMSERVICE_HPP
