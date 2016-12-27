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
#include "Common/DLLexport.hpp"

namespace SaltyEngine
{
    namespace SFML
    {
        class LIB_EXPORT Animation : public AAnimation {
        private:

            class AnimData {
            public:
                AnimData(AnimationClip * clip, SFML::SpriteRenderer *sprite);

                bool IsAnimOver() const;
                void Reset();
                void ReverseAndReset();
                void UpdateAnimTimeline(double deltaTime);

            private:
                AnimationClip *m_clip;
                size_t m_frameCount;
                SFML::SpriteRenderer *m_spriteRenderer;
                const std::list<SFML::Sprite *> &m_frames;
                double m_frameRate;
                typename std::list<SFML::Sprite *>::const_iterator m_iterator;
                typename std::list<SFML::Sprite *>::const_reverse_iterator m_reviterator;
                double m_elapsed = 0;
                bool m_playBackwards = false;
                size_t m_currentFrame = 0;
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

            bool IsPlaying(std::string const &name) const override;

        private:
            void ClearAnimData(void);
        };
    }
}