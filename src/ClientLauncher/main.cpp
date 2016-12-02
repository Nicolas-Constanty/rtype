#include "SaltyEngine/SaltyEngine.hpp"
#include "Common/Singleton.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "ClientLauncher/PlayerController.hpp"
#include "SaltyEngine/Input.hpp"
#include "SaltyEngine/SFML/Scene.hpp"
#include "ClientLauncher/RtypeFactory.hpp"
#include "Monster/Monster.hpp"

#define GAME2D

const std::vector<std::string> RtypeFactory<Monster>::names = {
	"Monster"
};

int main()
{

	Singleton<SaltyEngine::SaltyEngine>::Instance();
	RtypeFactory<Monster>	factory;
	// Create Scene
	SaltyEngine::SFML::Scene *scene = new SaltyEngine::SFML::Scene();

	SaltyEngine::GameObject *monster = factory.create("Monster");
	SaltyEngine::GameObject *monster2 = factory.create("Monster");

	std::cout << "Fact: " << monster << std::endl;
	std::cout << "Fact: " << monster2 << std::endl;

	//SaltyEngine::GameObject *monster = (SaltyEngine::GameObject*)SaltyEngine::Instantiate("Monster");
	// Add script to the player
	
	//std::cout << "Monster scripts -> " << monster->GetSaltyBehaviour().size() << std::endl;
	//monster->AddComponent<MonsterController>();
	//player->AddComponent<MonsterController>();

	// Push player in scene
	*scene << monster;
	*scene << monster2;
	//*scene << monster;

	// Push scene int SaltyEngine
	Singleton<SaltyEngine::SaltyEngine>::Instance() << scene;

	//std::cout << "Instance -> " << SaltyEngine::Instantiate("Monster") << std::endl;
	std::cout << "toto" << std::endl;
	// Run the SaltyEngine with default Scene 0
	


	Singleton<SaltyEngine::SaltyEngine>::Instance().Run();

	return 0;
}