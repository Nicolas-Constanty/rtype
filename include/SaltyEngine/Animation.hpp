#pragma once

#include <queue>
#include "SaltyBehaviour.hpp"
#include "AnimationClip.hpp"
#include "Constants.hpp"

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
		void PlayAnim();

	public:
		Animation(GameObject* const obj) : SaltyBehaviour(obj)
		{}
		virtual ~Animation()
		{}

	public:
		bool IsPlaying() const;
		void Play();
		void Play(std::string const& name);
		void PlayQueued(std::string const& animName) const;
		void RemoveClip(std::string const& clipName);
		void Stop();
		void Stop(std::string const& name);

		void AddClip(AnimationClip<T> * const clip, std::string const& name)
		{
			m_clips[name] = clip;
		}

		int GetClipCount() const;

	public:
		AnimationClip<T> const clip;
	};
}