#include <SaltyEngine/SFML/Sprite.hpp>
#include "Rtype/Game/Client/GameGUIBeam.hpp"

GameGUIBeam::GameGUIBeam(SaltyEngine::GameObject *const gameObj) : SaltyBehaviour("GUIBeam", gameObj)  {
    gameObject->AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite(this->spriteInit), SaltyEngine::Layout::gui);
    beamAnimation = gameObject->AddComponent<SaltyEngine::SFML::Animation>(false, SaltyEngine::AnimationConstants::WrapMode::ONCE);
    beamAnimation->AddClip(SaltyEngine::SFML::AssetManager::Instance().GetAnimation("GUI/Beam"), "Loading");
}

GameGUIBeam::~GameGUIBeam() {

}

void GameGUIBeam::Start() {

}

void GameGUIBeam::FixedUpdate() {
}

void GameGUIBeam::StartAnimation() {
    beamAnimation->Play("Loading");
}

void GameGUIBeam::StopAnimation() {
    beamAnimation->Stop("Loading");
}

void GameGUIBeam::ResetAnimation() {
    StopAnimation();
    this->gameObject->GetComponent<SaltyEngine::SFML::SpriteRenderer>()->SetSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite(this->spriteInit));
}
//
//void GameGUI::DisplayHighScore(int highscore) {
//    std::cout << "Highscore is : " << highscore << std::endl;
//}
