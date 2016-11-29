#include "Common/LibLoader.hpp"
#include "SaltyEngine/SaltyEngine.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "ClientLauncher/PlayerController.hpp"
#ifdef _WIN32
#include "Common/DllLoader.hpp"
#endif
#include "SaltyEngine/Input.hpp"

#define GAME2D

int main()
{
	/**
	 * Starts the engine
	 */
	Singleton<SaltyEngine::SaltyEngine>::Instance();

    // Create Scene
	SaltyEngine::Scene *scene(new SaltyEngine::Scene());
	// Create player
	SaltyEngine::GameObject *player = new SaltyEngine::GameObject("Player");

	std::shared_ptr<SaltyEngine::Object> gu = SaltyEngine::Instantiate("Monster");

	if (gu.get() != nullptr)
		std::cout << gu->GetName() << std::endl;

	std::cout << "Size = " << SaltyEngine::Object::FindObjectsOfType<SaltyEngine::GameObject>().size() << std::endl;

	// Add script to the player
	player->AddComponent<SaltyEngine::PlayerController>();
	
	// Push player in scene
	*scene << player;
	*scene << (SaltyEngine::GameObject *)gu.get();

	// Push scene int SaltyEngine
	Singleton<SaltyEngine::SaltyEngine>::Instance() << scene;

	// Run the SaltyEngine with default Scene 0
	Singleton<SaltyEngine::SaltyEngine>::Instance().Run();
	return 0;
}