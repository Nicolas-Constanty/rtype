//
// Created by victor on 09/12/16.
//

#ifndef RTYPE_ROOMNETWORKMANAGER_HPP
#define RTYPE_ROOMNETWORKMANAGER_HPP

#include "RoomNetworkSaltyEngine/ClientRoomNetworkManager.hpp"
#include <Network/Core/NativeSocketIOOperationDispatcher.hpp>
#include "SaltyEngine/SaltyBehaviour.hpp"
#include "Common/DLLexport.hpp"

class LIB_EXPORT RoomNetworkManager : public SaltyEngine::SaltyBehaviour, public ITransitionNetworkManager {
public:
    RoomNetworkManager(SaltyEngine::GameObject * const gameObject, std::string const &ip, unsigned short port);
    //RoomNetworkManager(std::string const &name, SaltyEngine::GameObject * const gameObject, std::string const &ip, unsigned short port);
    virtual ~RoomNetworkManager();

public:
    void Start();
    void Update();
	void SendAuthenticate(const std::string &name);

	SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject *const obj) override;

public:
	virtual void onGetAUTHENTICATE(AUTHENTICATEPackageRoom const &);
	virtual void onGetCREATE(CREATEPackageRoom const &);
	virtual void onGetJOIN(JOINPackageRoom const &);
	virtual void onGetQUIT(QUITPackageRoom const &);
	virtual void onGetPLUGGED(PLUGGEDPackageRoom const &);
	virtual void onGetSWAP(SWAPPackageRoom const &);
	virtual void onGetGET(GETPackageRoom const &);
	virtual void onGetFAILURE(FAILUREPackageRoom const &);
	virtual void onGetLAUNCH(LAUNCHPackageRoom const &);
	virtual void onGetDELETE(DELETEPackageRoom const &);
	virtual void onGetCHAT(CHATPackageRoom const &);

    ClientRoomNetworkManager const*GetNetworkManager(void) const;

	void OnDestroy() override;


private:
    std::string                                         ip;
    unsigned short                                      port;
    mutable ClientRoomNetworkManager                    *clientRoomNetworkManager = nullptr;
    mutable Network::Core::NativeSocketIOOperationDispatcher    dispatcher;
	RoomPackageFactory									factory;
	bool 												m_isConnected = false;
};

#endif //RTYPE_ROOMNETWORKMANAGER_HPP
