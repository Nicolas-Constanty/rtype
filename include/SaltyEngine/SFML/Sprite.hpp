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
		class Sprite : public sf::Sprite, public ::SaltyEngine::Sprite<sf::Vector2i>
		{
		public:
			explicit Sprite(Texture* const texture)
				: sf::Sprite(*texture),
				  ::SaltyEngine::Sprite<sf::Vector2i>(dynamic_cast<::SaltyEngine::Texture<sf::Vector2i> *>(texture), "SFMLSprite") {}

			explicit Sprite(Texture* const texture, Rect* const rect)
				: sf::Sprite(*texture),
				::SaltyEngine::Sprite<sf::Vector2i>(dynamic_cast<::SaltyEngine::Texture<sf::Vector2i> *>(texture), rect, "SFMLSprite")
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