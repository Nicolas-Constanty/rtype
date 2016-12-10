#include "Prefabs/Missile/Laser/Laser.hpp"
#include "Prefabs/Missile/Laser/LaserController.hpp"

Laser::Laser() : GameObject("Laser") {
	AddComponent<LaserController>();
}

Laser::~Laser() {
}

LASER_API SaltyEngine::Object const*GetObjectPrefab()
{
	return new Laser();
}
