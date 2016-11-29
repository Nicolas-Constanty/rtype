#pragma once
#include <functional>
#include <list>
#include <vector>
#include "Object.hpp"
#include "SaltyEngine/Sprite.hpp"

namespace SaltyEngine
{
	template <class T>
	class AnimationClip : public Object
	{
	private:
		std::list<std::function<void()>> m_events;
		int m_frameRate = 60;
		std::vector<T*> m_sprites;

	public:
		AnimationClip(std::string const& name = "Animation") : Object(name)
		{}

		virtual ~AnimationClip() {}

	public:
		template<class U>
		void AddEvent(U event)
		{
			m_events.push_back(event);
		}

		void AddSprite(T* const sprite)
		{
			m_sprites.push_back(sprite);
		}

		int GetFrameRate() const;
		void SetFrameRate(int frameRate);
		const std::vector<Sprite<T> *> GetFrames() const;

		void operator<<(T * const sprite)
		{
			AddSprite(sprite);
		}
	};
}