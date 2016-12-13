#pragma once

#include <queue>
#include <SaltyEngine/SFML/AssetManager.hpp>
#include <SaltyEngine/SFML/SpriteRenderer.hpp>
#include "SaltyEngine.hpp"
#include "SaltyBehaviour.hpp"
#include "AnimationClip.hpp"
#include "Constants.hpp"
#include "SaltyEngine/ASpriteRenderer.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "SaltyEngine/SaltyEngine.hpp"
#include "Debug.hpp"

namespace SaltyEngine
{
	template <class T>
	class Animation : public SaltyBehaviour
	{
//		TODO check if gameObject->GetComponent<ASpriteRenderer<T>> is nullptr
    private:

        class AnimData
        {
        public:
            AnimData(size_t frameCount, ASpriteRenderer<T> *sprite, const std::list<Sprite<T> *> &frames, double frameRate) :
                    m_frameCount(frameCount),
                    m_sprite(sprite),
                    m_frames(frames),
                    m_frameRate(frameRate),
                    m_iterator(frames.begin()),
                    m_reviterator(frames.rbegin())
            {}

            bool IsAnimOver() const
            {
                if (!m_playBackwards)
                    return m_iterator == m_frames.end();
                else
                    return m_reviterator == m_frames.rend();
            }

            void Reset()
            {
                m_iterator = m_frames.begin();
                m_reviterator = m_frames.rbegin();
            }

            void ReverseAndReset()
            {
                m_playBackwards = !m_playBackwards;
                Reset();
            }

            void UpdateAnimTimeline(double deltaTime)
            {
                m_elapsed += deltaTime;
                if (m_elapsed >= m_frameRate)
                {
                    m_elapsed = 0;
                    if (!m_playBackwards)
                    {
                        m_sprite->SetSprite(*m_iterator);
                        ++m_iterator;
                    }
                    else
                    {
                        m_sprite->SetSprite(*m_reviterator);
                        ++m_reviterator;
                    }
                }
            }
        private:
            size_t m_frameCount;
            ASpriteRenderer<T> *m_sprite;
            const std::list<Sprite<T> *> &m_frames;
            double m_frameRate;
            typename std::list<Sprite<T> *>::const_iterator m_iterator;
            typename std::list<Sprite<T> *>::const_reverse_iterator m_reviterator;
            double m_elapsed = 0;
            bool m_playBackwards = false;
        };
        AnimData *animData = nullptr;

	private:
		bool m_isPlaying = false;
		bool m_playAuto = true;
		std::map<std::string, AnimationClip<T> *> m_clips;

		AnimationConstants::WrapMode m_wrapMode = AnimationConstants::WrapMode::ONCE;

		std::queue<std::string> m_queuedAnims;

	private:
		void PlayAnim()
		{
			size_t frameCount = clip->GetFrames().size();
			ASpriteRenderer<T> *sprite = gameObject->GetComponent<ASpriteRenderer<T>>();
			const std::list<Sprite<T> *> &frames = clip->GetFrames();
			size_t frameRate = (size_t)(1000 /clip->GetFrameRate());
            std::cout << "Frame count = " << frameCount << std::endl;
			if (frameCount == 0)
			{
				Debug::PrintWarning("Animation: No frames in animation");
				return;
			}
			switch (m_wrapMode)
			{
			case AnimationConstants::ONCE:
				for (typename std::list<Sprite<T> *>::const_iterator it = frames.begin(); it != frames.end(); it++)
				{
					sprite->SetSprite(*it);
					WaitForMillisecond(frameRate);
				}
				break;

			case AnimationConstants::LOOP:
				for (;;)
				{
					for (typename std::list<Sprite<T> *>::const_iterator it = frames.begin(); it != frames.end(); it++)
					{
						std::cout << "toto" << " frame rate " << 1.f / clip->GetFrameRate() << std::endl;
						sprite->SetSprite((*it));
						WaitForMillisecond(frameRate);
					}
				}
				break;

			case AnimationConstants::PING_PONG:
//				for (;;)
//				{
//					for (i = 0; i < frameCount; ++i)
//					{
//						sprite->SetSprite(frames[i]);
//						WaitForMillisecond(frameRate);
//					}
//					for (i = frameCount - 1; i >= 0; --i)
//					{
//						sprite->SetSprite(frames[i]);
//						WaitForMillisecond(frameRate);
//					}
//				}
				break;
			}
		}

