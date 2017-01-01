#include "SaltyEngine/SFML/SpriteRenderer.hpp"
#include "SaltyEngine/SFML/Image.hpp"

namespace SaltyEngine
{
	namespace SFML
	{
		namespace GUI
		{
			Image::Image(GameObject* gameObj, ::SaltyEngine::SFML::Sprite* const sprite) : UIBehaviour(gameObj)
			{
				SpriteRenderer* sprr = gameObject->GetComponent<SpriteRenderer>();
				if (sprr == nullptr)
					gameObject->AddComponent<SpriteRenderer>(sprite, Layout::gui);
				else
				{
					sprr->SetLayout(Layout::gui);
					sprr->SetSprite(sprite);
				}
			}

			Image::Image(const std::string& name, GameObject* gameObj, ::SaltyEngine::SFML::Sprite* const sprite) : UIBehaviour(name, gameObj)
			{
				gameObject->AddComponent<SpriteRenderer>(sprite, Layout::gui);
			}

			Image::~Image()
			{
			}
		}
	}
}


