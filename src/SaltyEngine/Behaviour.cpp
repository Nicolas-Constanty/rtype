#include "SaltyEngine/Behaviour.hpp"

namespace SaltyEngine
{
	Behaviour::Behaviour(GameObject * const gameObj) : Component("Behaviour", gameObj) {};
	Behaviour::Behaviour(const std::string name, GameObject* const gameObj) : Component(name, gameObj) {};
}