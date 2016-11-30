#include <SFML/Graphics.hpp>
#include "SaltyEngine/SaltyEngine.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "SaltyEngine/SFML/Renderer.hpp"
#include "SaltyEngine/SFML/Button.hpp"
#include "SaltyEngine/Debug.hpp"
#include "SaltyEngine/Input.hpp"
#include "ClientLauncher/PlayerController.hpp"
#include "SaltyEngine/SFML/EventManager.hpp"

#include "SaltyEngine/SFML/AssetManager.hpp"

int main()
{
	SaltyEngine::SFML::Renderer *renderer = new SaltyEngine::SFML::Renderer(sf::VideoMode(1280, 720), "R-Type Launcher");
	SaltyEngine::SFML::EventManager *event_manager = new SaltyEngine::SFML::EventManager(renderer->GetRenderWindow());

	SaltyEngine::GameObject *player = new SaltyEngine::GameObject("Player");

    SaltyEngine::SFML::AssetManager::Instance().LoadTexture("Image");
    SaltyEngine::SFML::Texture *texture = SaltyEngine::SFML::AssetManager::Instance().GetTexture("Image");

	// Create Button
//	SaltyEngine::SFML::Texture *texture = new SaltyEngine::SFML::Texture();
//	if (!texture->loadFromFile("../../Assets/Textures/Image.png"))
//	{
//		SaltyEngine::Debug::PrintError("Failed to load texture");
//		return (1);
//	}
	SaltyEngine::SFML::Rect *rect = new SaltyEngine::SFML::Rect(10, 10, 100, 100);
	SaltyEngine::SFML::Sprite *spr = new SaltyEngine::SFML::Sprite(texture, rect);
	player->AddComponent<SaltyEngine::GUI::SFML::Button>(spr);
	player->AddComponent<SaltyEngine::PlayerController>();
	// Set SFML Renderer
	Singleton<SaltyEngine::SaltyEngine>::Instance().SetRenderer(renderer);
	Singleton<SaltyEngine::SaltyEngine>::Instance().SetEventManager(event_manager);
	// Create Scene
	SaltyEngine::Scene *scene(new SaltyEngine::Scene());

	*scene << player;
	// Push scene int SaltyEngine
	Singleton<SaltyEngine::SaltyEngine>::Instance() << scene;

	// Run the SaltyEngine with default Scene 0
	Singleton<SaltyEngine::SaltyEngine>::Instance().Run();
	return (0);
}
