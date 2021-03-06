//
// Created by gaspar_q on 12/12/16.
//

#include <Prefabs/Player/PlayerController.hpp>
#include "Rtype/Game/Common/RtypeNetworkFactory.hpp"

//todo fill it
const std::map<unsigned short, std::string>  RtypeNetworkFactory::rtypeObjects = {
        {0, "Player"},
        {1, "Mate"},
        {2, "Monster"},
        {3, "Laser"},
        {4, "MonsterWalker"},
        {5, "EnemyBullet"},
        {6, "MissileMedusa"},
        {7, "Beam"},
        {8, "MonsterFlying"},
        {9, "MonsterNeunoeil"},
        {10, "MissileNeunoeil"},
        {11, "Pod"},
        {12, "MissileHoming"},
        {13, "SpiralBonus"},
        {14, "BlockSimple"},
        {15, "LaserSpiral"},
        {16, "MonsterMedusa"}
};

SaltyEngine::GameObject *RtypeNetworkFactory::Create(unsigned short id, SaltyEngine::Vector const &pos, float rotation)
{
    std::map<unsigned short, std::string>::const_iterator   it = rtypeObjects.find(id);

    if (it != rtypeObjects.end())
    {
        SaltyEngine::GameObject *object = dynamic_cast<SaltyEngine::GameObject*>(SaltyEngine::Instantiate(it->second, pos, rotation));
        if (object)
            return object;
    }
    throw std::runtime_error("No such object for id => " + std::to_string(id));
}

unsigned short RtypeNetworkFactory::GetIDFromName(std::string const &id) {

    std::map<unsigned short, std::string>::const_iterator   it;

    it = std::find_if(rtypeObjects.begin(), rtypeObjects.end(), [id](std::pair<unsigned short, std::string> const &pair){
        return (id == pair.second);
    });
    if (it != rtypeObjects.end()) {
        return (it->first);
    }
    throw std::runtime_error("No suck object for id =>" + id);
    //return 0;
}

std::string const &RtypeNetworkFactory::GetStringFromID(unsigned short id) {
    std::map<unsigned short, std::string>::const_iterator it = rtypeObjects.find(id);
    if (it != rtypeObjects.end()) {
        return (it->second);
    }
    throw new std::runtime_error("No such object for id: " + std::to_string(id));
}

//
//bool RtypeNetworkFactory::IsMateColor(unsigned short id) {
//    return id >= 8 && id <= 11;
//}
//
//
//unsigned short RtypeNetworkFactory::GetMateColorFromPlayerID(int playerID) {
//    return (static_cast<unsigned short>(playerID + 8));
//}
