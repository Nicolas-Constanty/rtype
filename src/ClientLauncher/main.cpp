#include "SaltyEngine/SaltyEngine.hpp"
#include "Common/Singleton.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "SaltyEngine/PlayerController.hpp"
#include "SaltyEngine/Input.hpp"

#define GAME2D

int main()
{
	// Create Scene
	SaltyEngine::Scene *scene(new SaltyEngine::Scene());
	

	// Push scene int SaltyEngine
	Singleton<SaltyEngine::SaltyEngine>::Instance() << scene;

	// Run the SaltyEngine with default Scene 0
	Singleton<SaltyEngine::SaltyEngine>::Instance().Run();
	return 0;
}