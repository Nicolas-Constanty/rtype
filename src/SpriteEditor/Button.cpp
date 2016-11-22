#include "SpriteEditor/Button.hpp"

namespace SpriteEditor
{
	Button::Button(sf::Sprite sprite)
	{
		m_sprite = sprite;
	}
	Button::Button(sf::Texture texture)
	{
		m_sprite.setTexture(texture);
	}
	void Button::SetPosition(sf::Vector2f vector)
	{
		m_sprite.setPosition(vector);
	}
	sf::Sprite Button::operator()()
	{
		return m_sprite;
	}
}