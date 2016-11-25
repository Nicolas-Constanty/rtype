#include "SaltyEngine/SaltyEngine.hpp"
#include "Common/DllLoader.hpp"

#define GAME2D

int main()
{
	DllLoader *loader = new DllLoader();
	std::cout << loader->Load("MonsterTest.dll") << std::endl;
	std::cout << loader->Unload() << std::endl;
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