#include <SaltyEngine/Constants.hpp>
#include "Prefabs/Missile/Laser/Laser.hpp"
#include "Prefabs/Missile/Laser/LaserController.hpp"

Laser::Laser() : GameObject("Laser", SaltyEngine::Layer::Tag::BulletPlayer) {
	AddComponent<LaserController>();
}

Laser::~Laser() {
}

LASER_API SaltyEngine::Object const*GetObjectPrefab()
{
	return new Laser();
}
