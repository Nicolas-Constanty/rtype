//
// Created by veyrie_f on 17/12/16.
//

#include "SaltyEngine/SFML/AnimationClip.hpp"

void SaltyEngine::SFML::AnimationClip::AddSprite(::SaltyEngine::SFML::Sprite *const sprite) {
    if (sprite)
        m_sprites.push_back(sprite);
    else
        Debug::PrintWarning("Cannot add nullptr");
}

SaltyEngine::SFML::AnimationClip::~AnimationClip() {

}

SaltyEngine::SFML::AnimationClip::AnimationClip(const string &name, int frameRate, SaltyEngine::AnimationConstants::WrapMode mode) :
        AAnimationClip(name, frameRate, mode) {
}

const std::list<SaltyEngine::SFML::Sprite *> &SaltyEngine::SFML::AnimationClip::GetFrames() const {
    return m_sprites;
}

void SaltyEngine::SFML::AnimationClip::operator<<(SaltyEngine::SFML::Sprite *const sprite) {
    AddSprite(sprite);
}
