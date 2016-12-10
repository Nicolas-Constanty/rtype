#include <Prefabs/Missile/Laser/LaserController.hpp>
#include "Prefabs/Missile/MissileMedusa/MissileMedusa.hpp"
#include "Prefabs/Missile/MissileController.hpp"

MissileMedusa::MissileMedusa() : GameObject("MissileMedusa")
{
	AddComponent<MissileController>();
}


MissileMedusa::~MissileMedusa()
{
}

MISSILEMEDUSA_API SaltyEngine::Object const*GetObjectPrefab()
{
	return new MissileMedusa();
}
