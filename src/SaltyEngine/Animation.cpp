#include "SaltyEngine/Animation.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "SaltyEngine/ASpriteRenderer.hpp"

template <class T>
void SaltyEngine::Animation<T>::PlayAnim()
{
	int frameCount = clip.GetFrames().size();
	ASpriteRenderer<T> sprite = gameObject->GetComponent<ASpriteRenderer<T> >();

	switch (m_wrapMode)
	{
	case AnimationConstants::ONCE:
		for (int i = 0; i < frameCount; ++i)
		{
			sprite.SetSprite(clip.GetFrames()[i]);
			WaitForSecond(1.0 / clip.GetFrameRate());
		}
		break;

	case AnimationConstants::LOOP:
		int i = 0;
		for (;;)
		{
			sprite.SetSprite(clip.GetFrames()[i++]);
			WaitForSecond(1.0 / clip.GetFrameRate());
			i %= frameCount;
		}
		break;

	case AnimationConstants::PING_PONG:
		for (;;)
		{
			for (int i = 0; i < frameCount; ++i)
			{
				sprite.SetSprite(clip.GetFrames()[i]);
				WaitForSecond(1.0 / clip.GetFrameRate());
			}
			for (int i = frameCount - 1; i >= 0; --i)
			{
				sprite.SetSprite(clip.GetFrames()[i]);
				WaitForSecond(1.0 / clip.GetFrameRate());
			}
		}
		break;
	}
}

template <class T>
bool SaltyEngine::Animation<T>::IsPlaying() const
{
	return m_isPlaying;
}

template <class T>
void SaltyEngine::Animation<T>::Play()
{
	if (m_clips.size() == 0)
	{
		return;
	}
	m_isPlaying = true;
	clip = m_clips.at(0);
	StartCoroutine(&SaltyEngine::Animation::PlayAnim);
}

template <class T>
void SaltyEngine::Animation<T>::Play(std::string const& name)
{
	if (m_clips.size() == 0 || m_clips.find(name) == m_clips.end())
	{
		return;
	}
	m_isPlaying = true;
	clip = m_clips[name];
	StartCoroutine(&SaltyEngine::Animation::PlayAnim);
}

template <class T>
void SaltyEngine::Animation<T>::PlayQueued(std::string const& animName) const
{
	m_queuedAnims.push(animName);
}

template <class T>
void SaltyEngine::Animation<T>::RemoveClip(std::string const& clipName)
{
	if (m_clips.find(clipName) == m_clips.end())
	{
		return;
	}
	m_clips.erase(clipName);
}

template <class T>
void SaltyEngine::Animation<T>::Stop()
{
	m_isPlaying = false;
	// TODO : StopCoroutine();
}

template <class T>
void SaltyEngine::Animation<T>::Stop(std::string const& name)
{
	std::map<std::string, Animation<T> >::iterator it = m_clips.find(name);
	if (it != m_clips.end() || *it->second != clip)
	{
		return;
	}
	// TODO : StopCoroutine();
}

template <class T>
int SaltyEngine::Animation<T>::GetClipCount() const
{
	return m_clips.size();
}
