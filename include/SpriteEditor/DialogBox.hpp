#pragma once

#ifndef DIALOGBOX_HPP_
#define DIALOGBOX_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

namespace SpriteEditor
{
	class DialogBox : public sf::RenderWindow
	{
	public:
		DialogBox(const sf::String &title);
		~DialogBox();

		void Open();
		std::string OnValidate();
		void OnWrite(const sf::Event & ev);
		virtual void display();
		virtual void create();
	private:
		const sf::String &m_title_str;
		sf::Text m_title;
		sf::RectangleShape m_entry;
		sf::Font m_font;
		sf::Text m_cursor;
		sf::Text m_text;
		std::string m_aff;
		sf::Clock m_clock;
		sf::Time m_elapsed;
		std::string m_field;
		size_t m_max_size;
		bool m_clignot;
	};
}

#endif // !DIALOGBOX_HPP_
