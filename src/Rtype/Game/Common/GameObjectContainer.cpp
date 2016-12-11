//
// Created by gouet_v on 12/11/16.
//

#include <Rtype/Game/Common/GameObjectContainer.hpp>
#include <SaltyEngine/SaltyEngine.hpp>

GameObjectContainer::GameObjectContainer() {

}

GameObjectContainer::~GameObjectContainer() {

}

SaltyEngine::GameObject *GameObjectContainer::operator[](unsigned short serverID) const {
    std::map<unsigned short, unsigned short>::const_iterator it = idsServer.find(serverID);

    if (it != idsServer.end()) {
        SaltyEngine::AScene *scene = SaltyEngine::SaltyEngine::Instance().GetCurrentScene();
        if (scene) {
            std::cout << "FIND scene !" << std::endl;
            return scene->FindById(it->second);
        }
    }
    return (NULL);
}

void GameObjectContainer::Add(unsigned short serverID, SaltyEngine::GameObject *gameObject) {
    idsServer[serverID] = static_cast<unsigned short>(gameObject->GetInstanceID());
    idsClient[static_cast<unsigned short>(gameObject->GetInstanceID())] = serverID;
}

unsigned short GameObjectContainer::GetServerObjectID(SaltyEngine::GameObject *gameObject) const {
    std::map<unsigned short, unsigned short>::const_iterator it = idsClient.find(static_cast<unsigned short>(gameObject->GetInstanceID()));

    if (it != idsClient.end()) {
        return it->second;
    }
    throw std::runtime_error("unknown obj");
}