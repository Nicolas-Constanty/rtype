#include "SaltyEngine/SaltyEngine.hpp"
#include "Common/Singleton.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "Player/PlayerController.hpp"
#include "SaltyEngine/Input.hpp"
#include "SaltyEngine/SFML/Scene.hpp"

#define GAME2D

int main()
{
	Singleton<SaltyEngine::SaltyEngine>::Instance();
	
	// Create Scene
	SaltyEngine::SFML::Scene *scene = new SaltyEngine::SFML::Scene();

	SaltyEngine::GameObject *player = new SaltyEngine::GameObject("Player");

	SaltyEngine::GameObject *monster = (SaltyEngine::GameObject*)SaltyEngine::Instantiate("Monster");
	// Add script to the player
	player->AddComponent<SaltyEngine::PlayerController>();
	std::cout << "Monster scripts -> " << monster->GetSaltyBehaviour().size() << std::endl;
	//monster->AddComponent<MonsterController>();
	//player->AddComponent<MonsterController>();

	// Push player in scene
	*scene << player;
	*scene << monster;

	// Push scene int SaltyEngine
	Singleton<SaltyEngine::SaltyEngine>::Instance() << scene;

	//std::cout << "Instance -> " << SaltyEngine::Instantiate("Monster") << std::endl;
	std::cout << "toto" << std::endl;
	// Run the SaltyEngine with default Scene 0
	Singleton<SaltyEngine::SaltyEngine>::Instance().Run();
	return 0;
}