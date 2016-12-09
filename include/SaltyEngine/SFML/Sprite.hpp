#pragma once

#ifndef SFMLSPRITE_HPP_
#define SFMLSPRITE_HPP_

//#include <SFML/Graphics.hpp>
#include "SaltyEngine/Sprite.hpp"
#include "SaltyEngine/SFML/Texture.hpp"
#include "SaltyEngine/SFML/Rect.hpp"
#include "SaltyEngine/GameObject.hpp"

namespace SaltyEngine
{
	namespace SFML
	{
		class Sprite : public ::SaltyEngine::Sprite<sf::Vector2i>, public sf::Sprite
		{
			Rect	*m_bounds;
		public:
			explicit Sprite(Texture* texture) :
				::SaltyEngine::Sprite<sf::Vector2i>(texture ? dynamic_cast<::SaltyEngine::Texture<sf::Vector2i> *>(texture) : []() { ::SaltyEngine::Texture<sf::Vector2i> *t = new Texture(); t->Create(200, 200); return t; }(), "SFMLSprite"),
				sf::Sprite(*dynamic_cast<Texture *>(GetTexture())) {
				m_bounds = new Rect(getGlobalBounds().left, getGlobalBounds().top, getGlobalBounds().width, getGlobalBounds().height);
			}

			explicit Sprite(Texture* texture, Rect* const rect) :
				::SaltyEngine::Sprite<sf::Vector2i>(texture ? dynamic_cast<::SaltyEngine::Texture<sf::Vector2i> *>(texture) : []() { ::SaltyEngine::Texture<sf::Vector2i> *t = new Texture(); t->Create(200, 200); return t; }(), rect, "SFMLSprite"),
				sf::Sprite(*dynamic_cast<Texture *>(GetTexture()))
			{
				setTextureRect(*rect);
				m_bounds = new Rect(getGlobalBounds().left, getGlobalBounds().top, getGlobalBounds().width, getGlobalBounds().height);
			}

			virtual ~Sprite() {
				delete m_bounds;
			}

			Rect *GetBounds() const override
			{
                m_bounds->left = getGlobalBounds().left;
                m_bounds->top = getGlobalBounds().top;
                m_bounds->width = getGlobalBounds().width;
                m_bounds->height = getGlobalBounds().height;
				return m_bounds;
			}
		};
	}
}

#endif //!SFMLSPRITE_HPP_