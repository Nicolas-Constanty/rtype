//
// Created by victor on 29/11/16.
//

#ifndef RTYPE_RTYPEROOMTCPCONNECTION_HPP
#define RTYPE_RTYPEROOMTCPCONNECTION_HPP

#include <Network/TCP/ATCPClient.hpp>
#include <Protocol/Room/RTypeProtocolRoomManager.hpp>
#include "Protocol/Room/IProtocolRoomHandler.hpp"
//#include "RoomService.hpp"
#include "Protocol/Room/RoomPackageFactory.hpp"

class RoomService;

class RtypeRoomTCPConnection : public Network::TCP::ATCPClient,
                               public IProtocolRoomHandler
{
public:
    RtypeRoomTCPConnection(Network::Core::NativeSocketIOOperationDispatcher &dispatcher);
    RtypeRoomTCPConnection(Network::TCP::ATCPClient const &ref, std::string const &pseudo, unsigned int);
    virtual ~RtypeRoomTCPConnection();

public:
    virtual bool OnDataReceived(unsigned int len);
    virtual bool OnDataSent(unsigned int len);
    virtual bool OnStart();
    virtual void OnDisconnect();

private:
    bool        OnJoinRoom();
    void        OnSendGetRooms();
    void        BroadCastGETRoom();
    void        BroadCastNowGETRoom();
    void        SendQUITToAllClientsInsideTheRoom();

public:
    void        OnQUITEvent(bool canBroadcastGET);

public:
    void        removeOnRoom();

public:
    unsigned int getID() const;

public:

    virtual void onGetDELETEPackage(DELETEPackageRoom const &obj);
    virtual void onGetAUTHENTICATEPackage(AUTHENTICATEPackageRoom const &);
    virtual void onGetCREATEPackage(CREATEPackageRoom const &);
    virtual void onGetJOINPackage(JOINPackageRoom const &);
    virtual void onGetQUITPackage(QUITPackageRoom const &);
    virtual void onGetPLUGGEDPackage(PLUGGEDPackageRoom const &);
    virtual void onGetSWAPPackage(SWAPPackageRoom const &);
    virtual void onGetGETPackage(GETPackageRoom const &);
    virtual void onGetFAILUREPackage(FAILUREPackageRoom const &);
    virtual void onGetLAUNCHPackage(LAUNCHPackageRoom const &);
    virtual void onGetCHATPackage(CHATPackageRoom const &);

private:
    RTypeProtocolRoomManager protocolRoomManager;
    std::string                 pseudo;
    unsigned int                id;
    RoomPackageFactory          roomPackageFactory;
    RoomService                 *roomService;
};

#endif //RTYPE_RTYPEROOMTCPCONNECTION_HPP
