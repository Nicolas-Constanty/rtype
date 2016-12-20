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
#include "Common/Debug.hpp"

namespace SaltyEngine
{
    namespace SFML
    {
        class Animation : public AAnimation {
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
                        m_reviterator(frames.rbegin())
                {
                    m_sprite->SetSprite(*frames.begin());
                }

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
            mutable std::map<std::string, AnimationClip *> m_clips;

        public:
            Animation(GameObject *const obj, bool playAuto = true, AnimationConstants::WrapMode mode = AnimationConstants::WrapMode::ONCE);

            virtual ~Animation();

            /**
             * @brief Animation functions
             */
        public:
            void Play();

            void Play(std::string const &name);
            void RemoveClip(std::string const &clipName);

            void Stop(std::string const &name);

            void AddClip(AnimationClip *const clip, std::string const &name);

            size_t GetClipCount() const;

            AnimationClip *GetClip(std::string const& name) const;
            AnimationClip *GetClip(int id) const;

        public:
            AnimationClip *clip = nullptr;

        private:
            void UpdateAnimations();

            /**
             * @brief Behaviour functions
             */
        public:
            void Start();

            void FixedUpdate();

            virtual Component *CloneComponent(GameObject *const obj);

            void Stop() override;

        private:
            void ClearAnimData(void);
        };
    }
}