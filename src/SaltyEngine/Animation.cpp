#include "SaltyEngine/Animation.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "SaltyEngine/ASpriteRenderer.hpp"

template <class T>
Animation<T>::Animation(SaltyEngine::GameObject* const obj) : SaltyBehaviour(obj)
{
}


template <class T>
Animation<T>::~Animation()
{
}

template <class T>
void Animation<T>::PlayAnim()
{
	int frameCount = clip.GetFrames().size();
	SaltyEngine::ASpriteRenderer<T> sprite = gameObject->GetComponent<SaltyEngine::ASpriteRenderer<T> >();

	switch (m_wrapMode)
	{
	case SaltyEngine::Animation::ONCE:
		for (int i = 0; i < frameCount; ++i)
		{
			sprite.SetSprite(clip.GetFrames()[i]);
			WaitForSecond(1.0 / clip.GetFrameRate());
		}
		break;

	case SaltyEngine::Animation::LOOP:
		int i = 0;
		for (;;)
		{
			sprite.SetSprite(clip.GetFrames()[i++]);
			WaitForSecond(1.0 / clip.GetFrameRate());
			i %= frameCount;
		}
		break;

	case SaltyEngine::Animation::PING_PONG:
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
bool Animation<T>::IsPlaying() const
{
	return m_isPlaying;
}

template <class T>
void Animation<T>::Play()
{
	if (m_clips.size() == 0)
	{
		return;
	}
	m_isPlaying = true;
	clip = m_clips.at(0);
	StartCoroutine(&Animation::PlayAnim);
}

template <class T>
void Animation<T>::Play(std::string const& name)
{
	if (m_clips.size() == 0 || m_clips.find(name) == m_clips.end())
	{
		return;
	}
	m_isPlaying = true;
	clip = m_clips[name];
	StartCoroutine(&Animation::PlayAnim);
}

template <class T>
void Animation<T>::PlayQueued(std::string const& animName) const
{
	m_queuedAnims.push(animName);
}

template <class T>
void Animation<T>::RemoveClip(std::string const& clipName)
{
	if (m_clips.find(clipName) == m_clips.end())
	{
		return;
	}
	m_clips.erase(clipName);
}

template <class T>
void Animation<T>::Stop()
{
	m_isPlaying = false;
	// TODO : StopCoroutine();
}

template <class T>
void Animation<T>::Stop(std::string const& name)
{
	std::map<std::string, Animation<T> >::iterator it = m_clips.find(name);
	if (it != m_clips.end() || *it->second != clip)
	{
		return;
	}
	// TODO : StopCoroutine();
}

template <class T>
void Animation<T>::AddClip(AnimationClip<T> const& clip, std::string const& name)
{
	m_clips[name] = clip;
}

template <class T>
int Animation<T>::GetClipCount() const
{
	return m_clips.size();
}
