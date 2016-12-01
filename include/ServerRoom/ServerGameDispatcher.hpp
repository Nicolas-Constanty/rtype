//
// Created by victor on 30/11/16.
//

#ifndef RTYPE_SERVERGAMEDISPATCHER_HPP
#define RTYPE_SERVERGAMEDISPATCHER_HPP

#include "Common/Singleton.hpp"
#include "ServerRoom/RtypeGameServerTCPConnection.hpp"
#include "ServerRoom/RoomService.hpp"

class ServerGameDispatcher : public Singleton<ServerGameDispatcher> {
public:
    friend class Singleton<ServerGameDispatcher>;

private:
    ServerGameDispatcher();
    ~ServerGameDispatcher();

public:
    void Add(RtypeGameServerTCPConnection *);
    void Remove(RtypeGameServerTCPConnection *);
    RoomService *GetRoomServiceFromID(unsigned short) const;
    RoomService *CreateRoomService(std::string const &name, unsigned short clientMaxNbr,
                                   unsigned short mapID);
    std::list<RtypeGameServerTCPConnection *>   GetServerList() const;

private:
    std::list<RtypeGameServerTCPConnection *>   serverList;
};

#endif //RTYPE_SERVERGAMEDISPATCHER_HPP
