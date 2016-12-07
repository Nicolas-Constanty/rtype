//
// Created by victor on 29/11/16.
//

#ifndef RTYPE_RTYPEGAMESERVERTCPCONNECTION_HPP
#define RTYPE_RTYPEGAMESERVERTCPCONNECTION_HPP

#include <memory>
#include <Network/TCP/ATCPClient.hpp>
#include <Protocol/Server/RTypeProtocolServerManager.hpp>
#include <Protocol/Server/ServerPackageFactory.hpp>
#include "Protocol/Server/IProtocolServerHandler.hpp"
#include "ServerRoom/RoomService.hpp"

class RtypeGameServerTCPConnection : public Network::TCP::ATCPClient,
                                     public IProtocolServerHandler {
public:
    RtypeGameServerTCPConnection(Network::Core::NativeSocketIOOperationDispatcher &dispatcher);
    RtypeGameServerTCPConnection(Network::TCP::ATCPClient const &ref, unsigned int id, unsigned short roomNumberMax);
    virtual ~RtypeGameServerTCPConnection();

public:
    virtual bool OnDataReceived(unsigned int len);
    virtual bool OnDataSent(unsigned int len);
    virtual bool OnStart();
    virtual void OnDisconnect();

public:
    virtual void onGetAUTHENTICATEPackage(AUTHENTICATEPackageServer const &);
    virtual void onGetLAUNCHPackage(LAUNCHPackageServer const &);
    virtual void onGetSTATUSPackage(STATUSPackageServer const &);

public:
    RoomService            *AddRoomService(std::string const &name, unsigned short clientMaxNbr, unsigned short mapID);
    void                    RemoveRoomService(RoomService *);

public:
    RoomService     *GetRoomFromID(unsigned short id) const;
    unsigned int    getID() const;
    unsigned short  getRoomNumberMax() const;
    unsigned long   getActualRoomNumber() const;
    bool            isFull() const;
    std::list<RoomService *> RoomsService();

private:
    RTypeProtocolServerManager  protocolServerManager;
    unsigned int                id;
    unsigned short              roomNumberMax;
    ServerPackageFactory        serverPackageFactory;
    std::list<std::unique_ptr<RoomService>>    roomServiceList;

};

#endif //RTYPE_RTYPEGAMESERVERTCPCONNECTION_HPP
