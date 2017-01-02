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
		class LIB_EXPORT Scene : public AScene
		{
			typedef std::map <::SaltyEngine::ACollider2D<sf::Vector2i> *, std::map<::SaltyEngine::ACollider2D<sf::Vector2i> *, bool>> CollisionTab;
            typedef std::map <std::pair<::SaltyEngine::ACollider2D<sf::Vector2i> *, ::SaltyEngine::ACollider2D<sf::Vector2i> *>, bool> Coll;
		public:
			Scene() : AScene() {};
			explicit Scene(const std::string &name) : AScene(name) {};
			~Scene() {};

		public:
			void operator<<(GameObject * const gameobj) override;
			void InitScene(Component *const component) override;


		private:
			void Destroy() override ;
        };
	}
}

#endif // !SFMLSCENE_HPP_
