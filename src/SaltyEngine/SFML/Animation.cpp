//
// Created by veyrie_f on 17/12/16.
//

#include "SaltyEngine/SFML/Animation.hpp"

namespace SaltyEngine
{
    namespace SFML
    {
        Animation::Animation(SaltyEngine::GameObject *const obj, bool playAuto,
                                                SaltyEngine::AnimationConstants::WrapMode mode) :
                AAnimation(obj, playAuto, mode)
        {
        }

        Animation::~Animation() {
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

        void Animation::Play() {
            if (m_clips.size() == 0) {
                return;
            }
            ClearAnimData();
            m_isPlaying = true;
            clip = m_clips.begin()->second;
        }

        void Animation::Play(std::string const &name) {
            if (m_clips.size() == 0 || m_clips.find(name) == m_clips.end()) {
                Debug::PrintWarning("Cannot Play clip " + name);
                return;
            }
            ClearAnimData();
            m_isPlaying = true;
            clip = m_clips[name];
        }

        void Animation::RemoveClip(std::string const &clipName) {
            if (m_clips.find(clipName) == m_clips.end()) {
                return;
            }
            m_clips.erase(clipName);
        }

        void Animation::Stop(std::string const &name) {
            typename std::map<std::string, AnimationClip *>::iterator it = m_clips.find(name);
            if (it == m_clips.end() || it->second != clip) {
                return;
            }
            m_isPlaying = false;
        }

        void Animation::Stop()
        {
            AAnimation::Stop();
        }

        void Animation::AddClip(SaltyEngine::SFML::AnimationClip *const clip, std::string const &name) {
            if (clip == nullptr) {
                Debug::PrintError("AnimationClip " + name + " was null");
                return;
            }
            if (gameObject->GetComponent<SpriteRenderer>() == nullptr)
            {
                gameObject->AddComponent<SpriteRenderer>(AssetManager::Instance().GetSprite((*clip->GetFrames().begin())->GetName()), Layout::normal);
            }
            m_clips[name] = clip;
        }

        size_t Animation::GetClipCount() const {
            return m_clips.size();
        }

        void Animation::UpdateAnimations() {
            // If we are playing animations and we have a clip
            if (m_isPlaying && clip != nullptr && clip->GetFrames().size()) {
                // If we do not have animData yet
                if (animData == nullptr) {
                    animData = new AnimData(clip, gameObject->GetComponent<SpriteRenderer>());
                }
                // Update anim
                if (animData != nullptr) {
                    animData->UpdateAnimTimeline(Engine::Instance().GetFixedDeltaTime());
                    if (animData->IsAnimOver()) {

                        // If we have some anims queued, play them
                        if (m_queuedAnims.size() > 0) {

                            Play(m_queuedAnims.back());
                            m_queuedAnims.pop();
                        }
                        else
                        {
                            switch (clip->GetWrapMode())
                            {
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
            }
            else
            {
                ClearAnimData();
            }
        }

        void Animation::Start() {
            if (m_playAuto) {
                Play();
            }
        }

        void Animation::FixedUpdate() {
            UpdateAnimations();
        }

        Component *Animation::CloneComponent(SaltyEngine::GameObject *const obj) {
            Animation *anim = new Animation(obj, m_playAuto, m_wrapMode);
            for (typename std::map<std::string, AnimationClip *>::const_iterator it = m_clips.begin(); it != m_clips.end(); ++it) {
                anim->AddClip(AssetManager::Instance().GetAnimation(it->second->GetName()), it->first);
            }
            anim->m_queuedAnims = m_queuedAnims;
            anim->m_isPlaying = m_isPlaying;
            return anim;
        }

        void Animation::ClearAnimData(void) {
            if (animData != nullptr)
                delete animData;
            animData = nullptr;
        }

        AnimationClip *Animation::GetClip(std::string const &name) const {
            return m_clips[name];
        }

        AnimationClip *Animation::GetClip(int id) const
        {
            if (m_clips.size() <= 0)
                return nullptr;

            return std::next(m_clips.begin(), id)->second;
        }

        bool Animation::IsPlaying(std::string const &name) const {
            return m_isPlaying && clip != nullptr && clip->GetName() == name;
        }

        Animation::AnimData::AnimData(AnimationClip *clip, SFML::SpriteRenderer *sprite) :
                m_clip(clip),
                m_frameCount(clip->GetFrames().size()),
                m_spriteRenderer(sprite),
                m_frames(clip->GetFrames()),
                m_frameRate(1.0 / clip->GetFrameRate()),
                m_iterator(m_frames.begin()),
                m_reviterator(m_frames.rbegin())
        {
            m_spriteRenderer->SetSprite(*m_frames.begin());
        }

        bool Animation::AnimData::IsAnimOver() const {
            if (!m_playBackwards)
                return m_iterator == m_frames.end();
            else
                return m_reviterator == m_frames.rend();
        }

        void Animation::AnimData::Reset() {
            m_iterator = m_frames.begin();
            m_reviterator = m_frames.rbegin();
            m_currentFrame = 0;
        }

        void Animation::AnimData::ReverseAndReset() {
            m_playBackwards = !m_playBackwards;
            Reset();
            m_currentFrame = m_frameCount - 1;
        }

        void Animation::AnimData::UpdateAnimTimeline(double deltaTime) {
            m_elapsed += deltaTime;
            if (m_elapsed >= m_frameRate) {
                m_elapsed = 0;
                m_clip->operator[](m_currentFrame)();
                if (!m_playBackwards) {
                    m_spriteRenderer->SetSprite(*m_iterator);
                    ++m_iterator;
                    ++m_currentFrame;
                } else {
                    m_spriteRenderer->SetSprite(*m_reviterator);
                    ++m_reviterator;
                    --m_currentFrame;
                }
            }
            if (IsAnimOver())
            {
                m_clip->OnAnimEnd();
            }
        }
    }
}

