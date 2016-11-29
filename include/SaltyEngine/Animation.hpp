#pragma once

#include <queue>
#include "SaltyBehaviour.hpp"
#include "AnimationClip.hpp"
#include "Constants.hpp"

template <class T>
class Animation : public SaltyEngine::SaltyBehaviour
{
private:
	bool m_isPlaying = false;
	bool m_playAuto = true;
	std::map<std::string, AnimationClip<T> > m_clips;
	//AnimationClip<T> m_currClip;
	SaltyEngine::Animation::WrapMode m_wrapMode;

	std::queue<std::string> m_queuedAnims;

private:
	void PlayAnim();

public:
	Animation(SaltyEngine::GameObject* const obj);
	virtual ~Animation();

public:
	bool IsPlaying() const;
	void Play();
	void Play(std::string const& name);
	void PlayQueued(std::string const& animName) const;
	void RemoveClip(std::string const& clipName);
	void Stop();
	void Stop(std::string const& name);
	void AddClip(AnimationClip<T> const& clip, std::string const& name);
	int GetClipCount() const;

public:
	AnimationClip<T> const clip;
};

