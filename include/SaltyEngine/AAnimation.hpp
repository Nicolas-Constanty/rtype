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
	class AAnimation : public SaltyBehaviour
	{
	protected:
		bool m_isPlaying = false;
		bool m_playAuto = true;

		AnimationConstants::WrapMode m_wrapMode = AnimationConstants::WrapMode::ONCE;
		std::queue<std::string> m_queuedAnims;

	public:
		AAnimation(GameObject* const obj, bool playAuto = true,
				  AnimationConstants::WrapMode mode = AnimationConstants::WrapMode::ONCE);

		virtual ~AAnimation() {}

		/**
		 * @brief Animation functions
		 */
	public:
        bool IsPlaying() const;

		virtual void Play() = 0;

		virtual void Play(std::string const& name) = 0;

		void PlayQueued(std::string const& animName);

		virtual void RemoveClip(std::string const& clipName) = 0;

        void Stop();

		virtual void Stop(std::string const& name) = 0;

		virtual size_t GetClipCount() const = 0;

        AnimationConstants::WrapMode GetWrapMode() const;

		void SetWrapMode(AnimationConstants::WrapMode mode);

	private:
		virtual void UpdateAnimations() = 0;

		virtual Component *CloneComponent(GameObject* const obj) = 0;
	};
}