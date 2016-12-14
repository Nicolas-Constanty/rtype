#pragma once

#include <queue>
#include "SaltyEngine/SFML/AssetManager.hpp"
#include "SaltyEngine/SFML/SpriteRenderer.hpp"
#include "SaltyEngine/SaltyEngine.hpp"
#include "SaltyEngine/SaltyBehaviour.hpp"
#include "AnimationClip.hpp"
#include "SaltyEngine/Constants.hpp"
#include "SaltyEngine/ASpriteRenderer.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "SaltyEngine/SaltyEngine.hpp"
#include "SaltyEngine/AAnimation.hpp"
#include "SaltyEngine/Debug.hpp"

namespace SaltyEngine
{
    namespace SFML
    {
        class Animation : public AAnimation<sf::Vector2i> {
        private:

            class AnimData {
            public:
                AnimData(size_t frameCount, SFML::SpriteRenderer *sprite, const std::list<SFML::Sprite *> &frames,
                         double frameRate) :
                        m_frameCount(frameCount),
                        m_sprite(sprite),
                        m_frames(frames),
                        m_frameRate(frameRate),
                        m_iterator(frames.begin()),
                        m_reviterator(frames.rbegin()) {}

                bool IsAnimOver() const {
                    if (!m_playBackwards)
                        return m_iterator == m_frames.end();
                    else
                        return m_reviterator == m_frames.rend();
                }

                void Reset() {
                    m_iterator = m_frames.begin();
                    m_reviterator = m_frames.rbegin();
                }

                void ReverseAndReset() {
                    m_playBackwards = !m_playBackwards;
                    Reset();
                }

                void UpdateAnimTimeline(double deltaTime) {
                    m_elapsed += deltaTime;
                    if (m_elapsed >= m_frameRate) {
                        m_elapsed = 0;
                        if (!m_playBackwards) {
                            m_sprite->SetSprite(*m_iterator);
                            ++m_iterator;
                        } else {
                            m_sprite->SetSprite(*m_reviterator);
                            ++m_reviterator;
                        }
                    }
                }

            private:
                size_t m_frameCount;
                SFML::SpriteRenderer *m_sprite;
                const std::list<SFML::Sprite *> &m_frames;
                double m_frameRate;
                typename std::list<SFML::Sprite *>::const_iterator m_iterator;
                typename std::list<SFML::Sprite *>::const_reverse_iterator m_reviterator;
                double m_elapsed = 0;
                bool m_playBackwards = false;
            };

            AnimData *animData = nullptr;

        private:
            std::map<std::string, AnimationClip *> m_clips;

        public:
            Animation(GameObject *const obj, bool playAuto = true, AnimationConstants::WrapMode mode = AnimationConstants::WrapMode::ONCE) :
                    AAnimation(obj, playAuto, mode)
            {
            }

            virtual ~Animation() {
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

            /**
             * @brief Animation functions
             */
        public:
            void Play() {
                if (m_clips.size() == 0) {
                    return;
                }
                ClearAnimData();
                m_isPlaying = true;
                clip = m_clips.begin()->second;
                //StartCoroutine(&Animation::PlayAnim);
            }

            void Play(std::string const &name) {
                if (m_clips.size() == 0 || m_clips.find(name) == m_clips.end()) {
                    return;
                }
                ClearAnimData();
                m_isPlaying = true;
                clip = m_clips[name];
                //StartCoroutine(&Animation::PlayAnim);
            }

            void RemoveClip(std::string const &clipName) {
                if (m_clips.find(clipName) == m_clips.end()) {
                    return;
                }
                m_clips.erase(clipName);
            }

            void Stop(std::string const &name) {
                typename std::map<std::string, AnimationClip *>::iterator it = m_clips.find(name);
                if (it != m_clips.end() || it->second != clip) {
                    return;
                }
                m_isPlaying = false;
            }

            void AddClip(AnimationClip *const clip, std::string const &name) {
                m_clips[name] = clip;
            }

            size_t GetClipCount() const {
                return m_clips.size();
            }

        public:
            AnimationClip *clip = nullptr;

        private:
            void UpdateAnimations() {
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
                                Play(m_queuedAnims.back());
                                m_queuedAnims.pop();
                            } else {
                                switch (m_wrapMode) {
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

            /**
             * @brief Behaviour functions
             */
        public:
            void Start() {
                if (m_playAuto) {
                    Play();
                }
            }

            void FixedUpdate() {
                UpdateAnimations();
            }

            virtual Component *CloneComponent(GameObject *const obj) {
                Animation *anim = new Animation(obj, m_playAuto, m_wrapMode);
                for (typename std::map<std::string, AnimationClip *>::const_iterator it = m_clips.begin();
                     it != m_clips.end(); ++it) {
                    anim->AddClip(it->second->CopyClip(), it->first);
                }
                anim->m_queuedAnims = m_queuedAnims;
                anim->m_isPlaying = m_isPlaying;
                return anim;
            }

        private:
            void ClearAnimData(void)
            {
                if (animData != nullptr)
                    delete animData;
                animData = nullptr;
            }
        };
    }
}