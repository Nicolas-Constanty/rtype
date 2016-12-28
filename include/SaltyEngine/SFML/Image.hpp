#pragma once

#include "SaltyEngine/SFML/Sprite.hpp"
#include "SaltyEngine/GUI/UIBehaviour.hpp"

namespace SaltyEngine
{
	namespace SFML
	{
		namespace GUI
		{
			class LIB_EXPORT Image : public ::SaltyEngine::GUI::UIBehaviour
			{
			public:
				explicit Image(GameObject* gameObj, ::SaltyEngine::SFML::Sprite * const sprite);
				Image(const std::string& name, GameObject* gameObj, ::SaltyEngine::SFML::Sprite * const sprite);
				~Image();
			};
		}
	}
}

