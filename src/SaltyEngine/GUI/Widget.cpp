#include "SaltyEngine/GUI/Widget.hpp"

namespace SaltyEngine
{
	namespace GUI
	{
		Widget::Widget(const std::string & name, GameObject * const gameObj) : Component(name, gameObj)  {}
		Widget::Widget(GameObject* const gameObj) : Component("Widget", gameObj) {}

		Widget::~Widget() {}
	}
}