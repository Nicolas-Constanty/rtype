#pragma once
#include "SaltyEngine/GUI/UIBehaviour.hpp"
#include "SaltyEngine/SFML/Sprite.hpp"

namespace SaltyEngine
{
	namespace SFML
	{
		namespace GUI
		{
			class Image : public ::SaltyEngine::GUI::UIBehaviour
			{
			public:
				explicit Image(GameObject* gameObj, ::SaltyEngine::SFML::Sprite * const sprite);
				Image(const std::string& name, GameObject* gameObj, ::SaltyEngine::SFML::Sprite * const sprite);
				~Image();
			};
		}
	}
}

