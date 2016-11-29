#include "SaltyEngine\AnimationClip.hpp"

template <class T>
AnimationClip<T>::AnimationClip(std::string const& name) : Object(name)
{
}

template <class T>
AnimationClip<T>::~AnimationClip()
{
}

template <class T>
void AnimationClip<T>::AddSprite(SaltyEngine::Sprite<T> sprite)
{
	m_sprites.push_back(sprite);
}

template <class T>
int AnimationClip<T>::GetFrameRate() const
{
	return m_frameRate;
}

template <class T>
void AnimationClip<T>::SetFrameRate(int frameRate)
{
	m_frameRate = frameRate;
}

template <class T>
const std::vector<SaltyEngine::Sprite<T>> AnimationClip<T>::GetFrames() const
{
	return m_sprites;
}
