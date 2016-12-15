#pragma once
#include <functional>
#include <list>
#include "SaltyEngine/SFML/Texture.hpp"
#include "SaltyEngine/SFML/Sprite.hpp"
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
            AnimationClip(std::string const &name = "Animation", int frameRate = 60, AnimationConstants::WrapMode mode = AnimationConstants::WrapMode::ONCE) :
                    AAnimationClip(name, frameRate, mode)
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
        };
    }
}