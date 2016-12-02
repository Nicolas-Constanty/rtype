#pragma once

#ifndef BOXCOLLIDER2D_HPP_
#define BOXCOLLIDER2D_HPP_

#include "SaltyEngine/Collider.hpp"
#include "SaltyEngine/SFML/Rect.hpp"
#include "SaltyEngine/SFML/Renderer.hpp"

namespace SaltyEngine
{
	namespace SFML
	{
		class BoxCollider2D : public ACollider2D<sf::Vector2i>
		{
		public:
			explicit BoxCollider2D(GameObject * const gameObj) : ACollider2D("SFMLBoxCollider2D", gameObj), m_quad(sf::LinesStrip, 5) {
				m_quad[0].color = sf::Color::Green;
				m_quad[1].color = sf::Color::Green;
				m_quad[2].color = sf::Color::Green;
				m_quad[3].color = sf::Color::Green;
				m_quad[4].color = sf::Color::Green;
				Display();
				Renderer::AddDebug(this);
			};
			virtual ~BoxCollider2D() {};

		private:
			sf::VertexArray m_quad;

		public:
			void Display(void) override
			{
				ASpriteRenderer<sf::Vector2i> *sprr = gameObject->GetComponent<ASpriteRenderer<sf::Vector2i>>();
				if (sprr)
				{
					Sprite *spr = dynamic_cast<Sprite *>(sprr->GetSprite());
					if (spr)
					{
						Rect *bounds = dynamic_cast<Rect *>(spr->GetBounds());
						if (bounds)
						{
							m_bounds = bounds;
							m_quad[0].position = sf::Vector2f((float)bounds->left, (float)bounds->top);
							m_quad[1].position = sf::Vector2f((float)(bounds->left + bounds->width), (float)bounds->top);
							m_quad[2].position = sf::Vector2f((float)(bounds->left + bounds->width), (float)(bounds->top + bounds->height));
							m_quad[3].position = sf::Vector2f((float)bounds->left, (float)(bounds->top + bounds->height));
							m_quad[4].position = sf::Vector2f((float)bounds->left, (float)bounds->top);
						}
					}
				}
			};

		public:
			const sf::VertexArray &GetVertex(void) const
			{
				return m_quad;
			};

		public:
			virtual Component *CloneComponent(GameObject* const obj) {
				return new BoxCollider2D(obj);
			}
		};
	}
}

#endif // !BOXCOLLIDER2D_HPP_

