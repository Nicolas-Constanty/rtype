#include <SFML/Graphics.hpp>
#include "SaltyEngine/SaltyEngine.hpp"
#include "SaltyEngine/SFML/Renderer.hpp"
#include "SaltyEngine/SFML/Button.hpp"
#include "SaltyEngine/Input.hpp"
#include "Player/PlayerController.hpp"
#include "SaltyEngine/SFML/EventManager.hpp"
#include "SaltyEngine/Animation.hpp"
#include "SaltyEngine/SFML/Scene.hpp"
#include "SaltyEngine/SFML/AssetManager.hpp"

int main()
{
//    SaltyEngine::SFML::AssetManager::Instance().LoadAssets();

    SaltyEngine::SFML::Renderer *renderer = new SaltyEngine::SFML::Renderer(sf::VideoMode(1280, 720), "R-Type Launcher");
	SaltyEngine::SFML::EventManager *event_manager = new SaltyEngine::SFML::EventManager(renderer->GetRenderWindow());
	// Set Renderer and EventManager
	Singleton<SaltyEngine::SaltyEngine>::Instance().SetRenderer(renderer);
	Singleton<SaltyEngine::SaltyEngine>::Instance().SetEventManager(event_manager);

	// Create Scene
	SaltyEngine::SFML::Scene *scene = new SaltyEngine::SFML::Scene();

	// Create monster with sprites

    // Load scene
	std::list<std::pair<std::string, SaltyEngine::Vector2f>>	assets = SaltyEngine::SFML::AssetManager::Instance().LoadScene("scene1");

	for (std::list<std::pair<std::string, SaltyEngine::Vector2f>>::const_iterator it = assets.begin(); it != assets.end(); ++it) {
		std::cout << "Instantiate " << it->first << std::endl;
		*scene << (SaltyEngine::GameObject*)SaltyEngine::Object::Instantiate(it->first, it->second);
	}

	// Push scene int SaltyEngine
	Singleton<SaltyEngine::SaltyEngine>::Instance() << scene;

	// Run the SaltyEngine with default Scene 0
	Singleton<SaltyEngine::SaltyEngine>::Instance().Run();
	return (0);
}
