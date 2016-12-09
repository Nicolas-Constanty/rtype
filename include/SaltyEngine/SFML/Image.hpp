#pragma once
#include "SaltyEngine/GUI/UIBehaviour.hpp"
#include "SaltyEngine/SFML/Sprite.hpp"

namespace SaltyEngine
{
	namespace SFML
	{
		class Image : public GUI::UIBehaviour
		{
		public:
			Image(GameObject* gameObj, ::SaltyEngine::SFML::Sprite * const sprite);
			Image(const std::string& name, GameObject* gameObj, ::SaltyEngine::SFML::Sprite * const sprite);
			~Image();
		};
	}
}

