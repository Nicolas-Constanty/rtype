#pragma once

#ifndef SFMLRECT_HPP_
#define SFMLRECT_HPP_

#include <SFML/Graphics.hpp>
#include "SaltyEngine/BasicRect.hpp"

namespace SaltyEngine
{
	namespace SFML
	{
		class Rect : public ::SaltyEngine::BasicRect<sf::Vector2i>, public sf::IntRect
		{
		public:
            Rect(int rectLeft, int rectTop, int rectWidth, int rectHeight);
			Rect(const sf::Vector2<int>& position, const sf::Vector2<int>& size);

            virtual ~Rect() {}

		public:
			bool Contain(const sf::Vector2i &vec) const override;
			bool Intersect(IRect<sf::Vector2i> * const rect) const;
		};
		class FRect : public IRect<sf::Vector2f>, public sf::FloatRect
		{
		public:
			FRect(float rectLeft, float rectTop, float rectWidth, float rectHeight)
				: sf::FloatRect(rectLeft, rectTop, rectWidth, rectHeight) {}
			FRect(const sf::Vector2f& position, const sf::Vector2f& size)
				: sf::FloatRect(position, size) {}
			virtual ~FRect() {}

		public:
			bool Contain(const sf::Vector2f &vec) const override
			{
				return (contains(vec.x, vec.y));
			}

			bool Intersect(IRect<sf::Vector2f> * const rect) const override
			{
				FRect *r = dynamic_cast<FRect *>(rect);
				if (r)
					return intersects(*r);
				return false;
			};
		};
	}
}

#endif //!SFMLRECT_HPP_