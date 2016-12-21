#pragma once

#ifndef UIBEHAVIOUR_HPP_
#define UIBEHAVIOUR_HPP_

#include "SaltyEngine/SaltyBehaviour.hpp"
#include "SaltyEngine/GameObject.hpp"

namespace SaltyEngine
{
	namespace GUI
	{
		class UIBehaviour : public SaltyBehaviour
		{
		public:
			UIBehaviour(GameObject * const gameObj);
			UIBehaviour(const std::string & name, GameObject * const gameObj);
			virtual ~UIBehaviour() {};
			bool IsActive() const;

		public:
			virtual Component *CloneComponent(GameObject* const obj) {
				return new UIBehaviour(obj);
			}

			void OnGui() override;
		};
	}
}

#endif // !UIBEHAVIOUR_HPP_
