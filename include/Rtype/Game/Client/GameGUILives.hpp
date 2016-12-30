//
// Created by gouet_v on 12/30/16.
//

#ifndef RTYPE_GAMEGUILIVES_HPP
#define RTYPE_GAMEGUILIVES_HPP

#include "SaltyEngine/SFML.hpp"
#include "SaltyEngine/SaltyBehaviour.hpp"
#include "SaltyEngine/GameObject.hpp"

class PREF_EXPORT GameGUILives : public SaltyEngine::SaltyBehaviour {
public:
    GameGUILives(SaltyEngine::GameObject * const gameObj);
    virtual ~GameGUILives();

public:
    void Start();
    void FixedUpdate();

public:
    void DisplayLives(int lives);

public:
    virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj) {
        return new GameGUILives(obj);
    }

private:
    SaltyEngine::GUI::SFML::Label *livesLabel = NULL;

};
#endif //RTYPE_GAMEGUILIVES_HPP
