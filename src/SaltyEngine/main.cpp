#include "SaltyEngine/SaltyEngine.hpp"

#define GAME2D

int main()
{
	// Create Scene
	SaltyEngine::Scene *scene(new SaltyEngine::Scene());
	// Create player
	SaltyEngine::GameObject *player = new SaltyEngine::GameObject("Player");

	std::shared_ptr<SaltyEngine::Object> go = SaltyEngine::Object::Instantiate("DefaultMonster");

	std::cout << go->GetName() << std::endl;

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