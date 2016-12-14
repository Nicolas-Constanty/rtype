#pragma once
#include <functional>
#include <list>
#include "SaltyEngine/SFML/AssetManager.hpp"
#include "Object.hpp"
#include "SaltyEngine/Sprite.hpp"

namespace SaltyEngine
{
	template <class T>
	class AAnimationClip : public Object
	{
	protected:
		std::list<std::function<void()>> m_events;
		int m_frameRate = 60;

	public:
		AAnimationClip(std::string const& name = "Animation", int frameRate = 60) :
				Object(name),
				m_frameRate(frameRate)
		{}

		virtual ~AAnimationClip() {}

	public:
		template<class U>
		void AddEvent(U event)
		{
			m_events.push_back(event);
		}

//		virtual void AddSprite(Sprite<T> * const sprite) = 0;

		double GetFrameRate() const
		{
			return m_frameRate;
		}

		void SetFrameRate(int frameRate)
		{
			m_frameRate = frameRate;
		}

//		virtual const std::list<Sprite<T> *> &GetFrames() const = 0;

//		virtual void operator<<(Sprite<T> * const sprite) = 0;

//	public:
//		AnimationClip *CopyClip()
//		{
//			AnimationClip *animationclip = new AnimationClip("Animation(Clone)", m_frameRate);
//			for (std::list<std::function<void()>>::const_iterator j = m_events.begin(); j != m_events.end(); ++j) {
//				animationclip->m_events.push_back(*j);
//			}
//			for (Sprite<T> *sprite : m_sprites) {
//                if (sprite)
//                    animationclip->AddSprite(SFML::AssetManager::Instance().GetSprite(sprite->GetName()));
//			}
//			return animationclip;
//		}
	};
}