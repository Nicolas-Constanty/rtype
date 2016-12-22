//
// Created by gouet_v on 12/21/16.
//

#include "Rtype/Game/Client/EndScreen.hpp"

EndScreen::EndScreen(SaltyEngine::GameObject *const gameObj) : SaltyBehaviour("EndScreen", gameObj) {

}

EndScreen::~EndScreen() {

}

void EndScreen::Start() {
//    SaltyBehaviour::Start();
}

void EndScreen::VictoryScreen() {
    gameObject->AddComponent<SaltyEngine::GUI::SFML::Label>("Victoire !", 100,
                                                            SaltyEngine::SFML::AssetManager::Instance().GetFont("arial"),
                                                            sf::Color::White);
}

void EndScreen::DefeatScreen() {
    gameObject->AddComponent<SaltyEngine::GUI::SFML::Label>("Defaite !", 100,
                                                            SaltyEngine::SFML::AssetManager::Instance().GetFont("arial"),
                                                            sf::Color::White);
}

void EndScreen::FixedUpdate() {
//    SaltyBehaviour::FixedUpdate();
}

void EndScreen::SetQuitAction() {
//    InputKey::AddAction("Fire", new Input::Action(Input::KeyCode::Space, std::make_pair<unsigned int, int>(0, 1)));
}
