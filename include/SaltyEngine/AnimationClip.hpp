#pragma once
#include <functional>
#include <list>
#include "Object.hpp"
#include "SaltyEngine/SFML/SpriteRenderer.hpp"

class AnimationClip : public SaltyEngine::Object
{
private:
	std::list<std::function<void()>> m_events;
	int m_frameRate = 60;
	std::list<SaltyEngine::SFML::Sprite *> m_sprites;

public:
	AnimationClip(std::string const& name = "Animation");
	virtual ~AnimationClip();

public:
	template<class T>
	void AddEvent(T event)
	{
		m_events.push_back(event);
	}
	void AddSprite(SaltyEngine::SFML::Sprite * sprite);
	int GetFrameRate() const;
	void SetFrameRate(int frameRate);
	const std::list<SaltyEngine::SFML::Sprite*> GetFrames() const;
};