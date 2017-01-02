#include <Rtype/Game/Client/GameManager.hpp>
#include <Rtype/Game/Client/SpaceShipController.hpp>
#include <Rtype/Game/Client/GameGUIBeam.hpp>
#include <Rtype/Game/Client/GameGUIHighscore.hpp>
#include <Rtype/Game/Client/EndScreen.hpp>
#include <Common/Flags.hpp>
#include <SaltyEngine/SFML/SFMLSceneLoader.hpp>
#include "SaltyEngine/SFML.hpp"

void StartGame(int ac, char **av, const std::string &map)
{
	SaltyEngine::Engine::Instance().SetArguments(ac, (const char**)av);
	SaltyEngine::Engine::Instance().SetSceneLoader(new SaltyEngine::SFML::SFMLSceneLoader());
    SaltyEngine::Engine::Instance().LoadScene(map);
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