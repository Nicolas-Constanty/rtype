#pragma once

#ifndef SELECTABLE_HPP_
#define SELECTABLE_HPP_

#include <list>
#include "SaltyEngine/GUI/IDeselectHandler.hpp"
#include "SaltyEngine/GUI/IMoveHandler.hpp"
#include "SaltyEngine/GUI/IPointerDownHandler.hpp"
#include "SaltyEngine/GUI/IPointerEnterHandler.hpp"
#include "SaltyEngine/GUI/IPointerExitHandler.hpp"
#include "SaltyEngine/GUI/IPointerUpHandler.hpp"
#include "SaltyEngine/GUI/ISelectHandler.hpp"
#include "SaltyEngine/GUI/UIBehaviour.hpp"
#include "Common/Debug.hpp"

namespace SaltyEngine
{
	namespace GUI
	{
		class LIB_EXPORT Selectable : public UIBehaviour, public IDeselectHandler, public IMoveHandler, public IPointerDownHandler,
			public IPointerEnterHandler, public IPointerExitHandler, public IPointerUpHandler, public ISelectHandler
		{
		public:
			explicit Selectable(GameObject* gameObj)
				: UIBehaviour("Selectable", gameObj), interactable(true)
			{
			}

			Selectable(const std::string& name, GameObject* gameObj)
				: UIBehaviour(name, gameObj), interactable(true)
			{
			}

			virtual ~Selectable() {};
			void OnSelect() override { Debug::PrintInfo("OnSelect called"); };
			void OnDeselect() override { Debug::PrintInfo("OnDeselect called"); };
			void OnMove() override { Debug::PrintInfo("OnMove called"); };
			void OnPointerUp() override { Debug::PrintInfo("OnPointerUp called"); };
			void OnPointerDown() override { Debug::PrintInfo("OnPointerDown called"); };
			void OnPointerEnter() override { Debug::PrintInfo("OnPointerEnter called"); };
			void OnPointerExit() override { Debug::PrintInfo("OnPointerExit called"); };
			void Select() {};
		public:
			static std::list<Selectable> allSelectable;
			bool interactable;

		public:
			virtual Component *CloneComponent(GameObject* const obj) {
				return new Selectable(obj);
			}
		};
	}
}

#endif // !SELECTABLE_HPP_
