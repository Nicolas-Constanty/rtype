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
        class LIB_EXPORT AnimationClip : public AAnimationClip {
        private:
            std::list<Sprite *> m_sprites;

        public:
            AnimationClip(std::string const &name = "Animation", int frameRate = 60, AnimationConstants::WrapMode mode = AnimationConstants::WrapMode::ONCE);

            virtual ~AnimationClip();

        public:
            void AddSprite(::SaltyEngine::SFML::Sprite *const sprite);

            const std::list<Sprite*> &GetFrames() const;

            void operator<<(Sprite *const sprite);
        };
    }
}