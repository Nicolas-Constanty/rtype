#include "SaltyEngine/SFML.hpp"

int main()
{
//    SaltyEngine::SFML::AssetManager::Instance().LoadAssets();

    SaltyEngine::SFML::Renderer *renderer = new SaltyEngine::SFML::Renderer(sf::VideoMode(1280, 720), "R-Type Launcher");
	SaltyEngine::SFML::EventManager *event_manager = new SaltyEngine::SFML::EventManager(renderer->GetRenderWindow());
	// Set Renderer and EventManager
	Singleton<SaltyEngine::Engine>::Instance().SetRenderer(renderer);
	Singleton<SaltyEngine::Engine>::Instance().SetEventManager(event_manager);

	// Create Scene
	SaltyEngine::SFML::Scene *scene = new SaltyEngine::SFML::Scene();

	// Push scene int SaltyEngine
	Singleton<SaltyEngine::Engine>::Instance() << scene;

    // Load scene
	std::list<std::pair<std::string, SaltyEngine::Vector2f> > assets = SaltyEngine::SFML::AssetManager::Instance().LoadScene("scene1");

	for (std::list<std::pair<std::string, SaltyEngine::Vector2f>>::const_iterator it = assets.begin(); it != assets.end(); ++it) {
		SaltyEngine::Debug::PrintInfo("Instantiate " + it->first);
		SaltyEngine::Instantiate(it->first, it->second);
	}
	SaltyEngine::GameObject *obj = new SaltyEngine::GameObject("Destroyer", SaltyEngine::Layer::Tag::Destroy);
    obj->AddComponent<SaltyEngine::SFML::BoxCollider2D>(SaltyEngine::SFML::Rect(0, 0, 20, 1500));
    obj->transform.position = SaltyEngine::Vector(1290, 0);
    *scene << obj;
	// Run the SaltyEngine with default Scene 0
	Singleton<SaltyEngine::Engine>::Instance().Run();
	return (0);
}
