#pragma once

#include <queue>
#include "SaltyBehaviour.hpp"
#include "AnimationClip.hpp"
#include "Constants.hpp"
#include "SaltyEngine/ASpriteRenderer.hpp"
#include "Debug.hpp"

namespace SaltyEngine
{
	template <class T>
	class Animation : public SaltyBehaviour
	{
	private:
		bool m_isPlaying = false;
		bool m_playAuto = true;
		std::map<std::string, AnimationClip<T> *> m_clips;

		AnimationConstants::WrapMode m_wrapMode = AnimationConstants::WrapMode::LOOP;

		std::queue<std::string> m_queuedAnims;

	private:
		void PlayAnim()
		{
			size_t i;
			size_t frameCount = clip->GetFrames().size();
			ASpriteRenderer<T> *sprite = gameObject->GetComponent<ASpriteRenderer<T>>();
			const std::list<Sprite<T> *> &frames = clip->GetFrames();
			size_t frameRate = (size_t)(1000 /clip->GetFrameRate());

			if (frameCount == 0)
			{
				Debug::PrintWarning("Animation: No frames in animation");
				return;
			}
			switch (m_wrapMode)
			{
			case AnimationConstants::ONCE:
				for (std::list<Sprite<T> *>::const_iterator it = frames.begin(); it != frames.end(); it++)
				{
					sprite->SetSprite(*it);
					WaitForMillisecond(frameRate);
				}
				break;

			case AnimationConstants::LOOP:
				i = 0;
				for (;;)
				{
					for (std::list<Sprite<T> *>::const_iterator it = frames.begin(); it != frames.end(); it++)
					{
						std::cout << "toto" << i << " frame rate " << 1.f / clip->GetFrameRate() << std::endl;
						sprite->SetSprite((*it));
						WaitForMillisecond(frameRate);
						i %= frameCount;
					}
				}
				break;

			case AnimationConstants::PING_PONG:
				/*for (;;)
				{
					for (i = 0; i < frameCount; ++i)
					{
						sprite->SetSprite(frames[i]);
						WaitForMillisecond(frameRate);
					}
					for (i = frameCount - 1; i >= 0; --i)
					{
						sprite->SetSprite(frames[i]);
						WaitForMillisecond(frameRate);
					}
				}*/
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
			clip = m_clips.begin()->second;
			StartCoroutine(&Animation::PlayAnim);
		}

		void Play(std::string const& name)
		{
			if (m_clips.size() == 0 || m_clips.find(name) == m_clips.end())
			{
				return;
			}
			m_isPlaying = true;
			clip = m_clips[name];
			StartCoroutine(&Animation::PlayAnim);
		}

		void PlayQueued(std::string const& animName)
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
			typename std::map<std::string, Animation<T> >::iterator it = m_clips.find(name);
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

		size_t GetClipCount() const
		{
			return m_clips.size();
		}

	public:
		AnimationClip<T> *clip = nullptr;

		/**
		 * \brief Behaviour functions
		 */
	public:
		void Start()
		{
			std::cout << "STARTING" << std::endl;
			if (m_playAuto)
			{
				Play();
			}
		}
	};
}