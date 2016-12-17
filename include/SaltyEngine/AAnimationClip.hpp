#pragma once
#include <functional>
#include <list>
#include "Object.hpp"
#include "SaltyEngine/Sprite.hpp"

namespace SaltyEngine
{
	template <class T>
	class AAnimationClip : public Object
	{
	protected:
		std::list<std::function<void()>> m_events;
        std::function<void()> m_event_end = nullptr;
		int m_frameRate = 60;
        AnimationConstants::WrapMode m_wrapMode = AnimationConstants::WrapMode::ONCE;

	public:
		AAnimationClip(std::string const& name = "Animation", int frameRate = 60, AnimationConstants::WrapMode mode = AnimationConstants::WrapMode::ONCE) :
				Object(name),
				m_frameRate(frameRate),
                m_wrapMode(mode)
		{}

		virtual ~AAnimationClip() {}

	public:
		AnimationConstants::WrapMode GetWrapMode() const {
			return (m_wrapMode);
		}

		void	SetWrapMode(AnimationConstants::WrapMode wrapMode) {
			m_wrapMode = wrapMode;
		}

	public:
		template<class U>
		void AddEvent(U event)
		{
			m_events.push_back(event);
		}

		double GetFrameRate() const
		{
			return m_frameRate;
		}

		void SetFrameRate(int frameRate)
		{
			m_frameRate = frameRate;
		}

        void OnAnimEnd()
        {
            if (m_event_end != nullptr)
                m_event_end();
        }
	};
}