//
// Created by gouet_v on 12/19/16.
//

#ifndef RTYPE_GAMEGUI_HPP
#define RTYPE_GAMEGUI_HPP

#include "SaltyEngine/SFML.hpp"
#include "SaltyEngine/SaltyBehaviour.hpp"
#include "SaltyEngine/GameObject.hpp"

class PREF_EXPORT GameGUIBeam : public SaltyEngine::SaltyBehaviour {
public:
    GameGUIBeam(SaltyEngine::GameObject * const gameObj);
    virtual ~GameGUIBeam();

public:
    void Start();
    void FixedUpdate();

public:
    // beam animation
    void StartAnimation();
    void StopAnimation();
    void ResetAnimation();

public:
    // display highscore
//    void DisplayHighScore(int highscore);

private:
    SaltyEngine::SFML::Animation *beamAnimation;

public:
    virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj) {
        return new GameGUIBeam(obj);
    }

private:
    const std::string spriteInit = "GUI_Beam/beam1";
    bool loop = true;
};


#endif //RTYPE_GAMEGUI_HPP
