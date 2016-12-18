#include "SaltyEngine/SFML.hpp"
#include "TestCollision.hpp"

int main()
{
//    SaltyEngine::SFML::AssetManager::Instance().LoadAssets();

    SaltyEngine::SFML::Renderer *renderer = new SaltyEngine::SFML::Renderer(sf::VideoMode(1280, 720), "R-Type Launcher");
	SaltyEngine::SFML::EventManager *event_manager = new SaltyEngine::SFML::EventManager(renderer->GetRenderWindow());
	SaltyEngine::SFML::PhysicsHandler *ph = new SaltyEngine::SFML::PhysicsHandler(1280 / 2, 720 / 2, false);
	SaltyEngine::Engine::Instance().SetPhysicsHandler(ph);
	// Set Renderer and EventManager
	Singleton<SaltyEngine::Engine>::Instance().SetRenderer(renderer);
	Singleton<SaltyEngine::Engine>::Instance().SetEventManager(event_manager);

	// Create Scene
	SaltyEngine::SFML::Scene *scene = new SaltyEngine::SFML::Scene();

	// Push scene int SaltyEngine


    // Load scene
//	SaltyEngine::SFML::AssetManager::Instance().LoadScene("scene1");

//	for (std::list<std::pair<std::string, SaltyEngine::Vector2f>>::const_iterator it = assets.begin(); it != assets.end(); ++it) {
//		Debug::PrintInfo("Instantiate " + it->first);
//		SaltyEngine::Instantiate(it->first, it->second);
//	}
	SaltyEngine::GameObject *obj = new SaltyEngine::GameObject("Destroyer", SaltyEngine::Layer::Tag::Destroy);
    obj->AddComponent<SaltyEngine::SFML::BoxCollider2D>(sf::Vector2u(100, 100));
    //obj->transform.position = SaltyEngine::Vector(200, 200);
	obj->transform.position = SaltyEngine::Vector(82, 50);
	obj->transform.localScale = SaltyEngine::Vector(2, 2);
    *scene << obj;
	obj = new SaltyEngine::GameObject("Player", SaltyEngine::Layer::Tag::Player);
	SaltyEngine::SFML::Texture texture;
	if (!texture.loadFromFile("./Assets/Textures/SpaceShips.png"))
		return 0;
	SaltyEngine::SFML::Rect *rect = new SaltyEngine::SFML::Rect(0, 3, 32, 14);
	SaltyEngine::SFML::Sprite *spr = new SaltyEngine::SFML::Sprite(&texture, rect);
	obj->AddComponent<SaltyEngine::SFML::SpriteRenderer>(spr, SaltyEngine::Layout::normal);
	obj->AddComponent<SaltyEngine::SFML::SpriteCollider2D>();
	obj->AddComponent<TestCollision>();
	obj->transform.localScale = SaltyEngine::Vector(2, 2);
	obj->transform.position = SaltyEngine::Vector(30, 7);
	*scene << obj;
	for (int j = 0; j < 20; ++j) {
		obj = new SaltyEngine::GameObject("Player(Clone)", SaltyEngine::Layer::Tag::Player);
		rect = new SaltyEngine::SFML::Rect(0, 3, 32, 14);
		spr = new SaltyEngine::SFML::Sprite(&texture, rect);
		obj->AddComponent<SaltyEngine::SFML::SpriteRenderer>(spr, SaltyEngine::Layout::normal);
		obj->AddComponent<SaltyEngine::SFML::SpriteCollider2D>();
		obj->transform.localScale = SaltyEngine::Vector(2, 2);
		obj->transform.position = SaltyEngine::Vector(30 * j, 7 * j);
		*scene << obj;
	}
	// Run the SaltyEngine with default Scene 0
	Singleton<SaltyEngine::Engine>::Instance() << scene;
	Singleton<SaltyEngine::Engine>::Instance().Run();
	return (0);
}
