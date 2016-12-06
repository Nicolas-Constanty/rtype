//
// Created by victor on 06/12/16.
//

#ifndef RTYPE_BASETCP_HPP
#define RTYPE_BASETCP_HPP

#include <Network/Core/NativeSocketIOOperationDispatcher.hpp>
#include <unistd.h>
#include <vector>
#include <sys/select.h>
#include <sstream>
#include <cstdlib>
#include <Network/TCP/ATCPClient.hpp>
#include <Protocol/Server/IProtocolServerHandler.hpp>
#include <Protocol/Server/ServerPackageFactory.hpp>
#include <Protocol/Server/RTypeProtocolServerManager.hpp>
#include <Protocol/Server/ProtocolPrintServerPackage.hpp>

class ClientGameRooms : public Network::TCP::ATCPClient, public IProtocolServerHandler
{
public:
    ClientGameRooms(Network::Core::NativeSocketIOOperationDispatcher &dispatcher);
    ClientGameRooms(Network::Core::BasicConnection &ref);
    virtual ~ClientGameRooms();

private:
    RTypeProtocolServerManager protocolServerManager;

public:
    virtual void OnDataReceived(unsigned int len);
    virtual void onGetAUTHENTICATEPackage(AUTHENTICATEPackageServer const &obj);
    virtual void onGetLAUNCHPackage(LAUNCHPackageServer const &obj);
    virtual void onGetSTATUSPackage(STATUSPackageServer const &obj);
    virtual void OnDataSent(unsigned int len);
    virtual void OnStart();

private:
    ServerPackageFactory factory;
};

#endif //RTYPE_BASETCP_HPP
