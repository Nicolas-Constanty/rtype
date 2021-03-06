#include <Rtype/Game/Client/GameManager.hpp>
#include <Rtype/Game/Client/SpaceShipController.hpp>
#include "SaltyEngine/SFML.hpp"
#include "SaltyEngine/SaltyEngine.hpp"
#include "SaltyEngine/Object.hpp"

int main(int, char **)
{

#if _WIN32
	Network::Socket::WinSocket::Start();
#endif

	SaltyEngine::SFML::Renderer *renderer = new SaltyEngine::SFML::Renderer(sf::VideoMode(1920, 1080), "R-Type Launcher");
	SaltyEngine::SFML::EventManager *event_manager = new SaltyEngine::SFML::EventManager(renderer->GetRenderWindow());
	SaltyEngine::SFML::PhysicsHandler *ph = new SaltyEngine::SFML::PhysicsHandler(1920 / 2, 1080 / 2, false);
	SaltyEngine::Engine::Instance().SetPhysicsHandler(ph);
	// Set Renderer and EventManager
	Singleton<SaltyEngine::Engine>::Instance().SetRenderer(renderer);
	Singleton<SaltyEngine::Engine>::Instance().SetEventManager(event_manager);

//	SaltyEngine::Engine::Instance().SetFrameRate(30);

	// Create Scene
	SaltyEngine::SFML::Scene *scene = new SaltyEngine::SFML::Scene();

	SaltyEngine::Engine::Instance() << scene;

//	SaltyEngine::GameObject	*server = dynamic_cast<SaltyEngine::GameObject*>(SaltyEngine::Object::Instantiate(""));

	std::unique_ptr<SaltyEngine::GameObject> server;

	server.reset(new SaltyEngine::GameObject("Rtype", SaltyEngine::Layer::Tag::Destroy));
//	server->SetName("Rtype");
	SaltyEngine::SFML::AssetManager::Instance().LoadScene("scene2");
	server->AddComponent<Rtype::Game::Client::GameClientObject>("127.0.0.1", 4242);
	server->AddComponent<GameManager>();
	server->AddComponent<SaltyEngine::SFML::BoxCollider2D>(
			sf::Vector2u(40, 40)
	);
	server->transform.position = SaltyEngine::Vector2(50, 50);
//	server->transform.localScale = SaltyEngine::Vector2(2, 2);

	*scene << server.get();

//    SaltyEngine::GameObject	*player;
//    SaltyEngine::GameObject	*playerMoved;

//    if (ac > 1)
//    {
//        player = dynamic_cast<SaltyEngine::GameObject*>(SaltyEngine::Object::Instantiate());
//        playerMoved = dynamic_cast<SaltyEngine::GameObject*>(SaltyEngine::Object::Instantiate());
//    }
//    else
//    {
//        playerMoved = dynamic_cast<SaltyEngine::GameObject*>(SaltyEngine::Object::Instantiate());
//        player = dynamic_cast<SaltyEngine::GameObject*>(SaltyEngine::Object::Instantiate());
//    }

//    std::cout << "intanceID SERVER=" << server->GetInstanceID() << std::endl;
//    std::cout << "intanceID=" << player->GetInstanceID() << std::endl;

//    player->AddComponent<SaltyEngine::SpaceShipController>();
//	playerMoved->AddComponent<SaltyEngine::SpaceShipController>(false);

//    *scene << player;
//	*scene << playerMoved;

//	SaltyEngine::SaltyEngine::Instance().SetFrameRate(2);

	SaltyEngine::Engine::Instance().Run();

#if _WIN32
	Network::Socket::WinSocket::Stop();
#endif
	return (0);
}