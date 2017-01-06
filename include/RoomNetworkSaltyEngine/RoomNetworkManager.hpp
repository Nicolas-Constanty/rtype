//
// Created by victor on 09/12/16.
//

#ifndef RTYPE_ROOMNETWORKMANAGER_HPP
#define RTYPE_ROOMNETWORKMANAGER_HPP

#include "RoomNetworkSaltyEngine/ClientRoomNetworkManager.hpp"
#include <Network/Core/NativeSocketIOOperationDispatcher.hpp>
#include "SaltyEngine/SaltyBehaviour.hpp"
#include "Common/DLLexport.hpp"

class PREF_EXPORT RoomNetworkManager : public SaltyEngine::SaltyBehaviour, public ITransitionNetworkManager {
public:
    RoomNetworkManager(SaltyEngine::GameObject * const gameObject, std::string const &ip, unsigned short port);
    //RoomNetworkManager(std::string const &name, SaltyEngine::GameObject * const gameObject, std::string const &ip, unsigned short port);
    virtual ~RoomNetworkManager();

public:
    void Start();
    void Update();
	void SendAuthenticate(const std::string &name);
    void SendJoin(unsigned short idRoom);
    void SendLeave(unsigned short id, unsigned short idRoom);
    void SendCreate(unsigned short roomPlayerMax, std::string const &name, unsigned short mapID);
    void SendLaunch(unsigned short idRoom);
    void SendMsg(unsigned short idRoom, std::string const &msg);

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

public:
	void SetUDPIP(std::string const &);
	void SetUDPPort(unsigned int);
	void SetUDPSecret(unsigned int);

	std::string const &GetUDPIP() const;
	unsigned int GetUDPPort() const;
	unsigned int GetUDPSecret() const;

private:
    std::string                                         ip;
    unsigned short                                      port;
    mutable ClientRoomNetworkManager                    *clientRoomNetworkManager = nullptr;
    mutable Network::Core::NativeSocketIOOperationDispatcher    dispatcher;
	RoomPackageFactory									factory;
	bool 												m_isConnected = false;
	std::string udpIP = "127.0.0.1";
	unsigned int udpPort = 0;
	unsigned int udpSecret = 0;
};

#endif //RTYPE_ROOMNETWORKMANAGER_HPP
