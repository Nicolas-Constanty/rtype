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
            Rect(int rectLeft, int rectTop, int rectWidth, int rectHeight) :
            BasicRect(rectLeft, rectTop, rectWidth, rectHeight),
            sf::IntRect(rectLeft, rectTop, rectWidth, rectHeight) {}
			Rect(const sf::Vector2<int>& position, const sf::Vector2<int>& size) :
					BasicRect(position.x, position.y, size.x, size.y),
				  	sf::IntRect(position, size) {}

            virtual ~Rect() {}

		public:
			bool Contain(const sf::Vector2i &vec) const override
			{
				return (contains(vec.x, vec.y));
			}
			bool Intersect(IRect<sf::Vector2i> * const rect) const override
			{
				Rect *r = dynamic_cast<Rect *>(rect);
				if (r)
					return intersects(*r);
                else
                {
                    BasicRect<sf::Vector2i> *re = dynamic_cast<BasicRect<sf::Vector2i> *>(rect);
                    if (re)
					{
//						return BasicRect<sf::Vector2i>::Intersect(re);
						return intersects(sf::IntRect(re->_left, re->_top, re->_width, re->_height));
					}
                }
				return false;
			}
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