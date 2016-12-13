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
        virtual std::unique_ptr<Object> CloneMemberwise()
        {
            AnimationClip *animationClip = new AnimationClip("Animation(Clone)", m_frameRate);

            for (std::list<std::function<void()>>::iterator it = m_events.begin(); it != m_events.end(); ++it)
            {
                animationClip->m_events.push_back(*it);
            }
            for (Sprite<T> *sprite : m_sprites)
            {
                animationClip->m_sprites.push_back(SFML::AssetManager::Instance().GetSprite(sprite->GetName()));
            }
            return std::unique_ptr<Object>(animationClip);
        }

        AnimationClip *CopyClip()
        {
            AnimationClip *animationClip = new AnimationClip("Animation(Clone)", m_frameRate);

            for (std::list<std::function<void()>>::iterator it = m_events.begin(); it != m_events.end(); ++it)
            {
                animationClip->m_events.push_back(*it);
            }
            for (Sprite<T> *sprite : m_sprites)
            {
                std::cout << sprite << std::endl;
//                animationClip->m_sprites.push_back(SFML::AssetManager::Instance().GetSprite(sprite->GetName()));
//                animationClip->AddSprite(SFML::AssetManager::Instance().GetSprite(sprite->GetName()));
            }
            return animationClip;
        }
	};
}