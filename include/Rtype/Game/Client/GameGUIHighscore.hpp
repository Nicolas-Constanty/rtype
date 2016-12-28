//
// Created by gouet_v on 12/20/16.
//

#ifndef RTYPE_GAMEGUIHIGHSCORE_HPP
#define RTYPE_GAMEGUIHIGHSCORE_HPP

#include "SaltyEngine/SFML.hpp"
#include "SaltyEngine/SaltyBehaviour.hpp"
#include "SaltyEngine/GameObject.hpp"

class PREF_EXPORT GameGUIHighscore : public SaltyEngine::SaltyBehaviour {
public:
    GameGUIHighscore(SaltyEngine::GameObject * const gameObj);
    virtual ~GameGUIHighscore();

public:
    void Start();
    void FixedUpdate();

public:
    // display highscore
    void DisplayHighScore(int highscore);

private:
    SaltyEngine::SFML::Animation *beamAnimation;

public:
    virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj) {
        return new GameGUIHighscore(obj);
    }

private:
    SaltyEngine::GUI::SFML::Label *highscoreLabel = NULL;

};


#endif //RTYPE_GAMEGUIHIGHSCORE_HPP
