#include "SpriteEditor/SelectRect.hpp"
#include <iostream>

namespace SpriteEditor
{
	SelectRect::SelectRect(sf::FloatRect rect)
	{
		m_enable = false;
		m_vertices.setPrimitiveType(sf::LinesStrip);
		m_vertices.resize(5);
		m_select_area = rect;
		SetColor(sf::Color::Red);
	}

	void SelectRect::SetColor(const sf::Color &color)
	{
		m_vertices[0].color = color;
		m_vertices[1].color = color;
		m_vertices[2].color = color;
		m_vertices[3].color = color;
		m_vertices[4].color = color;
	}

	bool SelectRect::IsOver(const sf::Event &ev) const
	{
		return (ev.mouseButton.x > m_select_area.left && ev.mouseButton.y > m_select_area.top &&
			ev.mouseButton.x < m_select_area.left + m_select_area.width && ev.mouseButton.y < m_select_area.top + m_select_area.height);
	}

	void SelectRect::OnClic(const sf::Event & ev)
	{
		if (IsOver(ev))
		{
			if (!m_enable)
			{
				m_enable = true;
				m_start_point = sf::Vector2f(static_cast<float>(ev.mouseButton.x),
					static_cast<float>(ev.mouseButton.y));
			}
			else
				m_enable = false;
		}
		else
			m_enable = false;
	}

	std::string SelectRect::GetExport()
	{
		std::stringstream ss;
		ss << "\t\"start\" : { \"x\" : \"" << m_vertices[0].position.x << "\",";
		ss << " \"y\" : \"" << m_vertices[0].position.y << "\"}," << std::endl;
		ss << "\t\"end\" : { \"x\" : \"" << m_vertices[2].position.x << "\",";
		ss << " \"y\" : \"" << m_vertices[2].position.y << "\"}";
		ss << std::endl;
		return ss.str();
	}

	void SelectRect::Update(const sf::Event &ev)
	{
		if (m_enable)
		{
			m_vertices[0].position = m_start_point;
			m_vertices[4].position = m_start_point;
			float pos_x = static_cast<float>(ev.mouseMove.x);
			float pos_y = static_cast<float>(ev.mouseMove.y);
			if (pos_x < m_select_area.left)
				pos_x = m_select_area.left;
			else if (pos_x > m_select_area.left + m_select_area.width)
				pos_x = m_select_area.left + m_select_area.width;
			if (pos_y < m_select_area.top)
				pos_y = m_select_area.top;
			else if (pos_y > m_select_area.top + m_select_area.height)
				pos_y = m_select_area.top + m_select_area.height;
			m_vertices[1].position = sf::Vector2f(pos_x, m_start_point.y);
			m_vertices[2].position = sf::Vector2f(pos_x, pos_y);
			m_vertices[3].position = sf::Vector2f(m_start_point.x, pos_y);
		}
	}
}
