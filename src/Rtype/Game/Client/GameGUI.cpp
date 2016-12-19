#include <SaltyEngine/SFML/Sprite.hpp>
#include "Rtype/Game/Client/GameGUI.hpp"

GameGUI::GameGUI(SaltyEngine::GameObject *const gameObj) : SaltyBehaviour("GameGUI", gameObj)  {

}

GameGUI::~GameGUI() {

}

void GameGUI::Start() {
    gameObject->AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite(this->spriteInit), SaltyEngine::Layout::gui);
    beamAnimation = gameObject->AddComponent<SaltyEngine::SFML::Animation>(false, SaltyEngine::AnimationConstants::WrapMode::ONCE);
    beamAnimation->AddClip(SaltyEngine::SFML::AssetManager::Instance().GetAnimation("GUI/Beam"), "Loading");
    beamAnimation->Play("Loading");
}

void GameGUI::FixedUpdate() {
}

void GameGUI::StartAnimation() {
    beamAnimation->Play("Loading");
}

void GameGUI::StopAnimation() {
    beamAnimation->Stop("Loading");
}

void GameGUI::ResetAnimation() {
    StopAnimation();
//    this->gameObject->GetComponent<SaltyEngine::SFML::SpriteRenderer>()->SetSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite(this->spriteInit));
}
