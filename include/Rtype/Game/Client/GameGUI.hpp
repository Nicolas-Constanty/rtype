//
// Created by gouet_v on 12/19/16.
//

#ifndef RTYPE_GAMEGUI_HPP
#define RTYPE_GAMEGUI_HPP

#include "SaltyEngine/SaltyBehaviour.hpp"
#include "SaltyEngine/GameObject.hpp"

class GameGUI : public SaltyEngine::SaltyBehaviour {
public:
    GameGUI(SaltyEngine::GameObject * const gameObj);
    virtual ~GameGUI();

public:
    void Start();
    void FixedUpdate();

private:


public:
    virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj) {
        return new GameGUI(obj);
    }
};


#endif //RTYPE_GAMEGUI_HPP