	public:
		Animation(GameObject* const obj, bool playAuto = true,
				  AnimationConstants::WrapMode mode = AnimationConstants::WrapMode::ONCE) :
				SaltyBehaviour(obj),
				m_playAuto(playAuto),
				m_wrapMode(mode)
		{
		}
		virtual ~Animation()
		{
            if (animData != nullptr)
                delete animData;
            for (typename std::map<std::string, AnimationClip<T> *>::iterator it = m_clips.begin(); it != m_clips.end(); ++it)
            {
                if (it->second != nullptr)
                {
                    delete it->second;
                    it->second = nullptr;
                }
            }
            m_clips.clear();
        }

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
			//StartCoroutine(&Animation::PlayAnim);
		}

		void Play(std::string const& name)
		{
			if (m_clips.size() == 0 || m_clips.find(name) == m_clips.end())
			{
				return;
			}
			m_isPlaying = true;
			clip = m_clips[name];
			//StartCoroutine(&Animation::PlayAnim);
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
		}

		void Stop(std::string const& name)
		{
			typename std::map<std::string, Animation<T> >::iterator it = m_clips.find(name);
			if (it != m_clips.end() || *it->second != clip)
			{
				return;
			}
            m_isPlaying = false;
		}

		void AddClip(AnimationClip<T> * const clip, std::string const& name)
		{
			m_clips[name] = clip;
		}

		size_t GetClipCount() const
		{
			return m_clips.size();
		}

		AnimationConstants::WrapMode GetWrapMode() const {
			return m_wrapMode;
		}

		void SetWrapMode(AnimationConstants::WrapMode mode)
		{
			m_wrapMode = mode;
		}

	public:
		AnimationClip<T> *clip = nullptr;

	private:
		void UpdateAnimations()
		{
			// If we are playing animations and we have a clip
			if (m_isPlaying && clip != nullptr && clip->GetFrames().size())
			{
				// If we do not have animData yet
				if (animData == nullptr)
				{
					animData = new AnimData(
							clip->GetFrames().size(),
							gameObject->GetComponent<ASpriteRenderer<T>>(),
							clip->GetFrames(),
							(1.0 / clip->GetFrameRate())
					);
				}
				// Update anim
				if (animData != nullptr)
				{
                    animData->UpdateAnimTimeline(SaltyEngine::Instance().GetFixedDeltaTime());
                    if (animData->IsAnimOver()) {
                        switch (m_wrapMode) {
                            case AnimationConstants::ONCE:
                                m_isPlaying = false;
                                break;
                            case AnimationConstants::LOOP:
                                animData->Reset();
                                break;
                            case AnimationConstants::PING_PONG:
                                animData->ReverseAndReset();
                                break;
                        }
                    }
				}
			}
			else
			{
				if (animData != nullptr)
					delete animData;
				animData = nullptr;
			}
		}

		/**
		 * \brief Behaviour functions
		 */
	public:
		void Start()
		{
			if (m_playAuto)
			{
				Play();
			}
		}

        void FixedUpdate()
		{
			UpdateAnimations();
		}
	public:
		virtual Component *CloneComponent(GameObject* const obj) {
			Animation<T> *anim = new Animation<T>(obj, m_playAuto, m_wrapMode);
			for (typename std::map<std::string, AnimationClip<T> *>::const_iterator it = m_clips.begin(); it != m_clips.end(); ++it) {
				anim->AddClip(it->second->CopyClip(), it->first);
			}
            anim->m_queuedAnims = m_queuedAnims;
			return anim;
		}
	};
}