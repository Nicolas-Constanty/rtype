//
// Created by victor on 06/12/16.
//

#ifndef RTYPE_BASETCP_HPP
#define RTYPE_BASETCP_HPP

#include <memory>
#include <Network/Core/NativeSocketIOOperationDispatcher.hpp>
#include <unistd.h>
#include <vector>
#include <sys/select.h>
#include <sstream>
#include <queue>
#include <cstdlib>
#include <Network/TCP/ATCPClient.hpp>
#include <Protocol/Server/IProtocolServerHandler.hpp>
#include <Protocol/Server/ServerPackageFactory.hpp>
#include <Protocol/Server/RTypeProtocolServerManager.hpp>
#include <Protocol/Server/ProtocolPrintServerPackage.hpp>
#include <Thread/ThreadPool.hpp>
#include "Thread/StdThread.hpp"
#include "ServerGame/CreateRoomGameServer/Lobby.hpp"
#include "ServerGame/CreateRoomGameServer/ILobbyHandler.hpp"

class ClientGameRooms : public Network::TCP::ATCPClient, public IProtocolServerHandler, public ILobbyHandler
{
public:
    ClientGameRooms(Network::Core::NativeSocketIOOperationDispatcher &dispatcher, std::string const &ip, size_t thread);
    virtual ~ClientGameRooms();

public:
    virtual void OnDataReceived(unsigned int len);
    virtual void onGetAUTHENTICATEPackage(AUTHENTICATEPackageServer const &obj);
    virtual void onGetLAUNCHPackage(LAUNCHPackageServer const &obj);
    virtual void onGetSTATUSPackage(STATUSPackageServer const &obj);
    virtual void OnDataSent(unsigned int len);
    virtual void OnStart();

public:
    virtual void OnProcessEnd(int status, void *data);
    virtual void OnProcessBegin(void *data);

private:
    RTypeProtocolServerManager              protocolServerManager;
    ServerPackageFactory                    factory;
    size_t                                  threadNbr;
    ThreadPool<StdThread>                   pool;
    unsigned int                            ip;
    std::vector<std::unique_ptr<Lobby> >    lobbies;
    IMutex                                  *mutex;
    IMutex                                  *__mutex;
    std::queue<PackageServerHeader *>       _packageToSend;
};

#endif //RTYPE_BASETCP_HPP
