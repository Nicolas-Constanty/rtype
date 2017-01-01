#pragma once

#ifndef SFMLSPRITE_HPP_
#define SFMLSPRITE_HPP_

//#include <SFML/Graphics.hpp>
#include "SaltyEngine/SFML/Texture.hpp"
#include "SaltyEngine/SFML/Rect.hpp"
#include "SaltyEngine/Sprite.hpp"
#include "SaltyEngine/GameObject.hpp"

namespace SaltyEngine
{
	namespace SFML
	{
		class LIB_EXPORT Sprite : public ::SaltyEngine::Sprite<sf::Vector2i>, public sf::Sprite
		{
			Rect	*m_bounds;
		public:
			explicit Sprite(Texture* texture);

			Sprite(Texture* texture, Rect* const rect);

			virtual ~Sprite();

			Rect *GetBounds() const override;
		};
	}
}

#endif //!SFMLSPRITE_HPP_