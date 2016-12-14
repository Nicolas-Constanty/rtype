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
        {4, "MonsterWalker"}
};

SaltyEngine::GameObject *RtypeNetworkFactory::Create(unsigned short id, SaltyEngine::Vector const &pos)
{
    std::map<unsigned short, std::string>::const_iterator   it = rtypeObjects.find(id);

    if (it != rtypeObjects.end())
    {
        SaltyEngine::GameObject *object = dynamic_cast<SaltyEngine::GameObject*>(SaltyEngine::Instantiate(it->second, pos, 0));

//        if (object)
//        {
//            if (id == 1)
//            {
//                SaltyEngine::PlayerController   *compo = object->GetComponent<SaltyEngine::PlayerController>();
//
//                if (compo)
//                {
//                    compo->enabled = false;
//                }
//            }
//        }
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
