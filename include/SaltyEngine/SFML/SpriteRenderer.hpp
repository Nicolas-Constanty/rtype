#pragma once

#ifndef SPRITERENDERER_HPP_
#define SPRITERENDERER_HPP_

#include "SaltyEngine/SFML/Window.hpp"
#include "SaltyEngine/SFML/Sprite.hpp"
#include "SaltyEngine/SFML/Renderer.hpp"
#include "SaltyEngine/SFML/AssetManager.hpp"
#include "SaltyEngine/Config.hpp"
#include "SaltyEngine/ASpriteRenderer.hpp"

namespace SaltyEngine
{
    namespace SFML
    {
        class LIB_EXPORT SpriteRenderer : public ASpriteRenderer<sf::Vector2i>
        {
        public:
            // delete copy and move constructors and assign operators
            SpriteRenderer(SpriteRenderer const&) = delete;             // Copy construct
            SpriteRenderer(SpriteRenderer&&) = delete;                  // Move construct
            SpriteRenderer& operator=(SpriteRenderer const&) = delete;  // Copy assign
            SpriteRenderer& operator=(SpriteRenderer &&) = delete;      // Move assign
            explicit SpriteRenderer(const std::string &name, GameObject * const gameObj, Sprite * const sprite, Layout layer, Window * const w = nullptr);
            explicit SpriteRenderer(GameObject* const gameObj, Sprite * const sprite, Layout layer, Window * const w = nullptr);
            virtual ~SpriteRenderer() {}

        public:
            Sprite* GetSprite(void) const override;
            IWindow *GetWindow(void) const override;

        public:
            virtual Component *CloneComponent(GameObject* const obj);
        };
    }
}

#endif // !SPRITERENDERER_HPP_
