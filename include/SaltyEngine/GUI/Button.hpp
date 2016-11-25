#pragma once

#ifndef IBUTTONHANDLER_HPP_
#define IBUTTONHANDLER_HPP_

#include "SaltyEngine/GUI/Selectable.hpp"
#include "SaltyEngine/GUI/Event.hpp"

namespace SaltyEngine
{
	namespace GUI
	{
		class Button : public Selectable
		{
		public:
			virtual ~Button() {};

		public:
			void OnPointerClick(); //	Registered IPointerClickHandler callback.
			void OnSubmit(); //

		public:
			Event onClick;
		};
	}
}

#endif // !IBUTTONHANDLER_HPP_
