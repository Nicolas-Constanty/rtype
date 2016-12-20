#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>

namespace SpriteEditor
{
	class SelectRect : public sf::Drawable, public sf::Transformable
	{
	public:
		explicit SelectRect(sf::FloatRect rect);
		void SetColor(const sf::Color & color);
		bool IsOver(const sf::Event & ev) const;
		void Update(const sf::Event &ev);
		void OnClic(const sf::Event &ev);
		std::string GetExport();

	private:

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override
		{
			states.transform *= getTransform();
			states.texture = &m_texture;
			target.draw(m_vertices, states);
		}
		bool m_enable;
		sf::VertexArray m_vertices;
		sf::Texture m_texture;
		sf::Vector2f m_start_point;
		sf::Vector2f m_end_point;
		sf::FloatRect m_select_area;
	};
}