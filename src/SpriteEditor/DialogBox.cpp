#include "SpriteEditor/DialogBox.hpp"
#define ASSET_DIRECTORY "../../../Assets/"

namespace SpriteEditor
{
	DialogBox::DialogBox(const sf::String &title)
		: m_title_str(title), sf::RenderWindow(sf::VideoMode(500, 200), title),
		m_entry(sf::Vector2f(300, 40))
	{
		close();
		m_entry.setPosition(100, 70);
		m_entry.setOutlineThickness(2);
		m_entry.setOutlineColor(sf::Color::Red);
		if (!m_font.loadFromFile(ASSET_DIRECTORY "Fonts/arial.ttf"))
			std::cerr << "Invalid font" << std::endl;
		m_cursor.setFont(m_font);
		m_cursor.setString("|");
		m_cursor.setCharacterSize(28);
		m_cursor.setColor(sf::Color(150, 150, 150, 255));
		m_cursor.setPosition(102, 70);
		m_text.setFont(m_font);
		m_text.setColor(sf::Color(150, 150, 150, 255));
		m_text.setPosition(102, 70);
		m_max_size = 0;
		m_title.setFont(m_font);
		m_title.setColor(sf::Color(150, 150, 150, 255));
		m_title.setString(m_title_str);
		m_title.setPosition(500 / 2 - (m_title.getGlobalBounds().width / 2), 20);
	}

	DialogBox::~DialogBox()
	{
	}
	void DialogBox::Open()
	{
		create();
	}

	std::string DialogBox::OnValidate()
	{
		return (m_field + ".prefab");
	}

	void DialogBox::OnWrite(const sf::Event &ev)
	{
		if (ev.key.code < 128)
		{
			std::cout << ev.key.code << std::endl;
			if (ev.key.code == 8 && m_field.size())
			{
				m_field = m_field.substr(0, m_field.size() - 1);
				m_aff = m_aff.substr(0, m_aff.size() - 1);
				m_text.setString(m_field);
				while (m_text.getLocalBounds().width > 296)
				{
					if (m_field.size() > m_max_size)
						m_aff = m_field.substr(m_field.size() - m_max_size);
					m_text.setString(m_aff);
					m_max_size = m_aff.size();
				}
			}
			else if (ev.key.code != 8)
			{
				m_field += static_cast<char>(ev.key.code);
				m_aff += static_cast<char>(ev.key.code);
				m_text.setString(m_aff);
				while (m_text.getLocalBounds().width > 296)
				{
					m_aff = m_aff.substr(1, m_aff.size());
					m_max_size = m_aff.size();
					m_text.setString(m_aff);
				}
			}
			m_text.setString(m_aff);
			m_cursor.setPosition(102 + m_text.getGlobalBounds().width, m_cursor.getPosition().y);
			std::cout << m_field << std::endl;
			std::cout << m_aff << std::endl;
		}
	}
	void DialogBox::display()
	{
		if (m_clock.getElapsedTime().asSeconds() > 0.5f)
		{
			m_clock.restart();
			m_clignot = !m_clignot;
		}
		clear(sf::Color(50, 50, 50, 255));
		draw(m_entry);
		if (m_clignot)
			draw(m_cursor);
		draw(m_text);
		draw(m_title);
		sf::Window::display();
	}
	void DialogBox::create()
	{
		m_clock.restart();
		sf::Window::create(sf::VideoMode(500, 200), m_title_str);
	}
}
