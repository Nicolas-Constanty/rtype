#include "SaltyEngine/SFML/Renderer.hpp"

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
				DrawGame();
				DrawGUI();
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
			for (std::list<BoxCollider2D *>::const_iterator it = m_debug.begin(); it != m_debug.end(); ++it)
			{
				(*it)->Display();
				m_window->draw((*it)->GetVertex());
			}
		}

		void Renderer::DrawGame() const
		{
			for (int it = 0; it < Layout::SIZE; ++it)
			{
				if (m_spriteRenderers.find(it) != m_spriteRenderers.end())
					DrawSprites(m_spriteRenderers.at(it));
			}
		}

		void Renderer::DrawGUI() const
		{
			if (m_spriteRenderers.find(-1) != m_spriteRenderers.end())
				DrawSprites(m_spriteRenderers.at(-1));
		}

		void Renderer::DrawSprites(const SpriteList &sprite_list) const
		{
			for (SpriteList::const_iterator spr = sprite_list.begin(); spr != sprite_list.end(); ++spr)
			{	
				(*spr).spr->setPosition(
					(*spr).gm->transform.position.x - ((*spr).rect->width / 2),
					(*spr).gm->transform.position.y - ((*spr).rect->height / 2));
				(*spr).wind->draw((*(*spr).spr));
			}
		}

		void Renderer::AddSpriteRenderer(SpriteRenderer* const sprr)
		{
			if (m_spriteRenderers.find(sprr->GetLayer()) == m_spriteRenderers.end())
				m_spriteRenderers.emplace(std::make_pair(sprr->GetLayer(), SpriteList()));
			Sprite *s = dynamic_cast<Sprite *>(sprr->GetSprite());
			Rect *r = dynamic_cast<Rect *>(sprr->GetSprite()->GetRect());
			sf::RenderWindow *w = dynamic_cast<sf::RenderWindow *>(sprr->GetWindow());
			if (w == nullptr)
				w = m_window.get();
			if (r && s && w)
				m_spriteRenderers.at(sprr->GetLayer()).push_back(Drawable(s, r, w, sprr->gameObject));
		}

		void Renderer::AddDebug(BoxCollider2D *box)
		{
			if (box == nullptr) {
				Debug::PrintWarning("Cannot add empty box collider");
				return;
			}
			m_debug.push_back(box);
		}

		void Renderer::AddSelectable(GUI::Selectable* const select)
		{
			if (select == nullptr) {
				Debug::PrintWarning("Cannot add empty select");
				return;
			}
			m_selectables.push_back(select);
		}
	}
}


