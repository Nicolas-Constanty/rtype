#pragma once

#ifndef BOXCOLLIDER2D_HPP_
#define BOXCOLLIDER2D_HPP_

#include "SaltyEngine/SFML/SpriteCollider2D.hpp"

namespace SaltyEngine
{
	namespace SFML
	{
		class BoxCollider2D : public SpriteCollider2D {
		    public:
                BoxCollider2D(GameObject * const gameObj, const sf::Vector2u &size, bool debug = true);

        private:
			sf::VertexArray m_quad;

		public:
			void Display(void) override;

		public:
			const sf::VertexArray &GetVertex(void) const;

		public:
			virtual Component *CloneComponent(GameObject* const obj);

        private:
            bool m_debug;

        public:
            bool IsDebug() const;
		};
    }
}
//		class BoxCollider2D : public ACollider2D<sf::Vector2i>
//		{
//		public:
//			explicit BoxCollider2D(GameObject * const gameObj, bool debug = true) : ACollider2D("SFMLBoxCollider2D", gameObj), m_quad(sf::LinesStrip, 5), m_debug(debug) {
//
//                if (m_debug)
//                {
//                    m_quad[0].color = sf::Color::Green;
//                    m_quad[1].color = sf::Color::Green;
//                    m_quad[2].color = sf::Color::Green;
//                    m_quad[3].color = sf::Color::Green;
//                    m_quad[4].color = sf::Color::Green;
//                }
//            };
//			virtual ~BoxCollider2D() {};
//
//            BoxCollider2D(GameObject * const gameObj, Rect rect, bool debug = true) :
//                    ACollider2D("SFMLBoxCollider2D", gameObj,
//                                new ::SaltyEngine::BasicRect<sf::Vector2i>(rect.left, rect.top, rect.width, rect.height)),
//                    m_quad(sf::LinesStrip, 5), m_debug(debug)
//            {
//                if (m_debug)
//                {
//                    m_quad[0].color = sf::Color::Green;
//                    m_quad[1].color = sf::Color::Green;
//                    m_quad[2].color = sf::Color::Green;
//                    m_quad[3].color = sf::Color::Green;
//                    m_quad[4].color = sf::Color::Green;
//                }
//            }
//
//		private:
//			sf::VertexArray m_quad;
//
//		public:
//			void Display(void) override
//			{
//                if (!m_debug)
//                    return;
//				ASpriteRenderer<sf::Vector2i> *sprr = gameObject->GetComponent<ASpriteRenderer<sf::Vector2i>>();
//				if (sprr)
//				{
//					Sprite *spr = dynamic_cast<Sprite *>(sprr->GetSprite());
//					if (spr)
//					{
//						Rect *bounds = dynamic_cast<Rect *>(spr->GetBounds());
//						if (bounds)
//						{
//							m_bounds = bounds;
//							m_quad[0].position = sf::Vector2f((float)bounds->left, (float)bounds->top);
//							m_quad[1].position = sf::Vector2f((float)(bounds->left + bounds->width), (float)bounds->top);
//							m_quad[2].position = sf::Vector2f((float)(bounds->left + bounds->width), (float)(bounds->top + bounds->height));
//							m_quad[3].position = sf::Vector2f((float)bounds->left, (float)(bounds->top + bounds->height));
//							m_quad[4].position = sf::Vector2f((float)bounds->left, (float)bounds->top);
//						}
//					}
//				}
//                else
//                {
//                    ::SaltyEngine::BasicRect<sf::Vector2i> *rect = dynamic_cast<::SaltyEngine::BasicRect<sf::Vector2i> *>(m_bounds);
//                    rect->_left = (int) (gameObject->transform.position.x - rect->_width / 2);
//                    rect->_top = (int) (gameObject->transform.position.y - rect->_height / 2);
//					m_bounds = rect;
//                    m_quad[0].position = sf::Vector2f((float)rect->_left, (float)rect->_top);
//                    m_quad[1].position = sf::Vector2f((float)(rect->_left + rect->_width), (float)rect->_top);
//                    m_quad[2].position = sf::Vector2f((float)(rect->_left + rect->_width), (float)(rect->_top + rect->_height));
//                    m_quad[3].position = sf::Vector2f((float)rect->_left, (float)(rect->_top + rect->_height));
//                    m_quad[4].position = sf::Vector2f((float)rect->_left, (float)rect->_top);
//                }
//			};
//
//		public:
//			const sf::VertexArray &GetVertex(void) const
//			{
//				return m_quad;
//			};
//
//		public:
//			virtual Component *CloneComponent(GameObject* const obj) {
//				return new BoxCollider2D(obj);
//			}
//
//        private:
//            bool m_debug;
//
//        public:
//            bool IsDebug() const {
//                return m_debug;
//            }
//        };

#endif // !BOXCOLLIDER2D_HPP_

