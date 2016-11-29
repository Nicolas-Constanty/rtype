#include "SaltyEngine\AnimationClip.hpp"

template <class T>
int SaltyEngine::AnimationClip<T>::GetFrameRate() const
{
	return m_frameRate;
}

template <class T>
void SaltyEngine::AnimationClip<T>::SetFrameRate(int frameRate)
{
	m_frameRate = frameRate;
}

template <class T>
const std::vector<SaltyEngine::Sprite<T> *> SaltyEngine::AnimationClip<T>::GetFrames() const
{
	return m_sprites;
}