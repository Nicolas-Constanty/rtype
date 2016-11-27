#include "SaltyEngine/SFML/Renderer.hpp"
#include "SaltyEngine/SFML/Window.hpp"
#include "SaltyEngine/Debug.hpp"

namespace SaltyEngine
{
	namespace SFML
	{


		Renderer::Renderer(sf::VideoMode& vm, const std::string& name) : m_window(std::make_unique<sf::RenderWindow>(vm, name))
		{
		}

		void Renderer::Display() const
		{
			if (m_window->isOpen())
			{
				sf::Event event;
				while (m_window->pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						m_window->close();
				}
				m_window->clear();
				DrawGame(GetSprites());
				DrawGUI(GetSprites());
				m_window->display();
			}
			else
				Debug::PrintWarning("Main window has been closed!");
		}

		void Renderer::DrawGame(const SpriteMap &sprite_map) const
		{
			for (int it = 0; it < Layout::SIZE; it++)
			{
				if (sprite_map.find(it) != sprite_map.end())
					DrawSprites(sprite_map.at(it));
			}
		}

		void Renderer::DrawGUI(const SpriteMap &sprite_map) const
		{
			if (sprite_map.find(-1) != sprite_map.end())
				DrawSprites(sprite_map.at(-1));
		}

		void Renderer::DrawSprites(const SpriteList &sprite_list) const
		{
			for (SpriteList::const_iterator sprr = sprite_list.begin(); sprr != sprite_list.end(); ++sprr)
			{
				Window *w = dynamic_cast<Window *>((*sprr)->GetWindow());
				if (w == nullptr)
				{
					Sprite *s = dynamic_cast<Sprite *>((*sprr)->GetSprite());
					if (s != nullptr)
						m_window->draw(*s);
				}
			}
		}

		void Renderer::AddSpriteRenderer(SpriteRenderer* const sprr)
		{
			if (m_spriteRenderers.find(sprr->GetLayer()) == m_spriteRenderers.end())
				m_spriteRenderers.emplace(std::make_pair(sprr->GetLayer(), SpriteList()));
			m_spriteRenderers.at(sprr->GetLayer()).push_back(std::unique_ptr<SpriteRenderer>(sprr));
		}

		Renderer::SpriteMap  Renderer::m_spriteRenderers = {};
	}
}


