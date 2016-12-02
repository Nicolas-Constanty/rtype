#include <SFML/Graphics.hpp>
#include "SaltyEngine/SaltyEngine.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "SaltyEngine/SFML/Renderer.hpp"
#include "SaltyEngine/SFML/Button.hpp"
#include "SaltyEngine/Debug.hpp"
#include "SaltyEngine/Input.hpp"
#include "ClientLauncher/PlayerController.hpp"
#include "SaltyEngine/SFML/EventManager.hpp"
#include "SaltyEngine/Animation.hpp"
#include "Monster/MonsterController.hpp"
#include "SaltyEngine/SFML/Scene.hpp"
#include "ClientLauncher/RtypeFactory.hpp"
#include "Monster/Monster.hpp"

template <>
const std::vector<std::string> RtypeFactory<Monster>::names = {
	"Monster"
};

#include "SaltyEngine/SFML/AssetManager.hpp"

namespace SaltyEngine {
    #define AssetManager SFML::AssetManager::Instance()
}

int main()
{
	SaltyEngine::SFML::Renderer *renderer = new SaltyEngine::SFML::Renderer(sf::VideoMode(1280, 720), "R-Type Launcher");
	SaltyEngine::SFML::EventManager *event_manager = new SaltyEngine::SFML::EventManager(renderer->GetRenderWindow());
	// Set Renderer and EventManager
	Singleton<SaltyEngine::SaltyEngine>::Instance().SetRenderer(renderer);
	Singleton<SaltyEngine::SaltyEngine>::Instance().SetEventManager(event_manager);

	SaltyEngine::GameObject *player = new SaltyEngine::GameObject("Player");
    player->AddComponent<SaltyEngine::PlayerController>();

    ::SaltyEngine::AssetManager.LoadAssets();

    SaltyEngine::SFML::Texture *texture = SaltyEngine::AssetManager.GetTexture("Image");

	SaltyEngine::SFML::Rect *rect = new SaltyEngine::SFML::Rect(10, 10, 100, 100);
	SaltyEngine::SFML::Sprite *spr = new SaltyEngine::SFML::Sprite(texture, rect);

	// Create Scene
	SaltyEngine::SFML::Scene *scene = new SaltyEngine::SFML::Scene();

	RtypeFactory<Monster>	factory;
	// Create monster with sprites
	SaltyEngine::GameObject *monster = factory.create("Monster");
	monster->AddComponent<SaltyEngine::SFML::SpriteRenderer>(spr, SaltyEngine::Layout::normal);
	monster->AddComponent<SaltyEngine::PlayerController>();
	monster->AddComponent<SaltyEngine::SFML::BoxCollider2D>();

	rect = new SaltyEngine::SFML::Rect(100, 10, 100, 100);
	spr = new SaltyEngine::SFML::Sprite(texture, rect);
	SaltyEngine::GameObject *monster2 = factory.create("Monster");
	monster2->AddComponent<SaltyEngine::SFML::SpriteRenderer>(spr, SaltyEngine::Layout::normal);
	monster2->AddComponent<SaltyEngine::SFML::BoxCollider2D>();
	monster2->transform.position.x = 200;
	monster2->transform.position.y = 200;

    std::cout << "xx" << monster->GetComponent<MonsterController>() << std::endl;
    std::cout << monster2->GetComponent<MonsterController>() << std::endl;

	//*scene << player;
	*scene << monster;
	*scene << monster2;
	// Push scene int SaltyEngine
	Singleton<SaltyEngine::SaltyEngine>::Instance() << scene;

	// Run the SaltyEngine with default Scene 0
	Singleton<SaltyEngine::SaltyEngine>::Instance().Run();
	return (0);
}
