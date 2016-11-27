#pragma once

#ifndef SPRITERENDERER_HPP_
#define SPRITERENDERER_HPP_

#include <SFML/Graphics.hpp>
#include "SaltyEngine/Config.hpp"
#include "SaltyEngine/ASpriteRenderer.hpp"
#include "SaltyEngine/SFML/Renderer.hpp"
#include "SaltyEngine/SFML/Sprite.hpp"
#include "SaltyEngine/SFML/Window.hpp"

namespace SaltyEngine
{
	namespace SFML
	{
		class SpriteRenderer : public ASpriteRenderer<sf::Vector2i>
		{
		public:
			// delete copy and move constructors and assign operators
			SpriteRenderer(SpriteRenderer const&) = delete;             // Copy construct
			SpriteRenderer(SpriteRenderer&&) = delete;                  // Move construct
			SpriteRenderer& operator=(SpriteRenderer const&) = delete;  // Copy assign
			SpriteRenderer& operator=(SpriteRenderer &&) = delete;      // Move assign
			explicit SpriteRenderer(const std::string &name, GameObject * const gameObj, Sprite * const sprite, Layout layer, Window * const w = nullptr) : ASpriteRenderer(name, gameObj, sprite, layer)
			{
				Renderer::AddSpriteRenderer(this);
				m_window = w;
			}
			explicit SpriteRenderer(GameObject* const gameObj, Sprite * const sprite, Layout layer, Window * const w = nullptr) : ASpriteRenderer("SpriteRenderer", gameObj, sprite, layer)
			{
				Renderer::AddSpriteRenderer(this);
				m_window = w;
			}
			virtual ~SpriteRenderer() {};
			Sprite* GetSprite() const override
			{
				return (dynamic_cast<Sprite*>(m_sprite));
			};

			IWindow *GetWindow() const override
			{
				return (m_window);
			}
		};
	}
}

#endif // !SPRITERENDERER_HPP_
