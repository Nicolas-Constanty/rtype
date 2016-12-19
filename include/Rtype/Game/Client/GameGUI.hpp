//
// Created by gouet_v on 12/19/16.
//

#ifndef RTYPE_GAMEGUI_HPP
#define RTYPE_GAMEGUI_HPP

#include "SaltyEngine/SFML.hpp"
#include "SaltyEngine/SaltyBehaviour.hpp"
#include "SaltyEngine/GameObject.hpp"

class GameGUI : public SaltyEngine::SaltyBehaviour {
public:
    GameGUI(SaltyEngine::GameObject * const gameObj);
    virtual ~GameGUI();

public:
    void Start();
    void FixedUpdate();

public:
    void StartAnimation();
    void StopAnimation();
    void ResetAnimation();

private:
    SaltyEngine::SFML::Animation *beamAnimation;

public:
    virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj) {
        return new GameGUI(obj);
    }

private:
    const std::string spriteInit = "GUI_Beam/beam1";
    bool loop = true;
};


#endif //RTYPE_GAMEGUI_HPP
