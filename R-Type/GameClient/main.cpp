#include <Rtype/Game/Client/GameManager.hpp>
#include <Rtype/Game/Client/SpaceShipController.hpp>
#include <Rtype/Game/Client/GameGUIBeam.hpp>
#include <Rtype/Game/Client/GameGUIHighscore.hpp>
#include <Rtype/Game/Client/EndScreen.hpp>
#include <Common/Flags.hpp>
#include <SaltyEngine/SFML/SFMLSceneLoader.hpp>
#include "SaltyEngine/SFML.hpp"

void CreateGUIGame(SaltyEngine::Vector2i const &size, SaltyEngine::SFML::Scene *scene) {

	SaltyEngine::GameObject     *guiGameBeam = new SaltyEngine::GameObject("GUIBeam");
	guiGameBeam->AddComponent<GameGUIBeam>();
	guiGameBeam->transform.SetPosition(SaltyEngine::Vector2(size.x / 2, guiGameBeam->transform.GetPosition().y));

	SaltyEngine::SFML::SpriteRenderer *sprr = guiGameBeam->GetComponent<SaltyEngine::SFML::SpriteRenderer>();
	guiGameBeam->transform.SetPosition(guiGameBeam->transform.GetPosition().x, size.y - ((sprr) ? (sprr->GetSprite()->GetRect()->_height / 2) : 0));
	*scene << guiGameBeam;

	SaltyEngine::GameObject     *guiGameHighscore = new SaltyEngine::GameObject("GUIHighscore");
	guiGameHighscore->AddComponent<GameGUIHighscore>();
	guiGameHighscore->transform.SetPosition(static_cast<float>(size.x / 1.2), guiGameBeam->transform.GetPosition().y);
	*scene << guiGameHighscore;

	SaltyEngine::GameObject     *victoryScreen = new SaltyEngine::GameObject("EndScreen");
	victoryScreen->AddComponent<EndScreen>();
	victoryScreen->transform.SetPosition(size.x / 2, static_cast<float>(size.y / 2.3));
	*scene << victoryScreen;

//    SaltyEngine::GameObject     *buttonEnd = new SaltyEngine::GameObject("EndScreen");
    victoryScreen->AddComponent<EndScreen>();
    victoryScreen->transform.SetPosition(size.x / 2, static_cast<float>(size.y / 2.3));
    *scene << victoryScreen;
}

void CallCharabia(const std::string &map,
				  SaltyEngine::SFML::Scene *scene,
				  SaltyEngine::SFML::Renderer *renderer,
				  std::string	ip,
				  uint16_t port,
				  uint32_t secret)
{
	std::unique_ptr<SaltyEngine::GameObject> server;
	//
	SaltyEngine::SceneDefault *sceneDefault = SaltyEngine::SFML::AssetManager::Instance().LoadScene(map);
	if (sceneDefault == nullptr)
	{
		Debug::PrintError("Cannot open scene [" + map + "]");
		return;
	}
//
	scene->SetScale(sceneDefault->scale);
	//	SaltyEngine::GameObject *guiBehind = new SaltyEngine::GameObject("GUIBackgroundGame");
//	guiBehind->AddComponent<SaltyEngine::SFML::Image>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUIBackground")); //GUIBackground
//
//	guiBehind->transform.position.x = pos.x / 2;
//	guiBehind->transform.position.y = pos.y - 75 / 2;
//	*scene << guiBehind;
//
	server.reset(new SaltyEngine::GameObject("Rtype", SaltyEngine::Layer::Tag::Destroy));
//
	CreateGUIGame(renderer->GetRealSize(), scene);
//
	server->AddComponent<Rtype::Game::Client::GameClientObject>(ip, port, secret);
	server->AddComponent<GameManager>();

	*scene << server.get();

	SaltyEngine::Engine::Instance().Run();
}

void StartGame(int ac, char **av, const std::string &map)
{
	SaltyEngine::SFML::Scene *scene = new SaltyEngine::SFML::Scene();
	SaltyEngine::SFML::Scene *scene2 = new SaltyEngine::SFML::Scene();
    SaltyEngine::SFML::Scene *scene3 = new SaltyEngine::SFML::Scene();

    scene->SetName("sceneConnection");
    scene3->SetName("scene2");
    scene2->SetName("sceneRoom");

    SaltyEngine::Engine::Instance().SetArguments(ac, (const char**)av);
	SaltyEngine::Engine::Instance() << scene;
	SaltyEngine::Engine::Instance() << scene2;
    SaltyEngine::Engine::Instance() << scene3;

	SaltyEngine::SceneDefault *sceneDefault = SaltyEngine::SFML::AssetManager::Instance().LoadSize(map);

    unsigned int x = (unsigned int) sceneDefault->size.x; // 1920
    unsigned int y = (unsigned int) sceneDefault->size.y; // 1080
    SaltyEngine::SFML::Renderer *renderer = new SaltyEngine::SFML::Renderer(sf::VideoMode(x * 2, y * 2), "R-Type Launcher");
    SaltyEngine::SFML::EventManager *event_manager = new SaltyEngine::SFML::EventManager(renderer);
    SaltyEngine::SFML::PhysicsHandler *ph = new SaltyEngine::SFML::PhysicsHandler(x, y, false);
    SaltyEngine::Engine::Instance().SetPhysicsHandler(ph);
    // Set Renderer and EventManager
    Singleton<SaltyEngine::Engine>::Instance().SetRenderer(renderer);
    Singleton<SaltyEngine::Engine>::Instance().SetEventManager(event_manager);

//	SaltyEngine::Engine::Instance().SetFrameRate(30);

    // Create Scene
	sceneDefault = SaltyEngine::SFML::AssetManager::Instance().LoadScene(map);
	scene->SetScale(sceneDefault->scale);
	for (std::list<std::pair<std::string, SaltyEngine::Vector2f> >::const_iterator it = sceneDefault->objects.begin(); it != sceneDefault->objects.end(); ++it) {
		if (it->first == "GameManager") {
			SaltyEngine::Vector2f pos = it->second;
			SaltyEngine::Instantiate(it->first, pos, 0);
		}
	}
	SaltyEngine::Engine::Instance().SetSceneLoader(new SaltyEngine::SFML::SFMLSceneLoader());
	SaltyEngine::Engine::Instance().Run();
}

int main(int ac, char **av)
{
	Flags   flags;
	std::string	ip;
	uint16_t port;
	std::string map;
	uint32_t secret;
	bool help;

	flags.Var(ip, 'h', "host", std::string("127.0.0.1"), "The host to which connect", "Game host");
	flags.Var(port, 'p', "port", uint16_t(4242), "The port to which connect", "Game port");
	flags.Var(map, 'l', "level", std::string("sceneConnection"), "The level of the game server", "Game level");
	flags.Var(secret, 's', "secret", uint32_t(0), "The secret code of the game server", "Game secret");

	flags.Bool(help, 'i', "info", "Show this help message", "Info");

	if (!flags.Parse(ac, av))
		return 1;
	else if (help)
	{
		flags.PrintHelp(av[0]);
		return 1;
	}

#if _WIN32
	Network::Socket::WinSocket::Start();
#endif



	//COMMENT THIS LINE
	StartGame(ac, av, map);

	//UNCOMMENT THIS LINE TO GET OLD CLIENT
//	CallCharabia(map, scene, renderer, ip, port, secret);

#if _WIN32
	Network::Socket::WinSocket::Stop();
#endif
	return (0);
}