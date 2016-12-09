#include <Rtype/Game/Client/GameManager.hpp>
#include <Rtype/Game/Client/SpaceShipController.hpp>
#include "SaltyEngine/SFML.hpp"
#include "SaltyEngine/SaltyEngine.hpp"
#include "SaltyEngine/Object.hpp"

int main()
{
	SaltyEngine::SFML::AssetManager::Instance().LoadAssets();

	SaltyEngine::SFML::Renderer *renderer = new SaltyEngine::SFML::Renderer(sf::VideoMode(1280, 720), "R-Type Launcher");
	SaltyEngine::SFML::EventManager *event_manager = new SaltyEngine::SFML::EventManager(renderer->GetRenderWindow());
	// Set Renderer and EventManager
	Singleton<SaltyEngine::SaltyEngine>::Instance().SetRenderer(renderer);
	Singleton<SaltyEngine::SaltyEngine>::Instance().SetEventManager(event_manager);

	// Create Scene
	SaltyEngine::SFML::Scene *scene = new SaltyEngine::SFML::Scene();

	SaltyEngine::GameObject	*server = dynamic_cast<SaltyEngine::GameObject*>(SaltyEngine::Object::Instantiate());

    server->SetName("GameManager");
	server->AddComponent<Rtype::Game::Client::GameClientObject>("127.0.0.1", 4242);
	server->AddComponent<GameManager>();

	*scene << server;

	SaltyEngine::GameObject	*player = dynamic_cast<SaltyEngine::GameObject*>(SaltyEngine::Object::Instantiate());

	player->AddComponent<SaltyEngine::SpaceShipController>();

	*scene << player;

	SaltyEngine::SaltyEngine::Instance() << scene;

	SaltyEngine::SaltyEngine::Instance().Run();

	return (0);
}