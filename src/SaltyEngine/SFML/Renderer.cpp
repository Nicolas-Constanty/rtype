#include "SaltyEngine/SFML/Renderer.hpp"
#include "SaltyEngine/SFML/Window.hpp"
#include "SaltyEngine/Debug.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "Common/MakeUnique.hpp"

namespace SaltyEngine
{
	namespace SFML
	{
		Renderer::Renderer(sf::VideoMode& vm, const std::string& name) : m_window(Make_unique<sf::RenderWindow>(vm, name))
		{
		}

		void Renderer::Display() const
		{
			if (m_window->isOpen())
			{
				m_window->clear();
				DrawGame(GetSprites());
				DrawGUI(GetSprites());
				m_window->display();
			}
			else
				Debug::PrintWarning("Main window has been closed!");
		}

		sf::RenderWindow * Renderer::GetRenderWindow() const
		{
			return m_window.get();
		}

		void Renderer::DrawGame(const SpriteMap &sprite_map) const
		{
			for (int it = 0; it < Layout::SIZE; ++it)
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
					{
						s->setPosition((*sprr)->gameObject->transform.position.x, (*sprr)->gameObject->transform.position.y);
						m_window->draw(*s);
					}
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


