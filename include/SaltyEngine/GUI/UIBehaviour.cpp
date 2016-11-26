#include "UIBehaviour.hpp"

namespace SaltyEngine
{
	namespace GUI
	{
		UIBehaviour::UIBehaviour(GameObject * const gameObj) : SaltyBehaviour("SaltyBehaviour", gameObj) {};

		UIBehaviour::UIBehaviour(const std::string & name, GameObject * const gameObj) : SaltyBehaviour(name, gameObj) {};

		bool UIBehaviour::IsActive() const
		{
			return (gameObject->GetActiveSelf());
		}
	}
}