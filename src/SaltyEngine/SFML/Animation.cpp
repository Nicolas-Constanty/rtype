//
// Created by veyrie_f on 17/12/16.
//

#include "SaltyEngine/SFML/Animation.hpp"

SaltyEngine::SFML::Animation::Animation(SaltyEngine::GameObject *const obj, bool playAuto,
                                        SaltyEngine::AnimationConstants::WrapMode mode) :
        AAnimation(obj, playAuto, mode)
{
}

SaltyEngine::SFML::Animation::~Animation() {
    if (animData != nullptr)
        delete animData;
    for (typename std::map<std::string, SFML::AnimationClip *>::iterator it = m_clips.begin();
         it != m_clips.end(); ++it) {
        if (it->second != nullptr) {
            delete it->second;
            it->second = nullptr;
        }
    }
    m_clips.clear();
}

void SaltyEngine::SFML::Animation::Play() {
    if (m_clips.size() == 0) {
        return;
    }
    ClearAnimData();
    m_isPlaying = true;
    clip = m_clips.begin()->second;
}

void SaltyEngine::SFML::Animation::Play(std::string const &name) {
    if (m_clips.size() == 0 || m_clips.find(name) == m_clips.end()) {
        Debug::PrintWarning("Cannot Play clip " + name);
        return;
    }
    ClearAnimData();
    m_isPlaying = true;
    clip = m_clips[name];
}

void SaltyEngine::SFML::Animation::RemoveClip(std::string const &clipName) {
    if (m_clips.find(clipName) == m_clips.end()) {
        return;
    }
    m_clips.erase(clipName);
}

void SaltyEngine::SFML::Animation::Stop(std::string const &name) {
    typename std::map<std::string, AnimationClip *>::iterator it = m_clips.find(name);
    if (it != m_clips.end() || it->second != clip) {
        return;
    }
    m_isPlaying = false;
}

void SaltyEngine::SFML::Animation::AddClip(SaltyEngine::SFML::AnimationClip *const clip, std::string const &name) {
    if (clip == nullptr) {
        Debug::PrintError("AnimationClip " + name + " was null");
        return;
    }
    m_clips[name] = clip;
}

size_t SaltyEngine::SFML::Animation::GetClipCount() const {
    return m_clips.size();
}

void SaltyEngine::SFML::Animation::UpdateAnimations() {
    // If we are playing animations and we have a clip
    if (m_isPlaying && clip != nullptr && clip->GetFrames().size()) {
        // If we do not have animData yet
        if (animData == nullptr) {
            animData = new AnimData(
                    clip->GetFrames().size(),
                    gameObject->GetComponent<SpriteRenderer>(),
                    clip->GetFrames(),
                    (1.0 / clip->GetFrameRate())
            );
        }
        // Update anim
        if (animData != nullptr) {
            animData->UpdateAnimTimeline(Engine::Instance().GetFixedDeltaTime());
            if (animData->IsAnimOver()) {
                // If we have some anims queued, play them
                if (m_queuedAnims.size() > 0) {

                    std::cout << "On Anim end being called" << std::endl;
                    clip->OnAnimEnd();

                    Play(m_queuedAnims.back());
                    m_queuedAnims.pop();
                } else {
                    switch (clip->GetWrapMode()) {
                        case AnimationConstants::ONCE:
                            m_isPlaying = false;
                            break;
                        case AnimationConstants::LOOP:
                            animData->Reset();
                            break;
                        case AnimationConstants::PING_PONG:
                            animData->ReverseAndReset();
                            break;
                    }
                }
            }
        }
    } else {
        ClearAnimData();
    }
}

void SaltyEngine::SFML::Animation::Start() {
    if (m_playAuto) {
        Play();
    }
}

void SaltyEngine::SFML::Animation::FixedUpdate() {
    UpdateAnimations();
}

SaltyEngine::Component *SaltyEngine::SFML::Animation::CloneComponent(SaltyEngine::GameObject *const obj) {
    Animation *anim = new Animation(obj, m_playAuto, m_wrapMode);
    for (typename std::map<std::string, AnimationClip *>::const_iterator it = m_clips.begin(); it != m_clips.end(); ++it) {
        anim->AddClip(AssetManager::Instance().GetAnimation(it->second->GetName()), it->first);
    }
    anim->m_queuedAnims = m_queuedAnims;
    anim->m_isPlaying = m_isPlaying;
    return anim;
}

void SaltyEngine::SFML::Animation::ClearAnimData(void) {
    if (animData != nullptr)
        delete animData;
    animData = nullptr;
}

SaltyEngine::SFML::AnimationClip *SaltyEngine::SFML::Animation::GetClip(std::string const &name) const {
    return m_clips[name];
}

SaltyEngine::SFML::AnimationClip *SaltyEngine::SFML::Animation::GetClip(int id) const
{
    if (m_clips.size() <= 0)
        return nullptr;

    return std::next(m_clips.begin(), id)->second;
}
