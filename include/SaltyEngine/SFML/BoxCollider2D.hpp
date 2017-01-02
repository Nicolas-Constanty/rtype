#pragma once

#ifndef BOXCOLLIDER2D_HPP_
#define BOXCOLLIDER2D_HPP_

#include "SaltyEngine/SFML/SpriteCollider2D.hpp"

namespace SaltyEngine
{
	namespace SFML
	{
		class LIB_EXPORT BoxCollider2D : public SpriteCollider2D {
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

#endif // !BOXCOLLIDER2D_HPP_

