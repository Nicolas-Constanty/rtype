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

namespace SaltyEngine {
    #define AssetManager SFML::AssetManager::Instance()
}

int main()
{
	SaltyEngine::SFML::Renderer *renderer = new SaltyEngine::SFML::Renderer(sf::VideoMode(1280, 720), "R-Type Launcher");
	SaltyEngine::SFML::EventManager *event_manager = new SaltyEngine::SFML::EventManager(renderer->GetRenderWindow());

	SaltyEngine::GameObject *player = new SaltyEngine::GameObject("Player");

    SaltyEngine::AssetManager.LoadAssets();

    SaltyEngine::SFML::Texture *texture = SaltyEngine::AssetManager.GetTexture("Image");

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
