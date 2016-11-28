#pragma once

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include "SaltyEngine/GUI/Selectable.hpp"
#include "SaltyEngine/GUI/Event.hpp"

namespace SaltyEngine
{
	namespace GUI
	{
		class Button : public Selectable
		{
		public:
			explicit Button(GameObject* gameObj)
				: Selectable("Button", gameObj)
			{
				//gameObject->AddComponent<>()
			}

			Button(const std::string& name, GameObject* gameObj)
				: Selectable(name, gameObj)
			{
			}

			virtual ~Button() {};

		public:
			virtual void OnPointerClick(); //	Registered IPointerClickHandler callback.
			virtual void OnSubmit(); //

		public:
			Event onClick;
		};
	}
}

#endif // !BUTTON_HPP_