//
// Created by victor on 09/12/16.
//

#include <Common/Debug.hpp>
#include <SaltyEngine/SaltyEngine.hpp>
#include <Common/Flags.hpp>
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
    std::cout << "delete roomNetworkManager" << std::endl;
    if (clientRoomNetworkManager)
        delete clientRoomNetworkManager;
}

void RoomNetworkManager::Start() {
    if (clientRoomNetworkManager == nullptr)
        clientRoomNetworkManager = new ClientRoomNetworkManager(dispatcher);
    try {
        clientRoomNetworkManager->Connect(ip, port);
        dispatcher.setTimeout({0, 0});
        dispatcher.Watch(*clientRoomNetworkManager, Network::Core::NativeSocketIOOperationDispatcher::READ);
        m_isConnected = true;
    } catch (...) {
        m_isConnected = false;
    }
}

void RoomNetworkManager::Update() {
    if (m_isConnected) {
        dispatcher.Poll();
    }
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

void RoomNetworkManager::onGetGET(GETPackageRoom const &) {
//    std::cout << obj << std::endl;
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

void RoomNetworkManager::OnDestroy() {
    std::cout << "destroyyyy" << std::endl;
}

void RoomNetworkManager::SendJoin(unsigned short idRoom) {
    clientRoomNetworkManager->SendData(*factory.create<JOINPackageRoom>(idRoom));
}

void RoomNetworkManager::SendLeave(unsigned short id, unsigned short idRoom) {
    clientRoomNetworkManager->SendData(*factory.create<QUITPackageRoom>(id, idRoom));
}

void RoomNetworkManager::SendCreate(unsigned short roomPlayerMax, std::string const &name, unsigned short mapID) {
    clientRoomNetworkManager->SendData(*factory.create<CREATEPackageRoom>(0, roomPlayerMax, name, 0, mapID));
}

void RoomNetworkManager::SendLaunch(unsigned short idRoom) {
    clientRoomNetworkManager->SendData(*factory.create<LAUNCHPackageRoom>(idRoom));
}

void RoomNetworkManager::SendMsg(unsigned short idRoom, std::string const &msg) {
    clientRoomNetworkManager->SendData(*factory.create<CHATPackageRoom>(idRoom, msg));
}

void RoomNetworkManager::SetUDPIP(std::string const &ip) {
    udpIP = ip;
}

void RoomNetworkManager::SetUDPPort(unsigned int port) {
    udpPort = port;
}

void RoomNetworkManager::SetUDPSecret(unsigned int secret) {
    udpSecret = secret;
}

std::string const &RoomNetworkManager::GetUDPIP() const {
    return udpIP;
}

unsigned int RoomNetworkManager::GetUDPPort() const {
    return udpPort;
}

unsigned int RoomNetworkManager::GetUDPSecret() const {
    return udpSecret;
}
