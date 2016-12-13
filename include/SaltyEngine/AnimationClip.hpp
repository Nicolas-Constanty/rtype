#pragma once
#include <functional>
#include <list>
#include <SaltyEngine/SFML/AssetManager.hpp>
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
		std::list<Sprite<T> *> m_sprites;

	public:
		AnimationClip(std::string const& name = "Animation", int frameRate = 60) :
				Object(name),
				m_frameRate(frameRate)
		{}

		virtual ~AnimationClip() {}

	public:
		template<class U>
		void AddEvent(U event)
		{
			m_events.push_back(event);
		}

		void AddSprite(Sprite<T> * const sprite)
		{
            if (sprite)
                m_sprites.push_back(sprite);
            else
                Debug::PrintWarning("Cannot add nullptr");
		}

		double GetFrameRate() const
		{
			return m_frameRate;
		}

		void SetFrameRate(int frameRate)
		{
			m_frameRate = frameRate;
		}

		const std::list<Sprite<T> *> &GetFrames() const
		{
			return m_sprites;
		}

		void operator<<(Sprite<T> * const sprite)
		{
			AddSprite(sprite);
		}

	public:
		AnimationClip *CopyClip()
		{
			AnimationClip *animationclip = new AnimationClip("Animation(Clone)", m_frameRate);
			for (std::list<std::function<void()>>::const_iterator j = m_events.begin(); j != m_events.end(); ++j) {
				animationclip->m_events.push_back(*j);
			}
			for (Sprite<T> *sprite : m_sprites) {
                if (sprite)
                    animationclip->AddSprite(SFML::AssetManager::Instance().GetSprite(sprite->GetName()));
			}
			return animationclip;
		}
	};
}