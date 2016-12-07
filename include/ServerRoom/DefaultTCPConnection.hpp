//
// Created by victor on 29/11/16.
//

#ifndef RTYPE_DEFAULTTCPCONNECTION_HPP
#define RTYPE_DEFAULTTCPCONNECTION_HPP

#include <Network/TCP/ATCPClient.hpp>
#include <Protocol/Room/RTypeProtocolRoomManager.hpp>
#include <Protocol/Server/RTypeProtocolServerManager.hpp>
#include "Protocol/Room/ProtocolRoomAuthenticateHandler.hpp"
#include "Protocol/Server/ProtocolServerAuthenticateHandler.hpp"

class DefaultTCPConnection : public Network::TCP::ATCPClient,
                             public ProtocolRoomAuthenticateHandler,
                             public ProtocolServerAuthenticateHandler
{
public:
    DefaultTCPConnection(Network::Core::NativeSocketIOOperationDispatcher &dispatcher);
    DefaultTCPConnection(Network::Core::BasicConnection &ref);
    virtual ~DefaultTCPConnection();

public:
    virtual bool OnDataReceived(unsigned int len);
    virtual bool OnStart();
    virtual bool OnDataSent(unsigned int len);

public:
    virtual void onGetAUTHENTICATEPackage(AUTHENTICATEPackageRoom const &);
    virtual void onGetFAILUREPackage(FAILUREPackageRoom const &);

public:
    virtual void onGetAUTHENTICATEPackage(AUTHENTICATEPackageServer const &);

private:
    RTypeProtocolRoomManager protocolRoomManager;
    RTypeProtocolServerManager protocolServerManager;
};

#endif //RTYPE_DEFAULTTCPCONNECTION_HPP
