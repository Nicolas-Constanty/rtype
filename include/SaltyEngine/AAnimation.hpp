#pragma once

#include <queue>
#include "SaltyEngine/SFML/AnimationClip.hpp"
#include "SaltyEngine.hpp"
#include "SaltyBehaviour.hpp"
#include "Constants.hpp"
#include "SaltyEngine/ASpriteRenderer.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "SaltyEngine/SaltyEngine.hpp"
#include "Common/Debug.hpp"

namespace SaltyEngine
{
	template <class T>
	class AAnimation : public SaltyBehaviour
	{
	protected:
		bool m_isPlaying = false;
		bool m_playAuto = true;

		AnimationConstants::WrapMode m_wrapMode = AnimationConstants::WrapMode::ONCE;
		std::queue<std::string> m_queuedAnims;

	public:
		AAnimation(GameObject* const obj, bool playAuto = true,
				  AnimationConstants::WrapMode mode = AnimationConstants::WrapMode::ONCE) :
				SaltyBehaviour(obj),
				m_playAuto(playAuto),
				m_wrapMode(mode)
		{
        }

		virtual ~AAnimation()
		{
        }

		/**
		 * @brief Animation functions
		 */
	public:
        bool IsPlaying() const
		{
			return m_isPlaying;
		}

		virtual void Play() = 0;

		virtual void Play(std::string const& name) = 0;

		void PlayQueued(std::string const& animName)
		{
			m_queuedAnims.push(animName);
		}

		virtual void RemoveClip(std::string const& clipName) = 0;

        void Stop()
		{
			m_isPlaying = false;
		}

		virtual void Stop(std::string const& name) = 0;

//		virtual void AddClip(AAnimationClip<T> * const clip, std::string const& name) = 0;

		virtual size_t GetClipCount() const = 0;

        AnimationConstants::WrapMode GetWrapMode() const {
			return m_wrapMode;
		}

		void SetWrapMode(AnimationConstants::WrapMode mode)
		{
			m_wrapMode = mode;
		}

	private:
		virtual void UpdateAnimations() = 0;

		virtual Component *CloneComponent(GameObject* const obj) = 0;
	};
}