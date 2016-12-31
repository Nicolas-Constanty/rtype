//
// Created by victor on 09/12/16.
//

#include <Common/Debug.hpp>
#include <SaltyEngine/SaltyEngine.hpp>
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
    try {
        clientRoomNetworkManager->Connect(ip, port);
        dispatcher.setTimeout({0, 0});
        dispatcher.Watch(*clientRoomNetworkManager, Network::Core::NativeSocketIOOperationDispatcher::READ);
        m_isConnected = true;
        if (clientRoomNetworkManager->GetTransitionNetworkManager() == nullptr)
            clientRoomNetworkManager->SetTransitionNetworkManager(this);
    } catch (...) {
        m_isConnected = false;
    }
}

void RoomNetworkManager::Update() {
//    if (!m_isConnected)
//    {
////        try
////        {
////            clientRoomNetworkManager->Connect(ip, port);
////            dispatcher.setTimeout({0, 0});
////            dispatcher.Watch(*clientRoomNetworkManager, Network::Core::NativeSocketIOOperationDispatcher::READ);
////            m_isConnected = true;
////        }
////        catch (...)
////        {
////            m_isConnected = false;
////        }
//    }
//    else
    if (m_isConnected)
        dispatcher.Poll();
    else {
        Debug::PrintError("Server room not found !");
        SaltyEngine::Engine::Instance().Stop();
    }
}

void RoomNetworkManager::SendAuthenticate(const std::string &name)
{
	clientRoomNetworkManager->SendData(*factory.create<AUTHENTICATEPackageRoom>(name, 0));
}

SaltyEngine::Component *RoomNetworkManager::CloneComponent(SaltyEngine::GameObject *const obj)
{
    return new RoomNetworkManager(obj, ip, port);
}

void RoomNetworkManager::onGetAUTHENTICATE(AUTHENTICATEPackageRoom const &obj) {
    std::cout << obj << std::endl;
}

void RoomNetworkManager::onGetCREATE(CREATEPackageRoom const &obj) {
    std::cout << obj << std::endl;
}

void RoomNetworkManager::onGetJOIN(JOINPackageRoom const &obj) {
    std::cout << obj << std::endl;
}

void RoomNetworkManager::onGetQUIT(QUITPackageRoom const &obj) {
    std::cout << obj << std::endl;
}

void RoomNetworkManager::onGetPLUGGED(PLUGGEDPackageRoom const &obj) {
    std::cout << obj << std::endl;
}

void RoomNetworkManager::onGetSWAP(SWAPPackageRoom const &obj) {
    std::cout << obj << std::endl;
}

void RoomNetworkManager::onGetGET(GETPackageRoom const &obj) {
    std::cout << obj << std::endl;
}

void RoomNetworkManager::onGetFAILURE(FAILUREPackageRoom const &obj) {
    std::cout << obj << std::endl;
}

void RoomNetworkManager::onGetLAUNCH(LAUNCHPackageRoom const &obj) {
    std::cout << obj << std::endl;
}

void RoomNetworkManager::onGetDELETE(DELETEPackageRoom const &obj) {
    std::cout << obj << std::endl;
}

void RoomNetworkManager::onGetCHAT(CHATPackageRoom const &obj) {
    std::cout << obj << std::endl;
}

ClientRoomNetworkManager const *RoomNetworkManager::GetNetworkManager(void) const
{
    if (clientRoomNetworkManager == nullptr)
        clientRoomNetworkManager = new ClientRoomNetworkManager(dispatcher);
    return clientRoomNetworkManager;
}
