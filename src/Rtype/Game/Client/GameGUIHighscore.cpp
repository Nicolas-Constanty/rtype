//
// Created by gouet_v on 12/20/16.
//

#include "Rtype/Game/Client/GameGUIHighscore.hpp"

GameGUIHighscore::GameGUIHighscore(SaltyEngine::GameObject *const gameObj) : SaltyBehaviour("GUIHighscore", gameObj) {
    highscoreLabel = gameObject->AddComponent<SaltyEngine::GUI::SFML::Label>("00000000", 25,
                                                                             SaltyEngine::SFML::AssetManager::Instance().GetFont("arial"));
}

GameGUIHighscore::~GameGUIHighscore() {

}

void GameGUIHighscore::Start() {
}

void GameGUIHighscore::FixedUpdate() {
}

void GameGUIHighscore::DisplayHighScore(int highscore) {
    std::string value = "00000000";
    value += std::to_string(highscore);
    while (value.size() > 8) {
        value.erase(0, 1);
    }
    highscoreLabel->SetText(value);
}
