#include "SaltyEngine/SFML/Renderer.hpp"
#include "SaltyEngine/SFML/Window.hpp"
#include "SaltyEngine/Debug.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "Common/MakeUnique.hpp"

namespace SaltyEngine
{
	namespace SFML
	{
		Renderer::Renderer(sf::VideoMode const &vm, const std::string& name) : m_window(Make_unique<sf::RenderWindow>(vm, name))
		{
		}

		void Renderer::Display() const
		{
			if (m_window->isOpen())
			{
				m_window->clear();
				DrawGame(GetSprites());
				DrawGUI(GetSprites());
				DrawDebug();
				m_window->display();
			}
			else
				Debug::PrintWarning("Main window has been closed!");
		}

		sf::RenderWindow * Renderer::GetRenderWindow(void) const
		{
			return m_window.get();
		}

		void Renderer::DrawDebug() const
		{
			for (std::list<BoxCollider2D *>::const_iterator it = m_debug.begin(); it != m_debug.end(); it++)
			{
				(*it)->Display();
				m_window->draw((*it)->GetVertex());
			}
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
						Rect *rect = dynamic_cast<Rect *>((*sprr)->gameObject->GetComponent<SpriteRenderer>()->GetSprite()->GetRect());
						if (rect)
						{
							s->setPosition(
								(*sprr)->gameObject->transform.position.x - (rect->width / 2),
								(*sprr)->gameObject->transform.position.y - (rect->height / 2));
							m_window->draw(*s);
						}
					}
				}
			}
		}

		void Renderer::AddSpriteRenderer(SpriteRenderer* const sprr)
		{
			if (m_spriteRenderers.find(sprr->GetLayer()) == m_spriteRenderers.end())
				m_spriteRenderers.emplace(std::make_pair(sprr->GetLayer(), SpriteList()));
			m_spriteRenderers.at(sprr->GetLayer()).push_back(sprr);
		}

		void Renderer::AddDebug(BoxCollider2D *box)
		{
			m_debug.push_back(box);
		}

		Renderer::SpriteMap  Renderer::m_spriteRenderers = {};
		std::list<BoxCollider2D *> Renderer::m_debug = {};
	}
}


