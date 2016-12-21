//
// Created by gouet_v on 12/21/16.
//

#ifndef RTYPE_ENDSCREEN_HPP
#define RTYPE_ENDSCREEN_HPP

#include "SaltyEngine/SFML.hpp"
#include "SaltyEngine/SaltyBehaviour.hpp"
#include "SaltyEngine/GameObject.hpp"

class EndScreen : public SaltyEngine::SaltyBehaviour {
public:
    EndScreen(SaltyEngine::GameObject * const gameObj);
    virtual ~EndScreen();

public:
    void Start();
    void FixedUpdate();

public:
    // beam animation
    void VictoryScreen();
    void DefeatScreen();

public:
    virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj) {
        return new EndScreen(obj);
    }
};

#endif //RTYPE_ENDSCREEN_HPP
