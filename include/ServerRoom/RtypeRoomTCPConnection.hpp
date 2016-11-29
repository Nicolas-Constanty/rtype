//
// Created by victor on 29/11/16.
//

#ifndef RTYPE_RTYPEROOMTCPCONNECTION_HPP
#define RTYPE_RTYPEROOMTCPCONNECTION_HPP

#include <Network/TCP/ATCPClient.hpp>
#include <Protocol/Room/RTypeProtocolRoomManager.hpp>
#include "Protocol/Room/IProtocolRoomHandler.hpp"

class RtypeRoomTCPConnection : public Network::TCP::ATCPClient,
                               public IProtocolRoomHandler
{
public:
    RtypeRoomTCPConnection(Network::Core::NativeSocketIOOperationDispatcher &dispatcher);
    RtypeRoomTCPConnection(Network::TCP::ATCPClient const &ref, std::string const &pseudo, unsigned int);
    virtual ~RtypeRoomTCPConnection();

public:
    virtual void OnDataReceived(unsigned int len);
    virtual void OnDataSent(unsigned int len);
    virtual void OnStart();

public:
    virtual void onGetAUTHENTICATEPackage(AUTHENTICATEPackageRoom const &);
    virtual void onGetCREATEPackage(CREATEPackageRoom const &);
    virtual void onGetJOINPackage(JOINPackageRoom const &);
    virtual void onGetQUITPackage(QUITPackageRoom const &);
    virtual void onGetPLUGGEDPackage(PLUGGEDPackageRoom const &);
    virtual void onGetSWAPPackage(SWAPPackageRoom const &);
    virtual void onGetGETPackage(GETPackageRoom const &);
    virtual void onGetFAILUREPackage(FAILUREPackageRoom const &);
    virtual void onGetLAUNCHPackage(LAUNCHPackageRoom const &);

private:
    RTypeProtocolRoomManager protocolRoomManager;
    std::string                 pseudo;
    unsigned int                id;
    RoomPackageFactory          roomPackageFactory;
};

#endif //RTYPE_RTYPEROOMTCPCONNECTION_HPP
