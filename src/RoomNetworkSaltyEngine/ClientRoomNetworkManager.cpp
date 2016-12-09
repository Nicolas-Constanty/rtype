//
// Created by victor on 09/12/16.
//

#include "RoomNetworkSaltyEngine/ClientRoomNetworkManager.hpp"

ClientRoomNetworkManager::ClientRoomNetworkManager(Network::Core::NativeSocketIOOperationDispatcher &dispatcher)
        : Network::TCP::ATCPClient(dispatcher), protocolRoomManager(*this)
{

}

ClientRoomNetworkManager::ClientRoomNetworkManager(Network::Core::BasicConnection &ref)
        : Network::TCP::ATCPClient(ref.Dispatcher()), protocolRoomManager(*this)
{

}

ClientRoomNetworkManager::~ClientRoomNetworkManager()
{
    std::cout << "\e[31mDestructor called\e[0m" << std::endl;
}

bool ClientRoomNetworkManager::OnDataReceived(unsigned int)
{
    std::cout << "Receiving " << buff << std::endl;
    while (protocolRoomManager.handleProtocol(buff.buff(), buff.getLength())) {
        std::cout << "unknown cmd" << std::endl;
    }
    return true;
}

bool ClientRoomNetworkManager::OnDataSent(unsigned int len)
{
    std::cout << "Number of bytes sent: " << len << std::endl;
    return (true);
}

bool ClientRoomNetworkManager::OnStart() {
//    this->SendData(*(factory.create<AUTHENTICATEPackageRoom>("toto", 0)));
    return (true);
}

void ClientRoomNetworkManager::onGetAUTHENTICATEPackage(AUTHENTICATEPackageRoom const &obj) {
    std::cout << obj << std::endl;
//        this->SendData(*(factory.create<CREATEPackageRoom>(0, 2, "koalas", 0, 1)));
    buff += sizeof(obj);
//        this->SendData(*(factory.create<JOINPackageRoom>(1)));
}

void ClientRoomNetworkManager::onGetCREATEPackage(CREATEPackageRoom const &obj) {
    std::cout << obj << std::endl;
    buff += sizeof(obj);
}
void ClientRoomNetworkManager::onGetJOINPackage(JOINPackageRoom const &obj) {
    std::cout << obj << std::endl;
    buff += sizeof(obj);
}
void ClientRoomNetworkManager::onGetQUITPackage(QUITPackageRoom const &obj) {
    std::cout << obj << std::endl;
    buff += sizeof(obj);
}
void ClientRoomNetworkManager::onGetPLUGGEDPackage(PLUGGEDPackageRoom const &obj) {
    std::cout << obj << std::endl;
    buff += sizeof(obj);
}
void ClientRoomNetworkManager::onGetSWAPPackage(SWAPPackageRoom const &obj) {
    std::cout << obj << std::endl;
    buff += sizeof(obj);
}
void ClientRoomNetworkManager::onGetGETPackage(GETPackageRoom const &obj) {
    std::cout << obj << std::endl;
    buff += sizeof(obj);
}
void ClientRoomNetworkManager::onGetFAILUREPackage(FAILUREPackageRoom const &obj) {
    std::cout << obj << std::endl;
    buff += sizeof(obj);
}
void ClientRoomNetworkManager::onGetLAUNCHPackage(LAUNCHPackageRoom const &obj) {
    std::cout << obj << std::endl;
    buff += sizeof(obj);
}

void ClientRoomNetworkManager::onGetDELETEPackage(DELETEPackageRoom const &obj) {
    std::cout << obj << std::endl;
    buff += sizeof(obj);
}

void ClientRoomNetworkManager::onGetCHATPackage(CHATPackageRoom const &obj) {
    std::cout << obj << std::endl;
    buff += sizeof(obj);
}
