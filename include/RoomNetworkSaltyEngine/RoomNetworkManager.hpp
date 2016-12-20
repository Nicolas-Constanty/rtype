//
// Created by victor on 09/12/16.
//

#ifndef RTYPE_ROOMNETWORKMANAGER_HPP
#define RTYPE_ROOMNETWORKMANAGER_HPP

#include "RoomNetworkSaltyEngine/ClientRoomNetworkManager.hpp"
#include <Network/Core/NativeSocketIOOperationDispatcher.hpp>
#include "SaltyEngine/SaltyBehaviour.hpp"

class RoomNetworkManager : public SaltyEngine::SaltyBehaviour {
public:
    RoomNetworkManager(SaltyEngine::GameObject * const gameObject, std::string const &ip, unsigned short port);
    //RoomNetworkManager(std::string const &name, SaltyEngine::GameObject * const gameObject, std::string const &ip, unsigned short port);
    virtual ~RoomNetworkManager();

public:
    void Start();
    void Update();
	void SendAuthenticate(const std::string &name);


private:
    std::string                                         ip;
    unsigned short                                      port;
    ClientRoomNetworkManager                            *clientRoomNetworkManager;
    Network::Core::NativeSocketIOOperationDispatcher    dispatcher;
	RoomPackageFactory									factory;
};

#endif //RTYPE_ROOMNETWORKMANAGER_HPP
