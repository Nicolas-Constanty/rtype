//
// Created by gouet_v on 12/11/16.
//

#ifndef RTYPE_GAMEOBJECTCONTAINER_H
#define RTYPE_GAMEOBJECTCONTAINER_H

#include <map>
#include <SaltyEngine/GameObject.hpp>

class GameObjectContainer {
public:
    GameObjectContainer();
    ~GameObjectContainer();

public:
    SaltyEngine::GameObject *operator[](unsigned short serverID) const;
    unsigned short GetServerObjectID(SaltyEngine::GameObject *) const;

public:
    void    Add(unsigned short serverID, SaltyEngine::GameObject *);

private:
    std::map<unsigned short, unsigned short> idsServer;
    std::map<unsigned short, unsigned short> idsClient;
};

#endif //RTYPE_GAMEOBJECTCONTAINER_H
