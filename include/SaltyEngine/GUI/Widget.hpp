#pragma once

#ifndef WIDGET_HPP_
#define WIDGET_HPP_

#include "SaltyEngine/Component.hpp"

namespace SaltyEngine
{
	namespace GUI
	{
		class Widget : public Component
		{
			enum class State {
				NORMAL = 0,
				ACTIVE,
				OVER,
				DISABLE,
			};
		public:
			Widget(const std::string &name, GameObject* const gameObj);
			Widget(GameObject* const gameObj);

			~Widget();

		private:

		};
	}
}

#endif // !WIDGET_HPP_
