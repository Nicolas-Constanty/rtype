//
// Created by victor on 09/12/16.
//

#include "RoomNetworkSaltyEngine/RoomNetworkManager.hpp"

RoomNetworkManager::RoomNetworkManager(SaltyEngine::GameObject *const gameObject, std::string const &ip,
                                       unsigned short port) :
        SaltyEngine::SaltyBehaviour("RoomNetworkManager", gameObject), ip(ip), port(port), clientRoomNetworkManager(nullptr) {

}

//RoomNetworkManager::RoomNetworkManager(std::string const &name, SaltyEngine::GameObject *const gameObject,
//                                       std::string const &ip, unsigned short port)
//        : SaltyEngine::SaltyBehaviour(name, gameObject), ip(ip), port(port), clientRoomNetworkManager(NULL) {
//
//}

RoomNetworkManager::~RoomNetworkManager() {
    if (clientRoomNetworkManager)
        delete clientRoomNetworkManager;
}

void RoomNetworkManager::Start() {
    clientRoomNetworkManager = new ClientRoomNetworkManager(dispatcher);
}

void RoomNetworkManager::Update() {
    if (!m_isConnected)
    {
        try
        {
            clientRoomNetworkManager->Connect(ip, port);
            dispatcher.setTimeout({0, 0});
            dispatcher.Watch(*clientRoomNetworkManager, Network::Core::NativeSocketIOOperationDispatcher::READ);
            m_isConnected = true;
        }
        catch (...)
        {
            m_isConnected = false;
        }
    }
    else
        dispatcher.Poll();
}

void RoomNetworkManager::SendAuthenticate(const std::string &name)
{
	clientRoomNetworkManager->SendData(*factory.create<AUTHENTICATEPackageRoom>(name, 0));
}

SaltyEngine::Component *RoomNetworkManager::CloneComponent(SaltyEngine::GameObject *const obj)
{
    return new RoomNetworkManager(obj, ip, port);
}
