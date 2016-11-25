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
#include "SaltyEngine/Debug.hpp"

namespace SaltyEngine
{
	namespace GUI
	{
		class Selectable : public UIBehaviour, public IDeselectHandler, public IMoveHandler, public IPointerDownHandler,
			public IPointerEnterHandler, public IPointerExitHandler, public IPointerUpHandler, public ISelectHandler
		{
		public:
			virtual ~Selectable() {};
			virtual void OnSelect() { Debug::PrintInfo("OnSelect called"); };
			virtual void OnDeselect() { Debug::PrintInfo("OnDeselect called"); };
			virtual void OnMove() { Debug::PrintInfo("OnMove called"); };
			virtual void OnPointerUp() { Debug::PrintInfo("OnPointerUp called"); };
			virtual void OnPointerDown() { Debug::PrintInfo("OnPointerDown called"); };
			virtual void OnPointerEnter() { Debug::PrintInfo("OnPointerEnter called"); };
			virtual void OnPointerExit() { Debug::PrintInfo("OnPointerExit called"); };
			void Select() {};
		public:
			static std::list<Selectable> allSelectable;
			bool interactable;
		};
	}
}

#endif // !SELECTABLE_HPP_
