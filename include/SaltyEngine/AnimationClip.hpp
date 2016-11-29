#pragma once
#include <functional>
#include <list>
#include <vector>
#include "Object.hpp"
#include "SaltyEngine/Sprite.hpp"

template <class T>
class AnimationClip : public SaltyEngine::Object
{
private:
	std::list<std::function<void()>> m_events;
	int m_frameRate = 60;
	std::vector<SaltyEngine::Sprite<T>> m_sprites;

public:
	AnimationClip(std::string const& name = "Animation");
	virtual ~AnimationClip();

public:
	template<class U>
	void AddEvent(U event)
	{
		m_events.push_back(event);
	}
	void AddSprite(SaltyEngine::Sprite<T> sprite);
	int GetFrameRate() const;
	void SetFrameRate(int frameRate);
	const std::vector<SaltyEngine::Sprite<T>> GetFrames() const;
};
