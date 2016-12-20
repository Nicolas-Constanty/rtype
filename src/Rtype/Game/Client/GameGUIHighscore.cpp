//
// Created by gouet_v on 12/20/16.
//

#include "Rtype/Game/Client/GameGUIHighscore.hpp"

GameGUIHighscore::GameGUIHighscore(SaltyEngine::GameObject *const gameObj) : SaltyBehaviour("GUIHighscore", gameObj) {
    gameObject->AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("Laser/simple"), SaltyEngine::Layout::gui);
}

GameGUIHighscore::~GameGUIHighscore() {

}

void GameGUIHighscore::Start() {
}

void GameGUIHighscore::FixedUpdate() {
}

void GameGUIHighscore::DisplayHighScore(int highscore) {
    std::cout << "highscore is == " << highscore << std::endl;
}
