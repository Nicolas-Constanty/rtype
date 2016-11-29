#pragma once

#include "SaltyBehaviour.hpp"
#include "AnimationClip.hpp"
#include "Constants.hpp"

class Animation : public SaltyEngine::SaltyBehaviour
{
private:
	bool m_isPlaying = false;
	bool m_playAuto = true;
	std::map<std::string, AnimationClip> m_clips;
	SaltyEngine::Animation::WrapMode m_wrapMode;

private:
	void PlayAnim();
	void PlayAnim(std::string const& name);

public:
	Animation(SaltyEngine::GameObject* const obj);
	virtual ~Animation();

public:
	bool IsPlaying() const;
	void Play();
	void Play(std::string const& name);
	void PlayQueued(std::string const& animName) const;
	void RemoveClip(std::string const& clipName);
	void Stop() const;
	void Stop(std::string const& name) const;
	void AddClip(AnimationClip const& clip, std::string const& name);
	int GetClipCount() const;

public:
	AnimationClip const clip;
};

