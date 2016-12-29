//
// Created by veyrie_f on 29/12/16.
//

#ifndef RTYPE_GAMEMANAGER_HPP
#define RTYPE_GAMEMANAGER_HPP


#include "SaltyEngine/GameObject.hpp"

class GameManager : public SaltyEngine::SaltyBehaviour
{
public:
    explicit GameManager(SaltyEngine::GameObject *obj);

    virtual ~GameManager();
    void Start() override;

public:
    virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject *const obj);
};

#endif //RTYPE_GAMEMANAGER_HPP
