#pragma once
#include <functional>
#include <list>
#include "SaltyEngine/SFML/AssetManager.hpp"
#include "SaltyEngine/Object.hpp"
#include "SaltyEngine/Sprite.hpp"
#include "SaltyEngine/AAnimationClip.hpp"

namespace SaltyEngine
{
	namespace SFML
    {
        class AnimationClip : public AAnimationClip<sf::Vector2i> {
        private:
            std::list<Sprite *> m_sprites;

        public:
            AnimationClip(std::string const &name = "Animation", int frameRate = 60) :
                    AAnimationClip(name, frameRate)
            {}

            virtual ~AnimationClip() {}

        public:
            void AddSprite(::SaltyEngine::SFML::Sprite *const sprite) {
                if (sprite)
                    m_sprites.push_back(sprite);
                else
                    Debug::PrintWarning("Cannot add nullptr");
            }

            const std::list<Sprite*> &GetFrames() const {
                return m_sprites;
            }

            void operator<<(Sprite *const sprite) {
                AddSprite(sprite);
            }

        public:
            AnimationClip *CopyClip() {
                AnimationClip *animationclip = new AnimationClip("Animation(Clone)", m_frameRate);
                for (std::list<std::function<void()>>::const_iterator j = m_events.begin(); j != m_events.end(); ++j) {
                    animationclip->m_events.push_back(*j);
                }
                for (Sprite *sprite : m_sprites) {
                    if (sprite)
                        animationclip->AddSprite(SFML::AssetManager::Instance().GetSprite(sprite->GetName()));
                }
                return animationclip;
            }
        };
    }
}