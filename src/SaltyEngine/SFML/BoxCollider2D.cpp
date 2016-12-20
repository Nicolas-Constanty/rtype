//
// Created by nicolas-constanty on 17/12/16.
//

#include "SaltyEngine/SFML/BoxCollider2D.hpp"

namespace SaltyEngine
{
    namespace SFML
    {
        BoxCollider2D::BoxCollider2D(GameObject *const gameObj, const sf::Vector2u &size, bool debug)
                : SpriteCollider2D("BoxCollider2D", gameObj, size),
                  m_quad(sf::LinesStrip, 5), m_debug(debug)
        {
            if (m_debug)
                {
                    m_quad[0].color = sf::Color::Green;
                    m_quad[1].color = sf::Color::Green;
                    m_quad[2].color = sf::Color::Green;
                    m_quad[3].color = sf::Color::Green;
                    m_quad[4].color = sf::Color::Green;
                }
        }

        void BoxCollider2D::Display(void) {
            if (!m_debug)
                return;
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
                        m_quad[0].position = sf::Vector2f(bounds->left, bounds->top);
                        m_quad[1].position = sf::Vector2f(bounds->left + bounds->width, bounds->top);
                        m_quad[2].position = sf::Vector2f(bounds->left + bounds->width, bounds->top + bounds->height);
                        m_quad[3].position = sf::Vector2f(bounds->left, bounds->top + bounds->height);
                        m_quad[4].position = sf::Vector2f((float)bounds->left, bounds->top);
                    }
                }
            }
//            else
//            {
//                //::SaltyEngine::BasicRect<sf::Vector2i> *rect = dynamic_cast<::SaltyEngine::BasicRect<sf::Vector2i> *>(m_bounds);
//                l = (int) (gameObject->transform.position.x - rect->_width / 2);
//                rect->_top = (int) (gameObject->transform.position.y - rect->_height / 2);
//                m_quad[0].position = sf::Vector2f((float)rect->_left, (float)rect->_top);
//                m_quad[1].position = sf::Vector2f((float)(rect->_left + rect->_width), (float)rect->_top);
//                m_quad[2].position = sf::Vector2f((float)(rect->_left + rect->_width), (float)(rect->_top + rect->_height));
//                m_quad[3].position = sf::Vector2f((float)rect->_left, (float)(rect->_top + rect->_height));
//                m_quad[4].position = sf::Vector2f((float)rect->_left, (float)rect->_top);
//            }
        }

        const sf::VertexArray &BoxCollider2D::GetVertex(void) const {
            return m_quad;
        }

        Component *BoxCollider2D::CloneComponent(GameObject *const obj) {
            return new BoxCollider2D(obj, GetSize());
        }

        bool BoxCollider2D::IsDebug() const {
            return m_debug;
        }
    }
}