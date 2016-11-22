#include "SaltyEngine/Behaviour.hpp"

namespace SaltyEngine
{
	Behaviour::Behaviour(GameObject * const gameObj) : Component("Behaviour", gameObj), enabled(true) {};
	Behaviour::Behaviour(const std::string name, GameObject* const gameObj) : Component(name, gameObj), enabled(true) {};
}
