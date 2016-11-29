#pragma once

#include <queue>
#include "SaltyBehaviour.hpp"
#include "AnimationClip.hpp"
#include "Constants.hpp"
#include "SaltyEngine/ASpriteRenderer.hpp"

namespace SaltyEngine
{
	template <class T>
	class Animation : public SaltyBehaviour
	{
	private:
		bool m_isPlaying = false;
		bool m_playAuto = true;
		std::map<std::string, AnimationClip<T> *> m_clips;
		//AnimationClip<T> m_currClip;
		AnimationConstants::WrapMode m_wrapMode;

		std::queue<std::string> m_queuedAnims;

	private:
		void PlayAnim()
		{
			int i;
			int frameCount = clip.GetFrames().size();
			ASpriteRenderer<T> *sprite = gameObject->GetComponent<ASpriteRenderer<T> *>();

			switch (m_wrapMode)
			{
			case AnimationConstants::ONCE:
				for (i = 0; i < frameCount; ++i)
				{
					sprite->SetSprite(clip.GetFrames()[i]);
					WaitForSecond(1.0 / clip.GetFrameRate());
				}
				break;

			case AnimationConstants::LOOP:
				i = 0;
				for (;;)
				{
					sprite->SetSprite(clip.GetFrames()[i++]);
					WaitForSecond(1.0 / clip.GetFrameRate());
					i %= frameCount;
				}
				break;

			case AnimationConstants::PING_PONG:
				for (;;)
				{
					for (i = 0; i < frameCount; ++i)
					{
						sprite->SetSprite(clip.GetFrames()[i]);
						WaitForSecond(1.0 / clip.GetFrameRate());
					}
					for (i = frameCount - 1; i >= 0; --i)
					{
						sprite->SetSprite(clip.GetFrames()[i]);
						WaitForSecond(1.0 / clip.GetFrameRate());
					}
				}
				break;
			}
		}

	public:
		Animation(GameObject* const obj) : SaltyBehaviour(obj)
		{}
		virtual ~Animation()
		{}

		/**
		 * \brief Animation functions
		 */
	public:
		bool IsPlaying() const
		{
			return m_isPlaying;
		}

		void Play()
		{
			if (m_clips.size() == 0)
			{
				return;
			}
			m_isPlaying = true;
			clip = m_clips.at(0);
			StartCoroutine(&SaltyEngine::Animation::PlayAnim);
		}

		void Play(std::string const& name)
		{
			if (m_clips.size() == 0)
			{
				return;
			}
			m_isPlaying = true;
			clip = m_clips.at(0);
			StartCoroutine(&Animation::PlayAnim);
		}

		void PlayQueued(std::string const& animName) const
		{
			m_queuedAnims.push(animName);
		}

		void RemoveClip(std::string const& clipName)
		{
			if (m_clips.find(clipName) == m_clips.end())
			{
				return;
			}
			m_clips.erase(clipName);
		}

		void Stop()
		{
			m_isPlaying = false;
			// TODO : StopCoroutine();
		}

		void Stop(std::string const& name)
		{
			std::map<std::string, Animation<T> >::iterator it = m_clips.find(name);
			if (it != m_clips.end() || *it->second != clip)
			{
				return;
			}
			// TODO : StopCoroutine();
		}

		void AddClip(AnimationClip<T> * const clip, std::string const& name)
		{
			m_clips[name] = clip;
		}

		int GetClipCount() const
		{
			return m_clips.size();
		}

	public:
		AnimationClip<T> const clip;

		/**
		 * \brief Behaviour functions
		 */
	public:
		void Start()
		{
			std::cout << "STARTING" << std::endl;
			if (m_playAuto)
			{
				StartCoroutine(&Animation::PlayAnim);
			}
		}
	};
}