//
// Created by gouet_v on 12/11/16.
//

#ifndef RTYPE_GAMEOBJECTCONTAINER_H
#define RTYPE_GAMEOBJECTCONTAINER_H

#include <map>
#include <SaltyEngine/GameObject.hpp>

class PREF_EXPORT GameObjectContainer {
public:
    GameObjectContainer();
    ~GameObjectContainer();

public:
    SaltyEngine::GameObject *operator[](unsigned short serverID) const;
    unsigned short GetServerObjectID(SaltyEngine::GameObject *) const;
    SaltyEngine::GameObject *GetMateObjectID(int serverID) const;

public:
    int    Add(unsigned short serverID, SaltyEngine::GameObject *);
    int     AddMate(int serverID, SaltyEngine::GameObject *);

private:
    std::map<unsigned short, unsigned short> idsServer;
    std::map<unsigned short, unsigned short> idsClient;
    std::map<int, unsigned short> idsMate;
};

#endif //RTYPE_GAMEOBJECTCONTAINER_H
