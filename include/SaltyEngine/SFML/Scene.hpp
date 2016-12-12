#pragma once

#ifndef SFMLSCENE_HPP_
#define SFMLSCENE_HPP_

#include <SFML/Graphics.hpp>
#include "SaltyEngine/AScene.hpp"
#include "SaltyEngine/Collider.hpp"
#include "SaltyEngine/GUI/Selectable.hpp"

namespace SaltyEngine
{
	namespace SFML
	{
		class Scene : public AScene
		{
			typedef std::map <ACollider2D<sf::Vector2i> *, std::map<ACollider2D<sf::Vector2i> *, bool>> CollisionTab;
		public:
			Scene() : AScene() {};
			explicit Scene(const std::string &name) : AScene(name) {};
			~Scene() {};

		public:
			void UpdatePhysics() override;
			void operator<<(GameObject * const gameobj) override;

		private:
			CollisionTab m_collisions;
		};
	}
}

#endif // !SFMLSCENE_HPP_
