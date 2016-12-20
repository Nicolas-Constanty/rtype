//
// Created by gaspar_q on 12/12/16.
//

#ifndef RTYPE_RTYPENETWORKFACTORY_HPP
#define RTYPE_RTYPENETWORKFACTORY_HPP

#include <SaltyEngine/GameObject.hpp>

class RtypeNetworkFactory
{
public:
    static SaltyEngine::GameObject *Create(unsigned short id, SaltyEngine::Vector const &pos, float rotation);
    static unsigned short GetIDFromName(std::string const &);
//    static std::string GetStringFromID(unsigned short);
//    static unsigned short GetMateColorFromPlayerID(int playerID);
//    static bool IsMateColor(unsigned short);

private:
    static const std::map<unsigned short, std::string>  rtypeObjects;
};


#endif //RTYPE_RTYPENETWORKFACTORY_HPP
