#include "SaltyEngine/Animation.hpp"
#include "SaltyEngine/GameObject.hpp"


Animation::Animation(SaltyEngine::GameObject* const obj) : SaltyBehaviour(obj)
{
}


Animation::~Animation()
{
}

void Animation::PlayAnim()
{
	int frameCount;
	switch (m_wrapMode)
	{
	case SaltyEngine::Animation::ONCE:
		frameCount = m_clips.at(0).GetFrames().size();
		for (int i = 0; i < frameCount; ++i)
		{
			WaitForSecond(1.0 / m_clips.at(0).GetFrameRate());
		}
		break;

	case SaltyEngine::Animation::LOOP:
		for (;;)
		{
			WaitForSecond(1.0 / m_clips.at(0).GetFrameRate());
		}
		break;

	case SaltyEngine::Animation::PING_PONG:
		frameCount = m_clips.at(0).GetFrames().size();
		for (int i = 0; i < frameCount; ++i)
		{
			WaitForSecond(1.0 / m_clips.at(0).GetFrameRate());
		}
		for (int i = frameCount - 1; i >= 0; --i)
		{
			WaitForSecond(1.0 / m_clips.at(0).GetFrameRate());
		}
		break;
	}
}

void Animation::PlayAnim(std::string const& name)
{
}

bool Animation::IsPlaying() const
{
	return m_isPlaying;
}

void Animation::Play()
{
	if (m_clips.size() == 0)
	{
		return;
	}
	m_isPlaying = true;
	//StartCoroutine(&Animation::PlayAnim);
}

void Animation::Play(std::string const& name)
{
	if (m_clips.size() == 0 || m_clips.find(name) == m_clips.end())
	{
		return;
	}
	m_isPlaying = true;
	//m_coroutines.push_back(std::bind(&Animation::PlayAnim, this, name));
}

int Animation::GetClipCount() const
{
	return m_clips.size();
}
