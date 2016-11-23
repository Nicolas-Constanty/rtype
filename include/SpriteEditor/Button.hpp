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
		Button(const sf::Texture &texture);
		Button(const sf::Texture &texture, const sf::Texture &over);
		~Button() {};

	public:
		void SetPosition(sf::Vector2f vector);
		sf::Sprite operator()();
		void OnMouseOver(const sf::Event &event);
		virtual void OnClic(const sf::Event &event);
		sf::FloatRect GetRect() const;

	protected:
		sf::Sprite m_sprite;
		const sf::Texture &m_base;
		const sf::Texture &m_over;
		bool m_isover;
	};
}

#endif // !BUTTON_HPP_

