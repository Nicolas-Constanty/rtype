#include "Common/LibLoader.hpp"
#include "SaltyEngine/SaltyEngine.hpp"
#include "Common/Singleton.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "SaltyEngine/PlayerController.hpp"
#include "Common/DllLoader.hpp"
#include "SaltyEngine/Input.hpp"

#define GAME2D

int main()
{
#ifdef _WIN32
	DllLoader *loader = new DllLoader();
    std::cout << loader->Load("MonsterTest.dll") << std::endl;
	std::cout << loader->Unload() << std::endl;
#else
    LibLoader *loader = new LibLoader();
    std::cout << "Loading monster: " << loader->Load("./monster.so") << std::endl;
    std::cout << loader->Call(std::string("GetObject")) << std::endl;
    std::cout << loader->Unload() << std::endl;
#endif

	// Create Scene
	SaltyEngine::Scene *scene(new SaltyEngine::Scene());
	// Create player
	SaltyEngine::GameObject *player = new SaltyEngine::GameObject("Player");

	std::shared_ptr<SaltyEngine::Object> go = SaltyEngine::Instantiate("DefaultMonster");
	SaltyEngine::Instantiate("Mutant");
	SaltyEngine::Instantiate("Script");

	std::cout << go->GetName() << std::endl;

	std::cout << "Size = " << SaltyEngine::Object::FindObjectsOfType<SaltyEngine::GameObject>().size() << std::endl;

	// Add script to player
	player->AddComponent<SaltyEngine::PlayerController>();
	
	// Push player in scene
	*scene << player;

	// Push scene int SaltyEngine
	Singleton<SaltyEngine::SaltyEngine>::Instance() << scene;

	// Run the SaltyEngine with default Scene 0
	Singleton<SaltyEngine::SaltyEngine>::Instance().Run();
	return 0;
}