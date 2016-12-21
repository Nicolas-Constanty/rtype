#include <Rtype/Game/Client/GameManager.hpp>
#include <Rtype/Game/Client/SpaceShipController.hpp>
#include <Rtype/Game/Client/GameGUIBeam.hpp>
#include <Rtype/Game/Client/GameGUIHighscore.hpp>
#include "SaltyEngine/SFML.hpp"
#include "SaltyEngine/SaltyEngine.hpp"
#include "SaltyEngine/Object.hpp"

void CreateGUIGame(SaltyEngine::Vector2i const &size, SaltyEngine::SFML::Scene *scene) {

//	SaltyEngine::GameObject *guiBehind = new SaltyEngine::GameObject("GUIBackgroundGame");
//	guiBehind->AddComponent<SaltyEngine::SFML::Image>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUIBackground")); //GUIBackground
//
//	guiBehind->transform.position.x = size.x / 2;
//	guiBehind->transform.position.y = size.y - 75 / 2;
//	*scene << guiBehind;

	SaltyEngine::GameObject *guiGameBeam = new SaltyEngine::GameObject("GUIBeam");

	guiGameBeam->AddComponent<GameGUIBeam>();

//	guiGameBeam->transform.position.x = size.x / 2;
	guiGameBeam->transform.SetPosition(SaltyEngine::Vector2(size.x / 2, guiGameBeam->transform.GetPosition().y));

	SaltyEngine::SFML::SpriteRenderer *sprr = guiGameBeam->GetComponent<SaltyEngine::SFML::SpriteRenderer>();
//	guiGameBeam->transform.position.y = size.y - ((sprr) ? (sprr->GetSprite()->GetRect()->_height / 2) : 0);
	guiGameBeam->transform.SetPosition(guiGameBeam->transform.GetPosition().x, size.y - ((sprr) ? (sprr->GetSprite()->GetRect()->_height / 2) : 0));
	*scene << guiGameBeam;

//	SaltyEngine::GameObject *guiGameHighscore = new SaltyEngine::GameObject("GUIHighscore");
//
//	guiGameHighscore->AddComponent<GameGUIHighscore>();
//
//	guiGameHighscore->transform.position.x = size.x - 60;
//	guiGameHighscore->transform.position.y = size.y / 2 - 19;
//	*scene << guiGameHighscore;

}

int main(int, char **)
{

#if _WIN32
	Network::Socket::WinSocket::Start();
#endif

	unsigned int x = 960;
	unsigned int y = 540;
	SaltyEngine::SFML::Renderer *renderer = new SaltyEngine::SFML::Renderer(sf::VideoMode(x * 2, y * 2), "R-Type Launcher");
	SaltyEngine::SFML::EventManager *event_manager = new SaltyEngine::SFML::EventManager(renderer->GetRenderWindow());
	SaltyEngine::SFML::PhysicsHandler *ph = new SaltyEngine::SFML::PhysicsHandler(x, y, false);
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

//	SaltyEngine::GameObject *guiBehind = new SaltyEngine::GameObject("GUIBackgroundGame");
//	guiBehind->AddComponent<SaltyEngine::SFML::Image>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUIBackground")); //GUIBackground
//
//	guiBehind->transform.position.x = pos.x / 2;
//	guiBehind->transform.position.y = pos.y - 75 / 2;
//	*scene << guiBehind;

	server.reset(new SaltyEngine::GameObject("Rtype", SaltyEngine::Layer::Tag::Destroy));
	SaltyEngine::SceneDefault *sceneDefault = SaltyEngine::SFML::AssetManager::Instance().LoadScene("scene2");

	scene->SetScale(sceneDefault->scale);

	CreateGUIGame(renderer->GetRealSize(), scene);

	server->AddComponent<Rtype::Game::Client::GameClientObject>("127.0.0.1", 4242);
	server->AddComponent<GameManager>();
//    std::unique_ptr<SaltyEngine::GameObject> box_right = std::unique_ptr<SaltyEngine::GameObject>(new SaltyEngine::GameObject("box right"));
//    std::unique_ptr<SaltyEngine::GameObject> box_left = std::unique_ptr<SaltyEngine::GameObject>(new SaltyEngine::GameObject("box left"));
//    std::unique_ptr<SaltyEngine::GameObject> box_top = std::unique_ptr<SaltyEngine::GameObject>(new SaltyEngine::GameObject("box top"));
//    std::unique_ptr<SaltyEngine::GameObject> box_down = std::unique_ptr<SaltyEngine::GameObject>(new SaltyEngine::GameObject("box down"));
//	box_right->AddComponent<SaltyEngine::SFML::BoxCollider2D>(
//			sf::Vector2u(1, y)
//	);
//	box_right->transform.SetPosition(SaltyEngine::Vector2(x -1, y / 2));
//
//    box_left->AddComponent<SaltyEngine::SFML::BoxCollider2D>(
//            sf::Vector2u(1, y)
//    );
//    box_left->transform.SetPosition(SaltyEngine::Vector2(0, y / 2));
//
//    box_top->AddComponent<SaltyEngine::SFML::BoxCollider2D>(
//            sf::Vector2u(x, 1)
//    );
//    box_top->transform.SetPosition(SaltyEngine::Vector2(x / 2, 0));
//
//    box_down->AddComponent<SaltyEngine::SFML::BoxCollider2D>(
//            sf::Vector2u(x, 1)
//    );
//    box_down->transform.SetPosition(SaltyEngine::Vector2(x / 2, y -1));
//
//    *scene << box_right.get();
//    *scene << box_left.get();
//    *scene << box_down.get();
//    *scene << box_top.get();
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