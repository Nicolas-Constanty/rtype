#pragma once

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <SFML/Graphics.hpp>
#include "SaltyEngine/IWindow.hpp"

namespace SaltyEngine
{
	namespace SFML
	{
		class Window : public IWindow, public sf::RenderWindow
		{
		public:
			Window(const sf::VideoMode &vm, const std::string &name)
				: sf::RenderWindow(vm, name) {}
			virtual ~Window() {}

		public:
			bool IsOpen() const override
			{
				return (isOpen());
			}
		};
	}
}

#endif //!RECT_HPP_