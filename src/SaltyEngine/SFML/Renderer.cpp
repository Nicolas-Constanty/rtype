#include "SaltyEngine/SFML/Renderer.hpp"
#include "SaltyEngine/Sprite.hpp"

namespace SaltyEngine
{
	namespace SFML {
		Renderer::Renderer(sf::VideoMode const &vm, const std::string &name) :
				ARenderer<sf::Vector2i>(vm.width, vm.height),
				sf::RenderWindow(vm, name)
		{}

		void Renderer::Display() {
			if (isOpen()) {
				clear();
				DrawGame();
				DrawGUI();
				DrawDebug();
                DrawDrawable();
				DrawLabel();
				display();
			} else
				Debug::PrintWarning("Main window has been closed!");
		}

		/*sf::RenderWindow *Renderer::GetRenderWindow(void) const {
			return m_window.get();
		}*/

		void Renderer::DrawDebug() {
			for (std::list<BoxCollider2D *>::const_iterator it = m_debug.begin(); it != m_debug.end(); ++it) {
                if ((*it)->IsDebug())
				    (*it)->Display();
				draw((*it)->GetVertex());
			}
		}

		void Renderer::DrawGame() const {
			for (int it = 0; it < Layout::SIZE; ++it) {
				if (m_spriteRenderers.find(it) != m_spriteRenderers.end())
					DrawSprites(m_spriteRenderers.at(it));
			}
		}

		void Renderer::DrawGUI() const {
			if (m_spriteRenderers.find(-1) != m_spriteRenderers.end())
				DrawSprites(m_spriteRenderers.at(-1));
		}

		void Renderer::DrawSprites(const SpriteList &sprite_list) const {
			for (SpriteList::const_iterator it = sprite_list.begin(); it != sprite_list.end(); ++it) {
//				(*(*it).spr)->setPosition(
//						(*it).gm->transform.position.x * (*it).gm->transform.localScale.x - ((*it).rect->width * (*it).gm->transform.localScale.x / 2),
//						(*it).gm->transform.position.y * (*it).gm->transform.localScale.y - ((*it).rect->height * (*it).gm->transform.localScale.y / 2)
//				 );
				if ((*it).gm->ShouldBeRenderer() && (*it).gm->GetActiveSelf()) {
                    Color color = (*it).sprr->GetColor();
                    color *= 255;
                    (*(*it).spr)->setColor(sf::Color(color.r(), color.g(), color.b(), color.a()));
					(*it).wind->draw((*(*(*it).spr)));
				}
			}
		}

		void Renderer::AddSpriteRenderer(SpriteRenderer *const sprr) {
			m_spriteRenderers.emplace(std::make_pair(sprr->GetLayer(), SpriteList()));
			::SaltyEngine::Sprite<sf::Vector2i> **s = &sprr->m_sprite;
			sf::RenderWindow *w = dynamic_cast<sf::RenderWindow *>(sprr->GetWindow());
			if (w == nullptr)
				w = this;
			if (s && w)
				m_spriteRenderers.at(sprr->GetLayer()).push_back(Drawable((Sprite **) (s), w, sprr->gameObject, sprr));
		}

		void Renderer::AddLabel(SaltyEngine::GUI::SFML::Label *label)
		{
			if (label && std::find(m_labels.begin(), m_labels.end(), label) == m_labels.end())
				m_labels.push_back(label);
			else
				Debug::PrintWarning("Cannot add null label");
		}

		void Renderer::AddDebug(BoxCollider2D *box) {
			if (box == nullptr) {
				Debug::PrintWarning("Cannot add empty box collider");
				return;
			}
			if (std::find(m_debug.begin(), m_debug.end(), box) == m_debug.end())
				m_debug.push_back(box);
		}

		void Renderer::AddSelectable(GUI::Selectable *const select) {
			if (select == nullptr) {
				Debug::PrintWarning("Cannot add empty select");
				return;
			}
			if (std::find(m_selectables.begin(), m_selectables.end(), select) == m_selectables.end())
				m_selectables.push_back(select);
		}

		Renderer::~Renderer() {

		}

		void Renderer::RemoveSpriteRenderer(GameObject *const gm) {

            for (SpriteMap::iterator it = m_spriteRenderers.begin(); it != m_spriteRenderers.end(); ++it)
            {
                (*it).second.remove_if([gm](Drawable drawable) { return (gm == drawable.gm); });
            }
			GUI::SFML::Label *lb = gm->GetComponent<GUI::SFML::Label>();
			if (lb)
				m_labels.remove(lb);
            m_debug.remove_if([gm](BoxCollider2D *box) { return (gm == box->gameObject); });
        }

        ::SaltyEngine::Vector2i Renderer::GetRealSize() const {
			sf::Vector2u size = getSize();
			SaltyEngine::Vector2f	scale = SaltyEngine::Engine::Instance().GetCurrentScene()->GetScale();
            return SaltyEngine::Vector2i(static_cast<int>(size.x / scale.x), static_cast<int>(size.y / scale.y));
        }

		void Renderer::DrawLabel() {
			for (LabelList::const_iterator lab = m_labels.begin(); lab != m_labels.end() ; ++lab) {
                const Transform &t = (*lab)->gameObject->transform;
                (*lab)->setPosition(t.GetPosition().x * t.GetLocalScale().x, t.GetPosition().y * t.GetLocalScale().y);
				draw(*(*lab));
			}
		}

        void Renderer::DrawDrawable() {
            while (!m_drawables.empty()){
                draw(*m_drawables.front());
                m_drawables.pop();
            }
        }

        void Renderer::AddDrawable(const sf::Drawable *dr) {
            m_drawables.push(dr);
        }
    }
}


