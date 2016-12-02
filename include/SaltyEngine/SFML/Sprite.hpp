#pragma once

#ifndef SFMLSPRITE_HPP_
#define SFMLSPRITE_HPP_

#include <SFML/Graphics.hpp>
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
		public:
			explicit Sprite(Texture* const texture) :
				::SaltyEngine::Sprite<sf::Vector2i>(texture ? dynamic_cast<::SaltyEngine::Texture<sf::Vector2i> *>(texture) : []() { ::SaltyEngine::Texture<sf::Vector2i> *t = new Texture(); t->Create(200, 200); return t; }(), "SFMLSprite"),
				sf::Sprite(*dynamic_cast<Texture *>(GetTexture())) {}

			explicit Sprite(Texture* const texture, Rect* const rect) :
				::SaltyEngine::Sprite<sf::Vector2i>(texture ? dynamic_cast<::SaltyEngine::Texture<sf::Vector2i> *>(texture) : []() { ::SaltyEngine::Texture<sf::Vector2i> *t = new Texture(); t->Create(200, 200); return t; }(), rect, "SFMLSprite"),
				sf::Sprite(*dynamic_cast<Texture *>(GetTexture()))
			{
				setTextureRect(*rect);
			}

			Rect *GetBounds() const override
			{
				return new Rect(getGlobalBounds().left, getGlobalBounds().top, getGlobalBounds().width, getGlobalBounds().height);
			}
		};
	}
}

#endif //!SFMLSPRITE_HPP_