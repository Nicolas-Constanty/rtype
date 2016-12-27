#pragma once
#include <functional>
#include <list>
#include "Object.hpp"
#include "SaltyEngine/Sprite.hpp"

namespace SaltyEngine
{
//	template <class T>
	class LIB_EXPORT AAnimationClip : public Object
	{
	protected:
//		std::list<std::function<void()>> m_events;
		std::map<size_t, std::function<void()>> m_events;
        std::function<void()> m_event_end = nullptr;
		int m_frameRate = 60;
        AnimationConstants::WrapMode m_wrapMode = AnimationConstants::WrapMode::ONCE;

	public:
		AAnimationClip(std::string const& name = "Animation", int frameRate = 60, AnimationConstants::WrapMode mode = AnimationConstants::WrapMode::ONCE);

		virtual ~AAnimationClip() {}

	public:
		AnimationConstants::WrapMode GetWrapMode() const;

		void	SetWrapMode(AnimationConstants::WrapMode wrapMode);

	public:
		template<class U>
		void AddEvent(U event, int frame = -1)
		{
            if (frame == -1)
                m_event_end = event;
            else
//    			m_events.push_back(event);
    			m_events[frame] = event;
		}

        virtual std::function<void()> const operator[](size_t idx) const
        {
            return (m_events.find(idx) != m_events.end()) ? m_events.at(idx) : [](){};
        }

		double GetFrameRate() const;

		void SetFrameRate(int frameRate);

        void OnAnimEnd();
	};
}