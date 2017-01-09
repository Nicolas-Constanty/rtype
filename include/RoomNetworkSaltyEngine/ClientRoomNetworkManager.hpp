//
// Created by victor on 09/12/16.
//

#ifndef RTYPE_CLIENTROOMNETWORKMANAGER_HPP
#define RTYPE_CLIENTROOMNETWORKMANAGER_HPP

#include <Network/TCP/ATCPServer.hpp>
#include <Network/TCP/ATCPClient.hpp>
#include "Common/DLLexport.hpp"
#include <Protocol/Room/RoomPackageFactory.hpp>
#include "Protocol/Room/RoomPackageFactory.hpp"
#include "Protocol/Room/IProtocolRoomHandler.hpp"
#include "Protocol/Room/RTypeProtocolRoomManager.hpp"
#include "Protocol/Room/ProtocolPrintRoomPackage.hpp"
#include "ITransitionNetworkManager.hpp"

class PREF_EXPORT ClientRoomNetworkManager : public Network::TCP::ATCPClient, public IProtocolRoomHandler
{
public:
    ClientRoomNetworkManager(Network::Core::NativeSocketIOOperationDispatcher &dispatcher);
    ClientRoomNetworkManager(Network::Core::BasicConnection &ref);
    virtual ~ClientRoomNetworkManager();

public:
    virtual bool OnDataReceived(unsigned int len);
    virtual bool OnDataSent(unsigned int len);
    virtual bool OnStart();

public:
    virtual void onGetAUTHENTICATEPackage(AUTHENTICATEPackageRoom const &obj);
    virtual void onGetCREATEPackage(CREATEPackageRoom const &obj);
    virtual void onGetJOINPackage(JOINPackageRoom const &obj);
    virtual void onGetQUITPackage(QUITPackageRoom const &obj);
    virtual void onGetPLUGGEDPackage(PLUGGEDPackageRoom const &obj);
    virtual void onGetSWAPPackage(SWAPPackageRoom const &obj);
    virtual void onGetGETPackage(GETPackageRoom const &obj);
    virtual void onGetFAILUREPackage(FAILUREPackageRoom const &obj);
    virtual void onGetLAUNCHPackage(LAUNCHPackageRoom const &obj);
    virtual void onGetDELETEPackage(DELETEPackageRoom const &obj);
    virtual void onGetCHATPackage(CHATPackageRoom const &obj);

public:
    void SetTransitionNetworkManager(ITransitionNetworkManager *manager) const;
    ITransitionNetworkManager const*GetTransitionNetworkManager(void) const;
    std::list<GETPackageRoom *> const &GetPackages() const;
    void ClearPackagesGET() const;

private:
    RTypeProtocolRoomManager protocolRoomManager;
    RoomPackageFactory factory;
    mutable ITransitionNetworkManager   *transitionNetworkManager = NULL;
    mutable std::list<GETPackageRoom *> getPackages;

public:
    mutable bool canAddGETPackage = true;
};

#endif //RTYPE_CLIENTROOMNETWORKMANAGER_HPP
