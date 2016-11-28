#pragma once

#ifndef RECT_HPP_
#define RECT_HPP_

#include <SFML/Graphics.hpp>
#include "SaltyEngine/IRect.hpp"

namespace SaltyEngine
{
	namespace SFML
	{
		class Rect : public IRect<sf::Vector2i>, public sf::IntRect
		{
		public:
			Rect(int rectLeft, int rectTop, int rectWidth, int rectHeight)
				: sf::IntRect(rectLeft, rectTop, rectWidth, rectHeight) {}
			Rect(const sf::Vector2<int>& position, const sf::Vector2<int>& size)
				: sf::IntRect(position, size) {}
			virtual ~Rect() {}

		public:
			bool Contain(const sf::Vector2i &vec) const override
			{
				return (contains(vec.x, vec.y));
			}
		};
	}
}

#endif //!RECT_HPP_