#include "SpriteEditor/Button.hpp"

namespace SpriteEditor
{
	Button::Button(const sf::Texture &texture) : m_base(texture), m_over(texture)
	{
		m_isover = false;
		m_sprite.setTexture(m_base);
	}

	Button::Button(const sf::Texture & texture, const sf::Texture & over) : m_base(texture), m_over(over)
	{
		m_isover = false;
		m_sprite.setTexture(m_base);
	}

	void Button::SetPosition(sf::Vector2f vector)
	{
		m_sprite.setPosition(vector);
	}

	sf::Sprite Button::operator()()
	{
		return m_sprite;
	}

	void Button::OnMouseOver(const sf::Event &ev)
	{
		sf::FloatRect rect = m_sprite.getGlobalBounds();
		if (!m_isover && ev.mouseMove.x > rect.left && ev.mouseMove.y > rect.top &&
			ev.mouseMove.x < rect.left + rect.width && ev.mouseMove.y < rect.top + rect.height)
		{
			m_sprite.setTexture(m_over);
			m_isover = true;
		}
		else if (m_isover && ev.mouseMove.x < rect.left || ev.mouseMove.y < rect.top ||
			ev.mouseMove.x > rect.left + rect.width || ev.mouseMove.y > rect.top + rect.height)
		{
			m_sprite.setTexture(m_base);
			m_isover = false;
		}
	}

	void Button::OnClic(const sf::Event & event)
	{
		
	}

	sf::FloatRect Button::GetRect(void) const
	{
		return (m_sprite.getGlobalBounds());
	}
}