#include "SaltyEngine/SFML.hpp"

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

	return (0);
}