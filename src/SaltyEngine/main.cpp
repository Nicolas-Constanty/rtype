#include "SaltyEngine/SaltyReflection.hpp"
#include "SaltyEngine/SaltyGame.hpp"
#include "Common/Singleton.hpp"

#define GAME2D
using namespace SaltyEngine;

int main()
{
	AA *aa = new AA();
	Scene *scene(new Scene());

	// Add SaltyBehavior Object to scene
	*scene << aa;

	// Add Scene Object to SaltyGame
	Singleton<SaltyGame>::Instance() << scene;

	// Run the SaltyGame with default Scene 0
	Singleton<SaltyGame>::Instance().Run();
	return 0;
}