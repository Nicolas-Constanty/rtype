//
// Created by gouet_v on 12/30/16.
//

#include "Rtype/Game/Client/GameGUILives.hpp"

GameGUILives::GameGUILives(SaltyEngine::GameObject *const gameObj) : SaltyBehaviour("GameGUILives", gameObj) {
    livesLabel = gameObject->AddComponent<SaltyEngine::GUI::SFML::Label>("Lives : 3", 25,
                                                                         SaltyEngine::SFML::AssetManager::Instance().GetFont("arial"));
}

GameGUILives::~GameGUILives() {

}

void GameGUILives::Start() {
}

void GameGUILives::FixedUpdate() {
}

void GameGUILives::DisplayLives(int lives) {
    std::string value = "Lives : " + std::to_string(lives);
//    value += std::to_string(highscore);
//    while (value.size() > 8) {
//        value.erase(0, 1);
//    }
    livesLabel->SetText(value);
}
