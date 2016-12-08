#include "Rtype/Game/Client/SpaceShipController.hpp"
#include "SaltyEngine/SFML.hpp"

SaltyEngine::SpaceShipController::SpaceShipController(GameObject * const gamObj) : SaltyBehaviour("SpaceShipController", gamObj)
{
	::SaltyEngine::SFML::Texture *texture = ::SaltyEngine::SFML::AssetManager::Instance().GetTexture("SpaceShips");
	if (texture != nullptr)
	{
		gameObject->AddComponent<::SaltyEngine::SFML::SpriteRenderer>(new ::SaltyEngine::SFML::Sprite(texture, new ::SaltyEngine::SFML::Rect(0, 0, 34, 34)), ::SaltyEngine::Layout::normal);
	}
}

SaltyEngine::SpaceShipController::SpaceShipController(const std::string & name, GameObject * const gamObj) : SaltyBehaviour("SpaceShipController", gamObj)
{
}

void SaltyEngine::SpaceShipController::Start()
{
}

void SaltyEngine::SpaceShipController::FixedUpdate()
{
}

void SaltyEngine::SpaceShipController::DisplayCoroutine()
{
}
