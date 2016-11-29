#include "SaltyEngine\AnimationClip.hpp"



AnimationClip::AnimationClip(std::string const& name) : Object(name)
{
}


AnimationClip::~AnimationClip()
{
}

void AnimationClip::AddSprite(SaltyEngine::SFML::Sprite * sprite)
{
	m_sprites.push_back(sprite);
}

int AnimationClip::GetFrameRate() const
{
	return m_frameRate;
}

void AnimationClip::SetFrameRate(int frameRate)
{
	m_frameRate = frameRate;
}

const std::list<SaltyEngine::SFML::Sprite*> AnimationClip::GetFrames() const
{
	return m_sprites;
}
