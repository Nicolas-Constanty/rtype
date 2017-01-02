//
// Created by nicolas-constanty on 18/12/16.
//

#include "SaltyEngine/SFML/Rect.hpp"

namespace SaltyEngine
{
    namespace SFML
    {

        Rect::Rect(int rectLeft, int rectTop, int rectWidth, int rectHeight) :
                BasicRect(rectLeft, rectTop, rectWidth, rectHeight),
                sf::IntRect(rectLeft, rectTop, rectWidth, rectHeight)
        {

        }

        Rect::Rect(const sf::Vector2<int> &position, const sf::Vector2<int> &size) :
                BasicRect(position.x, position.y, size.x, size.y),
                sf::IntRect(position, size)
        {

        }

        bool Rect::Contain(const sf::Vector2i &vec) const {
                return (contains(vec.x, vec.y));
        }

        bool Rect::Intersect(IRect<sf::Vector2i> *const rect) const {
            Rect *r = dynamic_cast<Rect *>(rect);
            if (r)
                return intersects(*r);
            else
            {
                BasicRect<sf::Vector2i> *re = dynamic_cast<BasicRect<sf::Vector2i> *>(rect);
                if (re)
                {
                    return intersects(sf::IntRect(re->_left, re->_top, re->_width, re->_height));
                }
            }
            return false;
        }
    }
}
