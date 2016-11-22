#pragma once

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <SFML/Graphics.hpp>

#include <iostream>

namespace SpriteEditor
{
	class Button
	{
	public:
		Button(const std::string name);
		Button(sf::Sprite sprite);
		Button(sf::Texture texture);
		~Button() {};

	public:
		void SetPosition(sf::Vector2f vector);
		sf::Sprite operator()();
	private:
		sf::Sprite m_sprite;
		
	};
}

#endif // !BUTTON_HPP_

