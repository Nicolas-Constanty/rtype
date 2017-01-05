//
// Created by victor on 09/12/16.
//

#include "RoomNetworkSaltyEngine/ClientRoomNetworkManager.hpp"

ClientRoomNetworkManager::ClientRoomNetworkManager(Network::Core::NativeSocketIOOperationDispatcher &dispatcher)
        : Network::TCP::ATCPClient(dispatcher), protocolRoomManager(*this)
{
    std::cout << "constructor ClientRoomNetwrokManager" << std::endl;
}

ClientRoomNetworkManager::ClientRoomNetworkManager(Network::Core::BasicConnection &ref)
        : Network::TCP::ATCPClient(ref.Dispatcher()), protocolRoomManager(*this)
{
    std::cout << "constructor ClientRoomNetwrokManager cpy" << std::endl;
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
    if (transitionNetworkManager)
        transitionNetworkManager->onGetAUTHENTICATE(obj);
//        this->SendData(*(factory.create<CREATEPackageRoom>(0, 2, "koalas", 0, 1)));
    buff += sizeof(obj);
//        this->SendData(*(factory.create<JOINPackageRoom>(1)));
}

void ClientRoomNetworkManager::onGetCREATEPackage(CREATEPackageRoom const &obj) {
//    std::cout << obj << std::endl;
    if (transitionNetworkManager)
        transitionNetworkManager->onGetCREATE(obj);
    buff += sizeof(obj);
}
void ClientRoomNetworkManager::onGetJOINPackage(JOINPackageRoom const &obj) {
    std::cout << obj << std::endl;
    if (transitionNetworkManager)
        transitionNetworkManager->onGetJOIN(obj);
    buff += sizeof(obj);
}
void ClientRoomNetworkManager::onGetQUITPackage(QUITPackageRoom const &obj) {
    std::cout << obj << std::endl;
    if (transitionNetworkManager)
        transitionNetworkManager->onGetQUIT(obj);
    buff += sizeof(obj);
}
void ClientRoomNetworkManager::onGetPLUGGEDPackage(PLUGGEDPackageRoom const &obj) {
//    std::cout << obj << std::endl;
    if (transitionNetworkManager)
        transitionNetworkManager->onGetPLUGGED(obj);
    buff += sizeof(obj);
}
void ClientRoomNetworkManager::onGetSWAPPackage(SWAPPackageRoom const &obj) {
//    std::cout << obj << std::endl;
    if (transitionNetworkManager)
        transitionNetworkManager->onGetSWAP(obj);
    buff += sizeof(obj);
}
void ClientRoomNetworkManager::onGetGETPackage(GETPackageRoom const &obj) {
//    std::cout << obj << std::endl;
    if (canAddGETPackage) {
        GETPackageRoom *getPackageRoom = new GETPackageRoom(obj.roomPlayer, obj.roomPlayerMax, std::string(obj.name),
                                                            obj.roomID, obj.mapID, obj.launch);
        this->getPackages.push_back(getPackageRoom);
    }
    if (transitionNetworkManager)
        transitionNetworkManager->onGetGET(obj);
    buff += sizeof(obj);
}
void ClientRoomNetworkManager::onGetFAILUREPackage(FAILUREPackageRoom const &obj) {
//    std::cout << obj << std::endl;
    if (transitionNetworkManager)
        transitionNetworkManager->onGetFAILURE(obj);
    buff += sizeof(obj);
}
void ClientRoomNetworkManager::onGetLAUNCHPackage(LAUNCHPackageRoom const &obj) {
//    std::cout << obj << std::endl;
    if (transitionNetworkManager)
        transitionNetworkManager->onGetLAUNCH(obj);
    buff += sizeof(obj);
}

void ClientRoomNetworkManager::onGetDELETEPackage(DELETEPackageRoom const &obj) {
//    std::cout << obj << std::endl;
    std::list<GETPackageRoom *>::iterator it = getPackages.begin();
    while (it != getPackages.end()) {
        if ((*it)->roomID == obj.roomID) {
            delete *it;
            getPackages.erase(it);
            buff += sizeof(obj);
            return ;
        }
        ++it;
    }
    if (transitionNetworkManager)
        transitionNetworkManager->onGetDELETE(obj);
    buff += sizeof(obj);
}

void ClientRoomNetworkManager::onGetCHATPackage(CHATPackageRoom const &obj) {
//    std::cout << obj << std::endl;
    if (transitionNetworkManager)
        transitionNetworkManager->onGetCHAT(obj);
    buff += sizeof(obj);
}

void ClientRoomNetworkManager::SetTransitionNetworkManager(ITransitionNetworkManager *manager) const {
    transitionNetworkManager = manager;
}

ITransitionNetworkManager const *ClientRoomNetworkManager::GetTransitionNetworkManager(void) const
{
    return transitionNetworkManager;
}

std::list<GETPackageRoom *> const &ClientRoomNetworkManager::GetPackages() const {
    return this->getPackages;
}

void ClientRoomNetworkManager::ClearPackagesGET() const {
    std::list<GETPackageRoom *>::iterator it = getPackages.begin();
    while (it != getPackages.end()) {
//        if ((*it)->roomID == obj.roomID) {
            delete *it;
            it = getPackages.erase(it);
//            buff += sizeof(obj);
//            return ;
//        }
//        ++it;
    }
//    this->getPackages.clear();
}