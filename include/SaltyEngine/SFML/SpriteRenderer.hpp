#pragma once

#ifndef SPRITERENDERER_HPP_
#define SPRITERENDERER_HPP_

#include <SFML/Graphics.hpp>
#include "SaltyEngine/Config.hpp"
#include "SaltyEngine/ASpriteRenderer.hpp"
#include "SaltyEngine/SFML/Sprite.hpp"
#include "SaltyEngine/SFML/Window.hpp"
#include "SaltyEngine/SFML/Renderer.hpp"

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
				Rect *rect = dynamic_cast<Rect *>(GetSprite()->GetRect());
				sprite->setPosition(gameObject->transform.position.x - (rect->width / 2),
					gameObject->transform.position.y - (rect->height / 2));
			}
			explicit SpriteRenderer(GameObject* const gameObj, Sprite * const sprite, Layout layer, Window * const w = nullptr) : ASpriteRenderer("SpriteRenderer", gameObj, sprite, layer)
			{
				Renderer::AddSpriteRenderer(this);
				m_window = w;
				Rect *rect = dynamic_cast<Rect *>(GetSprite()->GetRect());
				sprite->setPosition(gameObject->transform.position.x - (rect->width / 2),
					gameObject->transform.position.y - (rect->height / 2));
			}
			virtual ~SpriteRenderer() {};
			Sprite* GetSprite(void) const override
			{
				return (dynamic_cast<Sprite*>(m_sprite));
			};

			IWindow *GetWindow(void) const override
			{
				return (m_window);
			}
		};
	}
}

#endif // !SPRITERENDERER_HPP_
